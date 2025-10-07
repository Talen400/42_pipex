# Colors for output
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
MAGENTA = \033[0;35m
CYAN = \033[0;36m
WHITE = \033[0;37m
RESET = \033[0m

# Configuration
NAME := pipex
CC := cc
CFLAGS	:= -g -Wextra -Wall -Werror

# Directories
SRC_DIR := ./srcs
OBJ_DIR := ./objs
LIBFT_DIR := ./libft

# Libraries
LIBFT := $(LIBFT_DIR)/libft.a
LIBS := $(LIBFT)

# Mandatory sources
SRCS := $(shell find $(SRC_DIR) -name "*.c")

OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

MANDATORY_MARK := .mandatory
BONUS_MARK := .bonus

all: $(NAME)

# Mandatory part

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@echo "$(BLUE)Created objects directory$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS)$(HEADERS) -c $< -o $@
	@echo "$(CYAN)Compiled: $(notdir $<)$(RESET)"

$(NAME): $(MANDATORY_MARK)

$(MANDATORY_MARK): $(LIBFT) $(OBJS)
	@rm -f $(BONUS_MARK)
	@echo "$(YELLOW)Linking $(NAME)...$(RESET)"
	@$(CC) $(OBJS) $(LIBS) -o $(NAME)
	@touch $(MANDATORY_MARK)
	@echo "$(GREEN)$(NAME) build successfully!$(RESET)"

# Libraries
$(LIBFT):
	@echo "$(YELLOW)Building libft...$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR)
	@echo "$(GREEN)Libft built sucessfully!$(RESET)"

clean:
	@echo "$(RED)Cleaning object files...$(RESET)"
	@rm -rf $(OBJ_DIR)
	@rm -f $(MANDATORY_MARK)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@echo "$(RED)Clean completed!$(RESET)"

fclean: clean
	@echo "$(RED)Full clean...$(RESET)"
	@rm -rf $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@echo "$(RED)Full clean completed!$(RESET)"

re: fclean all

.PHONY: all clean fclean re bonus


