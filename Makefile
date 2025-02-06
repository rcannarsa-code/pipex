NAME = pipex
CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

# Directories
SRC_DIR = src
INC_DIR = include
OBJ_DIR = obj
LIBFT_DIR = libft

# Sources
SRCS = $(addprefix $(SRC_DIR)/,\
	pipex.c\
	init.c\
	parse.c\
	execute.c\
	utils.c)

# Objects
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

# Libraries
LIBFT = $(LIBFT_DIR)/libft.a

# Include paths
INC = -I$(INC_DIR) -I$(LIBFT_DIR)

all: $(OBJ_DIR) $(LIBFT) $(NAME)

# Create objects directory
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Compile libft
$(LIBFT):
	make -C $(LIBFT_DIR)

# Compile program
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -lft -o $(NAME)

# Compile objects
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

clean:
	$(RM) -r $(OBJ_DIR)
	make clean -C $(LIBFT_DIR)

fclean: clean
	$(RM) $(NAME)
	make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re