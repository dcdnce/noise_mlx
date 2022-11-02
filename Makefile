SRCS = sources/main.c \
				sources/mlx.c \
				sources/dda.c \
				sources/utils.c \
				sources/noise1D/noise1D.c \
				sources/noise2D/noise2D.c \
				sources/noise2D/toFdf.c \
				sources/noise2D/interpolation.c \
				sources/noise2D/fbm.c \

OBJS = $(SRCS:.c=.o)

C = gcc

# Compiler flags (+ where to find headers)
CFLAGS = -Wall -Wextra
CFLAGS += -Iincludes
CFLAGS += -I/usr/include -Imlx -Iminilibx-linux
# Linking flags(+ where to find libs)
OS := $(shell uname)
ifeq ($(OS), Darwin)
	LFLAGS = -lmlx -framework OpenGL -framework AppKit
else
	LFLAGS = -L/usr/lib -Lminilibx-linux -lmlx -L/usr/lib/x86_64-linux-gnu -lXext -lX11 -lm -lbsd
endif

NAME = noise_bin

%.o : %.c
	$(C) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(C) $^ $(LFLAGS) -o $(NAME)

all: $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean all
