#include "../../minishell.h"

t_lexer_lst	*lexer(char *rd_line)
{
	int				i;
	t_lexer_lst			*tokens;
	int	state;

	i = 0;
	state = GENERAL;
	tokens = NULL;
	tokens = lexer_lst_init(tokens);
	if (tokens)
	{
		while (rd_line[i])
		{
			i = identifie_line(tokens, rd_line, i, &state);
		}
	}
	free(rd_line);
	return (tokens);
}
