#include "../../minishell.h"

int	identify_redirections(t_lexer_lst *tk, char *rd_line, int i, int *state)
{
	int	j;

	j = i;
	if (rd_line[i] == '<')
	{
		if (rd_line[i + 1] == '<')
			add_lexer_element_back(tk, create_new_lexer_element(rd_line + (i++), 2, HERE_DOC, *state));
		else
			add_lexer_element_back(tk, create_new_lexer_element(rd_line + (i), 1, IN_REDIR, *state));
		i++;
	}
	else if (rd_line[i] == '>')
	{
		if (rd_line[i + 1] == '>')
			add_lexer_element_back(tk, create_new_lexer_element(rd_line + (i++), 2, DOUBLE_OUT, *state));
		else
			add_lexer_element_back(tk, create_new_lexer_element(rd_line + (i), 1, OUT_REDIR, *state));
		i++;
	}
	return (i - j);
}

int	identifie_line(t_lexer_lst *tk, char *rd_line, int i, int *state)
{
	if (!check_special_char(rd_line[i]))
		i += word_lexer_type_get(tk, rd_line + i, *state);
	else if (rd_line[i] == '\'')
		check_modify_state_of_quote(tk, rd_line + (i++), state, 1);
	else if (rd_line[i] == '\"')
		check_modify_state_of_quote(tk, rd_line + (i++), state, 2);
	else if (rd_line[i] == '$')
	{
		if (check_special_char(rd_line[i + 1]) || rd_line[i + 1] == '=')
		{
			add_lexer_element_back(tk, create_new_lexer_element(rd_line + i, 1, WORD, *state));
			i++;
		}
		else
			i += env_key_lexer_type_get(tk, rd_line + i, *state);
	}
	else if (rd_line[i] == '>' || rd_line[i] == '<')
		i += identify_redirections(tk, rd_line, i, state);
	else if (rd_line[i] == '|')
		add_lexer_element_back(tk, create_new_lexer_element(rd_line + (i++), 1, PIPE, *state));
	else if (ft_isspace(rd_line[i]))
		add_lexer_element_back(tk, create_new_lexer_element(rd_line + (i++), 1, SPACE, *state));
	return (i);
}