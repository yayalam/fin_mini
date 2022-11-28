/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylambark <ylambark@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/26 02:44:24 by ylambark          #+#    #+#             */
/*   Updated: 2022/11/26 07:06:31 by ylambark         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	redirin_ex(t_one_red_element *redir, int *fd_in)
{
	if (access(redir->arg, F_OK) == 0)
	{
		close(*fd_in);
		*fd_in = open(redir->arg, O_RDONLY, 0666);
	}
	else
	{
		*fd_in = -1;
		write(2, "minishell: ", 11);
		ft_perror(redir->arg, ": No such file or directory");
	}
}

void	redir_ex(t_head_redir *head, t_fd *fd)
{
	t_one_red_element	*tmp;

	tmp = head->head;
	while (tmp)
	{
		if (tmp->type == IN_REDIR)
			redirin_ex(tmp, &fd->in);
		else if (tmp->type == OUT_REDIR)
		{
			close(fd->out);
			fd->out = open(tmp->arg, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		}
		else if (tmp->type == DOUBLE_OUT)
		{
			close(fd->out);
			fd->out = open(tmp->arg, O_WRONLY | O_CREAT | O_APPEND, 0666);
		}
		else if (tmp->type == HERE_DOC)
		{
			close(fd->in);
			fd->in = open(tmp->arg, O_RDONLY, 0666);
		}
		tmp = tmp->next;
	}
}
