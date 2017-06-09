LIBS = -lglfw3 -pthread -lglfw3 -lSOIL -lGLEW -lGLU -lGL -lXrandr -lXxf86vm -lXi -lXinerama -lX11 -lrt -ldl -lXcursor

hello:
	g++ src/HelloGL.cpp src/Shader.cpp  $(LIBS) -o HelloGL