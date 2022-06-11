SRCS = main.c mlx.c dda.c noise1D.c noise2D.c noise2DtoFdf.c utils.c
OBJS = $(SRCS:.c=.o)

C = gcc

# Compiler flags (+ where to find headers)
CFLAGS = -Wall -Wextra
CFLAGS += -I/usr/include -Imlx -Iminilibx-linux
# Linking flags(+ where to find libs)
LFLAGS_MAC = -Lmlx -lmlx -framework OpenGL -framework AppKit
LFLAGS = -L/usr/lib -Lminilibx-linux -lmlx -L/usr/lib/x86_64-linux-gnu -lXext -lX11 -lm -lbsd

NAME = noise_bin

%.o : %.c
	$(C) $(CFLAGS) -g -c $< -o $@

$(NAME): $(OBJS)
	$(C) $^ $(LFLAGS) -o $(NAME)

all: $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean all
