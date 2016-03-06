all:
	g++ -I ./hdr -C src/*.cpp -I/usr/local/include -L/usr/local/lib -lSDL -lSDL_image
