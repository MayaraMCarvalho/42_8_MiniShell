SOURCES		:=	env_init.c env_utils.c execve_error.c export_error.c \
				grammar_error.c builtin.c delimiter.c exec_utils.c \
				execute.c execve.c pipes.c pipes2.c redirect.c expand.c \
				del_quotes.c cmd_table.c grammar.c io_redirections.c \
				parser_utils.c signals_exec.c signals_init.c create_token.c \
				token_list.c token_utils.c token_string.c \
				\
				args.c cd.c commands.c echo.c env.c exit.c export.c free.c \
				handling.c lexer.c make_builtins.c minishell.c node.c \
				strcmp.c strtrim_mod.c token.c transfer_env.c unset.c utils.c \
				var.c verify.c

BUILD		:=	build
VPATH		:=	src/ src/input src/tokenize src/parse src/builtins src/executor src/errors src/env src/expander src/signals
OBJECTS		:=	$(addprefix $(BUILD)/, $(SOURCES:.c=.o))
NAME		:=	minishell
FLAGS		:=	-I$(shell brew --prefix readline)/include -Wall -Werror -Wextra
CC			:=	cc
HEADER		:=	headers/minishell.h libft/libft.h headers/token.h headers/parser.h headers/builtin.h headers/execute.h headers/execve.h headers/pipes.h headers/redirect.h headers/env_init.h headers/env_utils.h headers/expansions.h headers/signals.h headers/delimiter.h headers/error.h
LIBFT		:=	libft/libft.a
LIB_DIR		:=	libft
LIBS		:=	-lreadline -L$(shell brew --prefix readline)/lib

all: $(NAME)

$(NAME): $(OBJECTS) $(LIBFT)
	@printf "Compiling $(NAME)\n"
	@$(CC) $(FLAGS) -o $(NAME) $(OBJECTS) $(LIBFT) $(LIBS)

$(BUILD)/%.o: %.c $(HEADER) | $(BUILD)
	@$(CC) -g $(FLAGS) -c $< -o $@

$(BUILD):
	@mkdir -p $(BUILD)

$(LIBFT):
	make -C $(LIB_DIR)

clean:
	@rm -rf $(OBJECTS) $(BUILD)
	$(MAKE) -C $(LIB_DIR) clean
	@printf "Cleaned ✅\n"

fclean:
	@rm -rf $(OBJECTS) $(NAME) $(BUILD) test
	$(MAKE) -C $(LIB_DIR) fclean
	@printf "Fcleaned ✅\n"

re: fclean all

.PHONY: all test clean fclean re test_clean
