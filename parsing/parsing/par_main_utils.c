#include "../../minishell.h"

int	cmd_parser2(t_one_element **ptr, t_all_env *env,
		t_head_redir *red, char **arg)
{
	int	i;

	i = 0;
	while ((*ptr) && (*ptr)->type != PIPE)
	{
		if ((*ptr)->type == WORD)
			word_parse_handler(ptr, arg, &i);
		else if ((*ptr)->type == SPACE)
			(*ptr) = (*ptr)->next;
		else if ((*ptr)->type == DOUBLE_QUOTE || (*ptr)->type == QOUTE)
		{
			arg[i] = quotes_parse_handler(arg[i], ptr, (*ptr)->type, env);
			if (arg[i])
				(i)++;
		}
		else if ((*ptr)->type == DOLLAR)
			expand_env_element(ptr, env, arg, &i);
		else if (check_if_redir((*ptr)->type))
		{
			if (!redir_parse_handler(ptr, red, env))
				return (EXIT_FAILURE);
		}
	}
	arg[i] = NULL;
	return (EXIT_SUCCESS);
}

t_one_node_tree	*cmd_parser(t_one_element **ptr, t_all_env *env)
{
	t_one_node_tree		*tmp;
	char			**args;
	t_head_redir	*red;
	int				size;

	red = NULL;
	size = arg_counter((*ptr));
	args = ft_calloc(sizeof(char *), (size + 1));
	red = redir_head_lst_init(red);
	if (!args || !red)
		return (NULL);
	if (cmd_parser2(ptr, env, red, args) == EXIT_FAILURE)
		return (NULL);
	tmp = init_new_cmd_node(args, env->env, red);
	return (tmp);
}