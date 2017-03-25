LIBS = -lglfw3 -pthread -lglfw3 -lSOIL -lGLEW -lGLU -lGL -lXrandr -lXxf86vm -lXi -lXinerama -lX11 -lrt -ldl -lXcursor

hello:
	g++ HelloGL.cpp Shader.cpp  $(LIBS) -o HelloGL