all:
	g++ src/*.cpp -o Space_Boats -L/usr/local/lib -lSDL -lSDL_image -I./hdr -I/usr/local/include
