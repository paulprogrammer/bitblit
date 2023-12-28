SDL_LIBS := $(shell sdl2-config --static-libs)
CFLAGS := -Isrc/include -I/opt/homebrew/include
CC=cc -std=c99

all: bitblit

bitblit: bitblit_mac

bitblit_mac: build/main.o build/log.o
	$(CC) $(SDL_LIBS) $^ -o $@

build/%.o: src/main/%.c src/include/%.h
	mkdir -p build
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm bitblit*
	find . -name *.o -exec rm {} +