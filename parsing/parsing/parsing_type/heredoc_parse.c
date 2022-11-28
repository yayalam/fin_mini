#include "../../../minishell.h"

t_head_redir	*heredoc_parse_handler(t_head_redir *red, char *arg, char **env)
{	
	char	*tmp;
	int		fd;

	fd = open("/tmp/.minishell_tmp",
			O_RDWR | O_CREAT | O_APPEND | O_TRUNC, 0666);
	tmp = get_next_line(STDIN_FILENO);
	while (tmp)
	{
		if (ft_strncmp(tmp, arg, ft_strlen(arg)) == 0)
			break ;
		else
		{
			if (ft_strchr(tmp, '$') != -1)
				tmp = env_value_expand(tmp, env);
			write(fd, tmp, ft_strlen(tmp));
		}
		free(tmp);
		tmp = get_next_line(STDIN_FILENO);
	}
	free(arg);
	add_back_element_redir(red,
		creat_element_redir(ft_strdup("/tmp/.minishell_tmp"), HERE_DOC));
	close(fd);
	return (red);
}