CC = gcc

ifeq ($(OS),Windows_NT)
	RM = del
	EXE = .exe
	DLL = .dll
else
	RM = rm -f
	EXE = .out
	DLL = .so
endif

ifeq ($(OS),Windows_NT)
	INCLUDE_PATHS = \
		-IC:\\Libs\\include \
		-LC:\\Libs\\lib
else
	INCLUDE_PATHS =
endif

ifeq ($(OS),Windows_NT)
	LINK_LIBRARIES = \
		-lmingw32 \
		-luser32 \
		-lgdi32 \
		-lwinmm \
		-ldxguid \
		-lglew32 \
		-lSDL2main \
		-lSDL2 \
		-lSDL2_image \
		-lSDL2_ttf \
		-lopengl32 \
		-limagehlp
else
	LINK_LIBRARIES = \
		-lSDL2main \
		-lSDL2 \
		-lSDL2_image \
		-lSDL2_ttf
endif
	

all: main$(EXE) some_lib$(DLL) legacy_lib$(DLL)

test: all
	./main$(EXE)

.PHONY: all test

some_lib$(DLL): some_lib.c lib_impl.h share.h
	$(CC) -shared -o some_lib$(DLL) some_lib.c $(CFLAGS)

legacy_lib$(DLL): legacy_lib.c lib_impl.h share.h
	$(CC) -shared -o legacy_lib$(DLL) legacy_lib.c $(CFLAGS)

main$(EXE): main.c share.h
	$(CC) -o main$(EXE) main.c $(CFLAGS) $(INCLUDE_PATHS) $(LINK_LIBRARIES)


clean:
	$(RM) some_lib$(DLL)
	$(RM) legacy_lib$(DLL)
	$(RM) main$(EXE)
