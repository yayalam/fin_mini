#include "../../minishell.h"

int	check_special_char(char c)
{
	return (c == '\'' || c == '\"' || c == '<' || c == '>' || c == '|'
		|| c == '$' || ft_isspace(c) || c == '\n' || c == '\0');
}

int	ft_perror(char *msg, char *reason)
{
	write(STDERR_FILENO, msg, ft_strlen(msg));
	if (reason)
		write(STDERR_FILENO, reason, ft_strlen(reason));
	write(STDERR_FILENO, "\n", 1);
	return (EXIT_FAILURE);
}

int	ft_puterr(char *cmd, char *reason, char *msg, int err_num)
{
	write(STDERR_FILENO, "minishell: ", ft_strlen("minishell: "));
	write(STDERR_FILENO, cmd, ft_strlen(cmd));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, reason, ft_strlen(reason));
	write(STDERR_FILENO, ": ", 2);
	if (!msg)
		perror("");
	else
		printf("%s\n", msg);
	g_data.exit_status = err_num;
	return (err_num);
}