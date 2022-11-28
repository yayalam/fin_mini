#include "../../../minishell.h"

char	*quotes_parse_handler(char *str, t_one_element **ptr, int type, t_all_env *env)
{
	char	*value;

	*ptr = (*ptr)->next;
	while (*ptr && (*ptr)->type != type)
	{
		if (!str)
			str = ft_strdup("");
		if ((*ptr)->type == DOLLAR && (*ptr)->state == IN_DQUOTE)
		{
			value = get_value_of_env((*ptr)->content + 1, env);
			if (value)
				str = ft_strjoin(str, value);
		}
		else
			str = ft_strjoin(str, (*ptr)->content);
		*ptr = (*ptr)->next;
	}
	if (*ptr)
		*ptr = (*ptr)->next;
	return (str);
}