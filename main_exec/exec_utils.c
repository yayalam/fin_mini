#include "../minishell.h"

void	swap_fd_var(int *old_fd, int new_fd)
{
	*old_fd = new_fd;
}

void	fd_handler_builtin(t_one_cmd *my_cmd)
{
	if (my_cmd->fd.in != 0)
	{
		dup2(my_cmd->fd.in, STDIN_FILENO);
		close(my_cmd->fd.in);
	}
	if (my_cmd->fd.out != 1)
	{
		dup2(my_cmd->fd.out, STDOUT_FILENO);
		close(my_cmd->fd.out);
	}
}

void	fd_handler_execve(t_one_cmd *my_cmd, int fd[2])
{
	if (my_cmd->fd.in != 0)
	{
		dup2(my_cmd->fd.in, STDIN_FILENO);
		close(my_cmd->fd.in);
		if (fd[0] != 0)
			close(fd[0]);
	}
	if (my_cmd->fd.out != 1)
	{
		dup2(my_cmd->fd.out, STDOUT_FILENO);
		close(my_cmd->fd.out);
		if (fd[1] != 1)
			close(fd[1]);
	}
}

void	check_last_pid(int pid, int counter, int cmds_number)
{
	int	status;

	status = 0;
	if (counter == cmds_number)
	{
		waitpid(pid, &status, 0);
		if (!g_data.which)
			g_data.exit_status = WEXITSTATUS(status);
	}
}