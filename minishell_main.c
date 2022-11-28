#include "minishell.h"

void	init_global_var(t_data *data)
{
	data->exit_status = 0;
	data->which = 0;
	data->pid = 0;
	data->tree = NULL;
	data->ev = NULL;
	data->alloc = 0;
}

int	main(int c, char **v, char **env)
{
	(void)v;
	if (c != 1 || !*env)
		return (1);
	init_global_var(&g_data);
	init_sigaction(&g_data);
	mini_shell_executor(env);
}
