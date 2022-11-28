#include "../minishell.h"
int	ft_echo(t_one_cmd *cmd, t_one_element *head, char **env)
{
	int		i;
	int		j;
	bool	b;

	b = false;
	i = check_echo_args(cmd->args);
	if (i <= 1)
		i = 1;
	else
		b = true;
	while (cmd->args[i])
	{
		j = 0;
		j = ft_strjoin_echo(&cmd,
				search_key_all_env(head, cmd->args[i], env), env, i);
		write(STDOUT_FILENO, cmd->args[i], ft_strlen(cmd->args[i]));
		add_number_to(&i, j);
		if (cmd->args[i])
			write(STDOUT_FILENO, " ", 1);
	}
	if (!b)
		write(STDOUT_FILENO, "\n", 1);
	g_data.exit_status = EXIT_SUCCESS;
	return (EXIT_SUCCESS);
}
