CFILES = main.c

OBJDIR = obj
OFILES = $(addprefix $(OBJDIR)/, $(CFILES:.c=.o))

NAME      = cub3d
CC        = cc
CFLAGS    = -std=gnu11 -g3 -Wall -Wextra -Werror -Ift_printf -Iget_next_line -Ilibft -Iminilibx-linux -Isrc/parser -Isrc/game -I.
MLX_FLAGS = -Lminilibx-linux -lmlx -lX11 -lXext -lm

MAKEFLAGS += --no-print-directory --silent
PRINTF     = ft_printf/libftprintf.a
GNL        = get_next_line/get_next_line.a
LIBFT      = libft/libft.a
MLX        = minilibx-linux/libmlx_Linux.a
PARSER     = src/parser/parser.a
GAME       = src/game/game.a

GREEN   = \033[0;32m
YELLOW  = \033[0;33m
BLUE    = \033[0;36m
RED     = \033[0;31m
MAGENTA = \033[0;35m
CYAN    = \033[0;36m
RESET   = \033[0m

all: $(NAME)

$(NAME): $(MLX) $(OFILES) $(PRINTF) $(GNL) $(LIBFT) $(PARSER) $(GAME)
	@printf "$(GREEN)» 📦 Linking   $(RESET)» $(MAGENTA)./$(NAME)$(RESET)\n"
	@$(CC) $(CFLAGS) $(MLX_FLAGS) $(OFILES) $(GAME) $(PARSER) $(PRINTF) $(GNL) $(LIBFT) $(MLX) -o $(NAME)

$(OBJDIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@printf "$(BLUE)» ⚙️  Compiling $(RESET)» $(YELLOW)%20s$(RESET) | $(GREEN)%s$(RESET)\n" "$<" "$@"
	@$(CC) $(CFLAGS) -c $< -o $@

$(MLX): FORCE
	@[ -d $(dir $(MLX)) ] || git clone https://github.com/42Paris/minilibx-linux.git
	@$(MAKE) -C $(dir $@)

$(GNL): FORCE
	@$(MAKE) -C $(dir $@)

$(PRINTF): FORCE
	@$(MAKE) -C $(dir $@)

$(LIBFT): FORCE
	@$(MAKE) -C $(dir $@)

$(PARSER): FORCE
	@$(MAKE) -C $(dir $@)

$(GAME): FORCE
	@$(MAKE) -C $(dir $@)

clean:
	@printf "$(RED)» 🧹 Cleaning  $(RESET)» $(CYAN)./$(OBJDIR) $(RESET)\n"
	@rm -rf $(OBJDIR)
	@[ -d $(dir $(MLX)) ] && $(MAKE) -C $(dir $(MLX)) clean || true
	@$(MAKE) -C $(dir $(GNL)) clean
	@$(MAKE) -C $(dir $(PRINTF)) clean
	@$(MAKE) -C $(dir $(LIBFT)) clean
	@$(MAKE) -C $(dir $(PARSER)) clean
	@$(MAKE) -C $(dir $(GAME)) clean

fclean: clean
	@[ -d $(dir $(MLX)) ] && $(MAKE) -C $(dir $(MLX)) clean || true
	@$(MAKE) -C $(dir $(GNL)) fclean
	@$(MAKE) -C $(dir $(PRINTF)) fclean
	@$(MAKE) -C $(dir $(LIBFT)) fclean
	@$(MAKE) -C $(dir $(PARSER)) fclean
	@$(MAKE) -C $(dir $(GAME)) fclean
	@printf "$(RED)» 🔥 Removing  $(RESET)» $(MAGENTA)./$(NAME)$(RESET)\n"
	@rm -f $(NAME)

re: fclean all

FORCE:
.PHONY: all clean fclean re FORCE
