#include "../minishell.h"

int	ft_pwd(void)
{
	char	current[1024];
	char	*dir;

	dir = getcwd(current, sizeof(current));
	if (!dir)
	{
		perror("minishell: pwd: ");
		g_data.exit_status = EXIT_FAILURE;
		return (-1);
	}
	printf("%s\n", dir);
	g_data.exit_status = EXIT_SUCCESS;
	return (EXIT_SUCCESS);
}
