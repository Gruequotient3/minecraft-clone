PROG = main

IMGUI_DIR = ./lib/imgui

CC = g++
CXXFLAGS = -Wall -Wextra -O3
CXXFLAGS += -Ilib/glad/include
CXXFLAGS += -Ilib/glm/
CXXFLAGS += -Ilib/glfw/include
CXXFLAGS += -Ilib/stb
CXXFLAGS += -I$(IMGUI_DIR) -I$(IMGUI_DIR)/backends

LDFLAGS = -lm
LDFLAGS += -lglad -lglfw3 -lglm -lstb_image 
LDFLAGS += -lX11 -lpthread -lXrandr -lXi -ldl 
LDFLAGS += -Llib/glad/
LDFLAGS += -Llib/glfw/src/
LDFLAGS += -Llib/glm/glm/
LDFLAGS += -Llib/stb

ifeq ($(shell uname), Darwin)
	MACOSX_DEPLOYMENT_TARGET = 11.0
        CFLAGS += -mmacosx-version-min=$(MACOSX_DEPLOYMENT_TARGET)
        LDFLAGS += -framework OpenGL -mmacosx-version-min=$(MACOSX_DEPLOYMENT_TARGET)
else
	LDFLAGS += -lGL
endif


# ImGui src
CXXSRC = $(IMGUI_DIR)/imgui.cpp $(IMGUI_DIR)/imgui_demo.cpp $(IMGUI_DIR)/imgui_draw.cpp $(IMGUI_DIR)/imgui_tables.cpp $(IMGUI_DIR)/imgui_widgets.cpp
CXXSRC += $(IMGUI_DIR)/backends/imgui_impl_glfw.cpp $(IMGUI_DIR)/backends/imgui_impl_opengl3.cpp

CXXSRC += $(wildcard src/*.cpp) $(wildcard src/**/*.cpp)

OBJ = $(CXXSRC:.cpp=.o)

RM = rm -rf

all: $(PROG)

$(PROG): $(OBJ)
	$(CC) -o main $(OBJ) $(LDFLAGS)

libs:
	@cd lib/glad && $(CC) -o src/glad.o -Iinclude -c src/glad.c && ar rcs libglad.a src/glad.o
	@cd lib/glm && cmake . -DCGLM_STATIC=ON && make
	@cd lib/glfw && cmake . && make
	@cd lib/stb && $(CC) -c stb_image.cpp -o stb_image.o && ar rcs libstb_image.a stb_image.o

%.o: %.cpp %.hpp
	$(CC) $(CXXFLAGS) -c $< -o $@ 

clean:
	$(RM) $(OBJ) $(PROG)
