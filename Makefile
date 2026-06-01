CFLAGS = -Wall -Wextra -Werror -Wformat=2 -O3 -flto -ffast-math -pedantic
CC = gcc
NAME = space_time
RAYLIB = libs/raylib/src/libraylib.a
OBJ = build/main.o build/graphics.o build/space.o build/object.o build/mouse.o build/gravity.o build/keyboard.o
SRC = src/main.c src/graphics.c src/space.c build/object.c src/mouse.c src/gravity.c src/keyboard.c



LOCAL_INC = inc/
INC_DIR = libs/raylib/src -Ilibs/cJSON

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
	PLATFORM_LIBS = -Wl,-rpath,$(PWD)/libs/cJSON/build -Llibs/cJSON/build -framework Cocoa -framework IOKit -framework CoreVideo -framework OpenGL -lcjson 
	LIBCJSON = libs/cJSON/build/libcjson.dylib
else
	PLATFORM_LIBS = -lGL -lm -ldl -lpthread -lX11
	LIBCJSON = libs/cJSON/build/libcjson.a
endif

all: build $(NAME)

build/%.o: src/%.c
	$(CC) $(CFLAGS) -I$(LOCAL_INC) -I$(INC_DIR) $< -c -o $@


build:
	if [ ! -d "build/" ]; then \
		mkdir build; \
	fi

$(LIBCJSON):
	mkdir libs/cJSON/build
	cmake -S libs/cJSON -B libs/cJSON/build
	cmake --build libs/cJSON/build
	make -C libs/cJSON/build

$(RAYLIB):
	$(MAKE) -C libs/raylib/src PLATFORM=PLATFORM_DESKTOP

$(NAME): $(OBJ) $(RAYLIB) $(LOCAL_INC) $(LIBCJSON)
	$(CC) $(CFLAGS) $(PLATFORM_LIBS) $(OBJ) $(LIBCJSON) $(RAYLIB) -I$(LOCAL_INC) -I$(INC_DIR) -o $(NAME)

clean :
	rm -rf build/

fclean : clean
	rm -rf $(NAME)

re : fclean all

test : re
	./$(NAME) tests/space.json

.SILENT: build fclean clean
