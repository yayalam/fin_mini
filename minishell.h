#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <signal.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <unistd.h>
# include <dirent.h>
# include <fcntl.h>
# include <errno.h>
# include <readline/history.h>
# include <readline/readline.h>

# define	EQUAL 0
# define	WORD -1
# define	SPACE ' '
# define	NEW_LINE '\n'
# define	QOUTE '\''
# define	DOUBLE_QUOTE '\"'
# define	DOLLAR '$'
# define	PIPE '|'
# define	IN_REDIR '<'
# define	OUT_REDIR '>'
# define	HERE_DOC 4
# define	DOUBLE_OUT 5
# define	READING 0
# define	EXECUTING 1
# define	IN_DQUOTE 0
# define	IN_QUOTE 1
# define	GENERAL 2
# define	CMD 0
#define RED     "\033[31m"
#define RESET   "\033[0m"
#define GREEN   "\033[32m" 

typedef struct s_one_elem		t_one_element;
typedef struct s_one_redir_elem	t_one_red_element;
typedef union u_cmd_pipe		t_cmd_or_pipe;
typedef struct s_one_node_tree	t_one_node_tree;
typedef struct s_node_pipe		t_node_pipe;
typedef struct s_head_redir	t_head_redir;

typedef struct s_fd
{
	int	in;
	int	out;
}	t_fd;

typedef struct s_one_cmd
{
	char			**args;
	char			**env;
	t_fd			fd;
	t_head_redir	*redir;
}	t_one_cmd;

typedef struct s_node_pipe
{
	t_one_node_tree	*left;
	t_one_node_tree	*right;
}	t_node_pipe;

typedef union u_cmd_pipe
{
	t_node_pipe	*pipe;
	t_one_cmd	*cmd;
}	t_cmd_or_pipe;

typedef struct s_one_node_tree
{
	int				type;
	t_cmd_or_pipe	*content;
}	t_one_node_tree;

typedef struct s_tree_root
{
	t_one_node_tree	*root;	
}	t_tree_root;

typedef struct s_one_elem
{
	char			*content;
	int				len;
	int	type;
	int	state;
	t_one_element			*next;
	t_one_element			*prev;
}	t_one_element;

typedef struct s_lexer_lst
{
	t_one_element	*head;
	t_one_element	*tail;
	int		size;
}	t_lexer_lst;

typedef struct s_env_one
{
	char				*key;
	char				*value;
	struct s_env_one	*next;
	struct s_env_one	*prev;
}	t_env_one_element;

typedef struct s_all_env
{
	t_env_one_element			*head;
	char				**env;
	int					size;
}	t_all_env;

typedef struct s_data
{
	int					exit_status;
	int	shell_state;
	int					pid;
	int					which;
	t_all_env				*ev;
	t_lexer_lst				*lex;
	t_tree_root				*tree;
	int					alloc;
	char				**env;
}	t_data;

typedef struct s_one_redir_elem
{
	char			*arg;
	int	type;
	t_one_red_element	*next;
}	t_one_red_element;

typedef struct s_head_redir
{
	t_one_red_element	*head;
	t_one_red_element	*tail;
	int				size;
}	t_head_redir;

t_data						g_data;


	/*all utils*/
int	ft_atoi(char *str);
void	*ft_calloc(size_t count, size_t size);
char	*ft_itoa(int n);
char	**ft_split(char *s, char c);
char	*get_next_line(int fd);
/*gnl utils*/
size_t	ft_strlen_gnl(char *s);
int	ft_strchr_gnl(char *s1, char c);
char	*ft_strjoin_gnl(char *s1, char *s2);
/*gnl*/

/*str utils*/
int	ft_strncmp(char *s1, char *s2, size_t n);
char	*ft_strjoin_directory(char *s1, char *s2);
int	ft_strisspace(char *str);
int	ft_isalnum(int c);
int	ft_strlen(char *s);
char	*ft_strjoin(char *s1, char *s2);
int		ft_strchr(char *s, int c);
char	*ft_substr(char *s, unsigned int start, size_t len);
char	*ft_strdup(char *s1);
char	*ft_strndup(char *s1,int n);
/*str utils*/
	/*all utils*/

	/*handle env*/
/*list env*/
t_all_env	*init_env(t_all_env *env);
t_env_one_element	*create_new_elem_env(char *line);
void	add_env_elem(t_all_env *env, t_env_one_element *new);
t_all_env	*create_all_env_struct(char **tab);
/*list env*/
/*search env*/
char	*get_value_of_env(char *key, t_all_env *env);
t_env_one_element	*search_element_struct_env(t_all_env *env, char *key);
char	*search_element_array_env(char *key, char **env);
char	*find_value_expand_env(char **line, char **env);
char	*env_value_expand(char *line, char **env);
/*search env*/
/*utils env*/
void	del_one_element_env(t_all_env *env, t_env_one_element *elem);
void	free_all_srtuct_env(t_all_env *env);
char	**from_struct_to_array(t_all_env *env);
/*utils env*/
	/*handle env*/

	/*lexer*/
/*lex list*/
int	check_if_no_element(t_lexer_lst *list);
t_lexer_lst	*lexer_lst_init(t_lexer_lst *list);
t_one_element	*create_new_lexer_element(char *content, int len, int type, int state);
void	add_lexer_element_back(t_lexer_lst *list, t_one_element *new);
void	free_lexer_all_struct(t_lexer_lst *list);
/*lex list*/

/*lex utilt*/
int	ft_isspace(char c);
int	check_special_char(char c);
int	word_lexer_type_get(t_lexer_lst *tokens, char *str, int state);
int	env_key_lexer_type_get(t_lexer_lst *tokens, char *str, int state);
void	check_modify_state_of_quote(t_lexer_lst *tokens, char *str, int *state, int flag);
/*lex utilt*/

/*main lex*/
int	identify_redirections(t_lexer_lst *tokens, char *line, int i, int *state);
int	identifie_line(t_lexer_lst *tokens, char *line, int i, int *state);
t_lexer_lst	*lexer(char *line);
/*main lex*/

	/*lexer*/
	
	/*my_parser*/
/*ast*/
t_tree_root	*init_tree(t_tree_root *tree);
t_one_node_tree	*init_new_cmd_node(char **args, char **env, t_head_redir *redir);
void	free_tree(t_one_node_tree *node);
/*ast*/

/*par util*/
int	check_if_redir(int type);
void	quotes_redir_counter(t_one_element **elem, int type, int *i);
int	arg_counter(t_one_element *elem);
/*par util*/

/*redir list utils*/
t_head_redir	*redir_head_lst_init(t_head_redir *list);
t_one_red_element	*creat_element_redir(char *arg, int type);
void	add_back_element_redir(t_head_redir *list, t_one_red_element *new);
void	free_redir_list(t_head_redir *list);
/*redir list utils*/

/*par main*/
void	expand_env_element(t_one_element **ptr, t_all_env *env, char **args, int *i);
int	cmd_parser2(t_one_element **ptr, t_all_env *env,
		t_head_redir *redir, char **args);
t_one_node_tree	*cmd_parser(t_one_element **ptr, t_all_env *env);
int	my_parser(t_tree_root **tree, t_one_element *ptr, t_all_env *env);
/*par main*/

/*par type*/
char	*quotes_parse_handler(char *str, t_one_element **ptr, int type, t_all_env *env);
t_head_redir	*heredoc_parse_handler(t_head_redir *redir, char *arg, char **env);
t_head_redir	*redir_parse_handler(t_one_element **ptr, t_head_redir *redir, t_all_env *env);
t_one_node_tree	*pipe_parse_handler(t_one_element **ptr);
void	word_parse_handler(t_one_element **ptr, char **args, int *i);
/*par type*/
	/*parse*/

/*handle error*/
int	check_pipe_err(t_one_element *ptr);
int	check_redir_err(t_one_element *ptr);
int	ft_perror(char *msg, char *utils);
int	ft_puterr(char *cmd, char *arg, char *msg, int err_num);
/*handle error*/

/*syntax check error*/
t_one_element	*white_space_skipper(t_one_element *ptr, int opt);
char	*check_redir_type(int type);
t_one_element	*check_quote_unclose(t_one_element **ptr, int type);
int	check_err_syntax(t_lexer_lst *list);
/*syntax check error*/

/*main && main utils*/
void	init_global_var(t_data *data);
void	assign_global_data(char **env);
int	counter_number_of_cmds(t_one_node_tree *ptr);
int	readline_luncher(char **line);
void	ft_wait(void);
void	mini_shell_executor(char **env);
/*main && main utils*/

/*signals all*/
void	init_sigaction(t_data *data);
void	handle_sigaction(int sig, siginfo_t *siginfo, void *ptr);
/*signals all*/

		/*execution*/
	/*built in exec*/
/*echo*/
void	cmd_state_check(t_one_element**ptr, char **env, int *value);
void	add_number_to(int *i, int plus);
int	ft_echo(t_one_cmd *cmd, t_one_element *lex, char **env);
int	ft_strjoin_echo(t_one_cmd **cmd, t_one_element *ptr, char **env, int i);
int	echo_cmd_check(t_one_element *ptr, char **env);
int	check_echo_args(char **args);
int	if_flag(char *opt);
/*echo*/

/*cd*/
int	ft_cd(t_one_cmd *cmd, char ***env);
void	cd_dir_change_in_env(t_all_env *ev, char *cwd, char *owd);
/*cd*/

/*unset*/
int	ft_unset(t_one_cmd *cmd, char ***ev);
void	delete_env_for_unset(char *args, t_all_env *env);
int	ft_isdigit(char c);
/*unset*/

/*pwd*/
int	ft_pwd(void);
/*pwd*/

/*exit*/
int	ft_exit(t_one_cmd *cmd, char **env);
int	check_exit_arg(char **args);
int	ft_isnum(char *num);
int	counter_args_exit(char **args);
/*exit*/

/*env*/
int	ft_env(t_one_cmd *cmd, char **env);
/*env*/

/*export*/
int	ft_export(char ***ev, t_one_cmd *cmd, t_one_element *head);
int	ft_isalpha(char c);
void	env_var_handler(t_all_env *env, t_one_cmd *cmd, t_one_element *head);
void	check_index(t_all_env *env, char *args_i, char **tmp, int index);
int	ft_strjoin_export(t_one_cmd **cmd, t_one_element *ptr, char **env, int i);
/*util 1*/
void	print_env_sorted_export_noparam(t_all_env *env);
void	sort_env_for_export(t_all_env *env);
void	swap_env_elem(t_env_one_element *a, t_env_one_element *b);
int	ft_strcmp(char *s1, char *s2);
/*util 1*/
/*util 2*/
int	check_export_cmd(t_one_element *ptr, char **env);
void	state_handler(t_one_element **ptr, char **env, int *value);
t_one_element	*search_key_all_env(t_one_element *head, char *arg, char **env);
int	check_equal_sign(char **args);
char	**ft_split_for_env(char *arg);
/*util 2*/
/*export*/
	/*built in exec*/
/*exec cmd*/
int		cmd_executor(t_one_cmd *cmd, char **env, int fd[2]);
void	fd_handler_execve(t_one_cmd *cmd, int fd[2]);
void	builtin_ex(t_one_cmd *cmd, char ***env, t_one_element *head);
void	fd_handler_builtin(t_one_cmd *cmd);
void	swap_fd_var(int *old, int new_fd);
/*exec cmd*/

/*exec redir*/
void	redirin_ex(t_one_red_element *tmp, int *in);
void	redir_ex(t_head_redir *list, t_fd *fd);
/*exec redir*/

/*main exec*/
void	main_execute(t_one_node_tree *ptr, char ***env, int counter_number_of_cmds, t_one_element *lexer_head);
int		builtin_exec(t_one_node_tree *ptr, char ***env, t_one_element *head, int fd[2]);
void	check_last_pid(int pid, int count, int counter_number_of_cmds);
void	identify_builtin(t_one_cmd *cmd, char ***env, t_one_element *head);
int	is_buitlin(char *cmd);
/*main exec*/

/*search path*/
int		*search_r_l(t_one_node_tree *ptr);
char	*get_cmd(char *cmd, char **env);
char	*get_path_cmd(char *cmd, char **env);
char	*check_dot_slach(char *cmd, char **env);
/*search path*/
		/*execution*/

/*clean*/
void	lexer_free(t_lexer_lst *lexer);
void	parse_free(t_tree_root *tree);
void	parse_lex_free(t_lexer_lst *lexer, t_tree_root *tree);
void	cmd_free(t_one_cmd *cmd);
void	double_dimension_free(char **arg);
/*clean*/
#endif