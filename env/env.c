#include "../minishell.h"
int	ft_env(t_one_cmd *cmd, char **env)
{
	int	i;

	i = 0;
	if (!cmd->args[1])
	{
		while (env[i])
		{
			if (ft_strchr(env[i], '=') != -1)
				printf("%s\n", env[i]);
			i++;
		}
	}
	else
	{
		g_data.exit_status = EXIT_FAILURE;
		return (ft_perror("minishell: env: Too many arguments.", NULL));
	}
	return (EXIT_SUCCESS);
}
