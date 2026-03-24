# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaimega2 <jaimega2@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/11 14:47:47 by rnuno-im          #+#    #+#              #
#    Updated: 2026/01/20 15:09:10 by jaimega2         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell

SRCS	= main.c \
		  srcs/utils/shell_loop.c \
		  srcs/utils/process_input.c \
		  srcs/utils/process_input_utils.c \
		  srcs/executor/executor.c \
		  srcs/executor/executor_utils.c \
		  srcs/executor/executor_utils_2.c \
		  srcs/lexer/tokenizer.c \
		  srcs/lexer/token_extract.c \
		  srcs/lexer/preprocess.c \
		  srcs/lexer/preprocess_utils.c \
		  srcs/lexer/lexer_handlers.c \
		  srcs/lexer/lexer_list_utils.c \
		  srcs/parser/parse_tokens.c \
		  srcs/parser/parse_tokens_core.c \
		  srcs/parser/parse_tokens_utils.c \
		  srcs/parser/parse_handlers.c \
		  srcs/parser/parser_utils.c \
		  srcs/expander/expand_vars.c \
		  srcs/expander/expand_utils.c \
		  srcs/expander/remove_quotes.c \
		  srcs/executor/builtins/builtins.c \
		  srcs/executor/builtins/ft_echo.c \
		  srcs/executor/builtins/ft_env.c \
		  srcs/executor/builtins/ft_exit.c \
		  srcs/executor/builtins/ft_pwd.c \
		  srcs/executor/builtins/ft_cd.c \
		  srcs/executor/builtins/ft_unset.c \
		  srcs/executor/builtins/ft_export.c \
		  srcs/utils/env_utils.c \
		  srcs/utils/export_utils.c \
		  srcs/executor/pipex/pipex.c \
		  srcs/executor/pipex/pipex_utils.c \
		  srcs/executor/redirections/heredoc.c \
		  srcs/executor/redirections/redirections.c \
		  srcs/utils/print_error.c \
		  srcs/executor/signals/signals.c \
		  srcs/executor/signals/ctrl-D.c \
		  srcs/executor/signals/ctrl-C.c 

OBJ_DIR	= obj
OBJS	= $(SRCS:%.c=$(OBJ_DIR)/%.o)

LIBFT	= libft/libft.a

CC		= cc

CFLAGS	= -Wall -Wextra -Werror -Iincludes

LDFLAGS	= -lreadline

all: $(NAME)

$(NAME): $(OBJ_DIR) $(LIBFT) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -Llibft -lft $(LDFLAGS) -o $(NAME)
	@echo "✅ Compilation complete: $(NAME)"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	@make -s -C libft

clean:
	@rm -rf $(OBJ_DIR)
	@make -s -C libft clean
	@echo "🧹 Object files cleaned."

fclean: clean
	@rm -rf $(NAME)
	@make -s -C libft fclean
	@echo "🗑️  All cleaned."

re: fclean all

.PHONY: all clean fclean re