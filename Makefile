CFILES = main.c

OBJDIR = obj
OFILES = $(addprefix $(OBJDIR)/, $(CFILES:.c=.o))

NAME      = cub3d
CC        = cc
CFLAGS    = -std=gnu11 -Wall -Wextra -Werror -Iminilibx-linux
MLX_FLAGS = -Lminilibx-linux -lmlx -lX11 -lXext -lm

MAKEFLAGS += --no-print-directory --silent
MLX        = minilibx-linux/libmlx_Linux.a

GREEN   = \033[0;32m
YELLOW  = \033[0;33m
BLUE    = \033[0;36m
RED     = \033[0;31m
MAGENTA = \033[0;35m
CYAN    = \033[0;36m
RESET   = \033[0m

all: $(NAME)

$(NAME): $(MLX) $(OFILES)
	@printf "$(GREEN)» 📦 Linking   $(RESET)» $(MAGENTA)./$(NAME)$(RESET)\n"
	@$(CC) $(CFLAGS) $(MLX_FLAGS) $(OFILES) $(MLX) -o $(NAME)

$(OBJDIR)/%.o: %.c
	@mkdir -p $(OBJDIR)
	@printf "$(BLUE)» ⚙️  Compiling $(RESET)» $(YELLOW)%12s$(RESET) | $(GREEN)%s$(RESET)\n" "$<" "$@"
	@$(CC) $(CFLAGS) -c $< -o $@

$(MLX): FORCE
	@[ -d $(dir $(MLX)) ] || git clone https://github.com/42Paris/minilibx-linux.git
	@$(MAKE) -C $(dir $@)

clean:
	@printf "$(RED)» 🧹 Cleaning  $(RESET)» $(CYAN)./$(OBJDIR) $(RESET)\n"
	@[ -d $(dir $(MLX)) ] && $(MAKE) -C $(dir $(MLX)) clean || true
	@rm -rf $(OBJDIR)

fclean: clean
	@printf "$(RED)» 🔥 Removing  $(RESET)» $(MAGENTA)./$(NAME)$(RESET)\n"
	@rm -rf $(dir $(MLX))
	@rm -f $(NAME)

re: fclean all

FORCE:
.PHONY: all clean fclean re FORCE
