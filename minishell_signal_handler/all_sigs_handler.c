#include "../minishell.h"

void	handle_sigaction(int sig, siginfo_t *tmp, void *p)
{
	(void) p;
	(void) tmp;
	if (sig == SIGINT)
	{
		if (g_data.shell_state != READING)
			return ;
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_data.exit_status = 1;
	}
}

void	init_sigaction(t_data *data)
{
	struct sigaction	sa;

	memset(&sa, 0, sizeof(sa));
	sa.sa_sigaction = &handle_sigaction;
	sa.sa_flags = 0;
	rl_catch_signals = 0;
	data->exit_status = 0;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGINT);
	sigaddset(&sa.sa_mask, SIGQUIT);
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}
