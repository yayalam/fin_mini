#include "../../../minishell.h"

t_head_redir	*redir_parse_handler(t_one_element **ptr, t_head_redir *red, t_all_env *env)
{
	int	type;
	char			*arg;

	type = (*ptr)->type;
	while ((*ptr)->type != WORD && (*ptr)->type != DOLLAR)
		*ptr = (*ptr)->next;
	if ((*ptr)->type == DOLLAR && type != HERE_DOC)
	{
		arg = get_value_of_env((*ptr)->content + 1, env);
		if (!arg)
		{
			printf("bash: %s: ambiguous redirect\n", (*ptr)->content);
			return (NULL);
		}
	}
	else
		arg = ft_strdup((*ptr)->content);
	*ptr = (*ptr)->next;
	if (type == HERE_DOC)
		return (heredoc_parse_handler(red, arg, env->env));
	add_back_element_redir(red, creat_element_redir(arg, type));
	return (red);
}