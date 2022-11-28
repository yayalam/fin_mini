#include "../minishell.h"

int	*search_r_l(t_one_node_tree *ptr)
{
	return (&ptr->content->pipe->right->content-> \
		pipe->left->content->cmd->fd.out);
}

char	*get_path_cmd(char *cmd, char **env)
{
	char	**my_bin_paths;
	char	*all_paths_combined;
	char	*cmd_path;
	int		i;

	i = 0;
	all_paths_combined = search_element_array_env("PATH", env);
	my_bin_paths = ft_split(all_paths_combined, ':');
	cmd_path = ft_strdup("");
	if (!cmd_path)
		return (NULL);
	while (my_bin_paths[i])
	{
		cmd_path = ft_strjoin_directory(my_bin_paths[i], cmd);
		if (cmd_path)
		{
			if (access(cmd_path, F_OK) == 0)
				return (cmd_path);
			i++;
			free(cmd_path);
		}
	}
	printf("minishell: %s: command not found\n", cmd);
	return (NULL);
}

char	*check_dot_slach(char *cmd_to_check, char **env)
{
	char	*cmd_path;

	if (cmd_to_check[0] == '/')
	{
		if (opendir(cmd_to_check) != NULL)
			printf("minishell: %s: is a directory\n", cmd_to_check);
		else if (access(cmd_to_check, F_OK) == 0)
			return (cmd_to_check);
		else
			printf("minishell: %s: No such file or directory\n", cmd_to_check);
	}
	else if (cmd_to_check[0] == '.')
	{
		cmd_path = ft_strjoin_directory(search_element_array_env("PWD", env), cmd_to_check);
		if (access(cmd_path, F_OK) == 0)
			return (cmd_to_check);
		else
			printf("minishell: %s: No such file or directory\n", cmd_to_check);
	}
	return (NULL);
}

char	*get_cmd(char *command, char **env)
{
	char	*cmd_path;

	if (command[0] == '/' || command[0] == '.')
		cmd_path = check_dot_slach(command, env);
	else
		cmd_path = get_path_cmd(command, env);
	if (cmd_path)
		return (cmd_path);
	exit(EXIT_FAILURE);
	return (NULL);
}
