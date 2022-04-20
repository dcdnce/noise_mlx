SRCS = main.c mlx.c dda.c noise1D.c utils.c
OBJS = $(SRCS:.c=.o)

C = gcc

# Compiler flags (+ where to find headers)
CFLAGS = -Wall -Wextra
CFLAGS += -I/usr/include -Imlx
# Linking flags(+ where to find libs)
LFLAGS = -Lmlx -lmlx -framework OpenGL -framework AppKit

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
