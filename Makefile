name = minishell

src = all_utils/utils_for_string/utils_str.c all_utils/utils_for_string/utils_str2.c all_utils/utils_for_string/utils_str3.c all_utils/utils_for_string/utils_str4.c \
	all_utils/utils_for_string/all_ft_strjoin.c all_utils/ft_atoi.c all_utils/ft_calloc.c all_utils/ft_itoa.c all_utils/ft_split.c all_utils/gnl_utils.c all_utils/gnl.c all_utils/redir_utils.c \
	cd/cd_utils.c cd/cd.c echo/echo.c echo/utils_echo.c env/env.c error_checker/error_syntax_checker.c error_checker/redir_pipe_check_err.c \
	exit/exit_utils.c exit/exit.c export/export.c export/util_export.c handle_env/search_env.c handle_env/util_env.c handle_env/utils_env2.c \
	list_utils/ast_utils.c list_utils/free_list_func.c list_utils/lex_list.c list_utils/list_env.c list_utils/list_redir.c main_exec/builtin_identify.c \
	main_exec/exec_utils.c main_exec/execute_cmd.c main_exec/main_execute.c main_exec/search_cmd_path.c minishell_signal_handler/all_sigs_handler.c \
	parsing/lexer/lex_util.c parsing/lexer/identifier.c parsing/lexer/main_lexer.c parsing/parsing/parsing_type/heredoc_parse.c parsing/parsing/parsing_type/pipe_pars.c \
	parsing/parsing/parsing_type/quotes_parse.c parsing/parsing/parsing_type/redir_parse.c parsing/parsing/parsing_type/word_parse.c parsing/parsing/par_main_utils.c \
	parsing/parsing/par_main.c parsing/parsing/util_pars.c pwd/pwd.c redir_exec/execute_redir.c unset/unset.c main_utils.c minishell_main.c

obj = $(src:.c=.o)

flags = -L/opt/homebrew/opt/readline/lib -I/opt/homebrew/opt/readline/include -lreadline -Wall -Wextra -Werror

hd = minishell.h

all: $(name)

$(name): $(src) $(hd)
	cc $(flags) $(src) -o $(name)

%.o:%.c
	cc $(flags) -c $< -o $@

clean:
	rm -rf $(obj)

fclean: clean
	rm -rf $(name)

re: fclean all