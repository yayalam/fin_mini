#include "../minishell.h"
int	counter_args_exit(char **arg)
{
	int	i;

	i = 0;
	while (arg[i])
		i++;
	return (i);
}

int	check_exit_arg(char **arg)
{
	if (arg[0] && !arg[1])
	{
		parse_free(g_data.tree);
		exit(EXIT_SUCCESS);
	}
	if (counter_args_exit(arg) > 2)
	{
		parse_free(g_data.tree);
		printf("minishel: exit: too many arguments\n");
		g_data.exit_status = 1;
		exit (1);
	}
	if (!ft_isnum(arg[1]))
	{
		parse_free(g_data.tree);
		printf("exit: %s: numeric argument required\n", arg[1]);
		g_data.exit_status = 255;
		exit(255);
	}
	return (0);
}
