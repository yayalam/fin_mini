#include "../minishell.h"
int	ft_cd(t_one_cmd *cmd, char ***env)
{
	t_all_env		*tmp;
	char		cwd[1024];
	char		owd[1024];

	tmp = create_all_env_struct(*env);
	getcwd(owd, sizeof(owd));
	if (!cmd->args[1])
	{
		if (chdir(env_value_expand("$HOME", *env)) != 0)
			return (ft_puterr(cmd->args[0],
					env_value_expand("$HOME", *env), NULL, 1));
	}
	else
	{
		if (chdir(cmd->args[1]) != 0)
			return (ft_puterr(cmd->args[0], cmd->args[1], NULL, 1));
	}
	getcwd(cwd, sizeof(cwd));
	cd_dir_change_in_env(tmp, cwd, owd);
	*env = from_struct_to_array(tmp);
	g_data.exit_status = EXIT_SUCCESS;
	return (EXIT_SUCCESS);
}
