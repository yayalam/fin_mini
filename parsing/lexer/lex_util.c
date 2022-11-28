#include "../../minishell.h"

int	word_lexer_type_get(t_lexer_lst *tk, char *str, int state)
{
	int	i;

	i = 0;
	while (!check_special_char(str[i]))
		i++;
	add_lexer_element_back(tk, create_new_lexer_element(str, i, WORD, state));
	return (i);
}

int	env_key_lexer_type_get(t_lexer_lst *tk, char *str, int state)
{
	int	i;

	i = 1;
	if (str[i] == '?' || (str[i] >= '0' && str[i] <= '9'))
		i++;
	else
		while (ft_isalnum(str[i]) && str[i] != '\n' && str[i] != '\0')
			i++;
	add_lexer_element_back(tk, create_new_lexer_element(str, i, DOLLAR, state));
	return (i);
}

void	check_modify_state_of_quote(t_lexer_lst *tk, char *str, int *state, int flag)
{
	int	state_tmp;
	int	type;

	if (flag == 1)
	{
		state_tmp = IN_QUOTE;
		type = QOUTE;
	}
	else
	{
		state_tmp = IN_DQUOTE;
		type = DOUBLE_QUOTE;
	}
	if (*state == GENERAL)
	{
		add_lexer_element_back(tk, create_new_lexer_element(str, 1, type, *state));
		*state = state_tmp;
	}
	else if (*state == state_tmp)
	{
		*state = GENERAL;
		add_lexer_element_back(tk, create_new_lexer_element(str, 1, type, *state));
	}
}
