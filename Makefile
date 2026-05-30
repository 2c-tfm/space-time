CFLAGS = -Wall -Wextra -Werror -Wformat=2 -O3 -flto -ffast-math -pedantic
GFLAGS = -framework Cocoa -framework IOKit -framework CoreVideo -framework OpenGL 
CC = gcc
NAME = space_time
RAYLIB = libs/raylib/src/libraylib.a
OBJ = build/main.o build/graphics.o build/space.o
SRC = src/main.c src/graphics.c src/space.c

LOCAL_INC = inc/
INC_DIR = libs/raylib/src

all: build $(NAME)

build/%.o: src/%.c
	$(CC) $(CFLAGS) -I$(LOCAL_INC) -I$(INC_DIR) $< -c -o $@


build:
	if [ ! -d "build/" ]; then \
		mkdir build; \
	fi

$(RAYLIB):
	$(MAKE) -C libs/raylib/src PLATFORM=PLATFORM_DESKTOP

$(NAME): $(OBJ) $(RAYLIB) $(LOCAL_INC)
	$(CC) $(CFLAGS) $(GFLAGS) $(OBJ) $(RAYLIB) -I$(LOCAL_INC) -I$(INC_DIR) -o $(NAME)

clean :
	rm -rf build/

fclean : clean
	rm -rf $(NAME)

re : fclean all

test : re
	./$(NAME)

.SILENT: build fclean clean
