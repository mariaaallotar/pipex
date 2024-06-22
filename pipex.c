/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 14:42:19 by maheleni          #+#    #+#             */
/*   Updated: 2024/06/20 14:42:21 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//TODO: remove this inclusion
#include <stdio.h>

static void first_child_pipex(t_pipex *s_pipex, int i)
{
	int infile;

	infile = open(s_pipex->argv[1], O_RDONLY);
    dup2(STDIN_FILENO, infile);
    dup2(STDOUT_FILENO, s_pipex->pipe_fds[1]);
    // close();     //what to close?
    execve(s_pipex->paths[i], (const char *)s_pipex->cmds_w_flags[i], s_pipex->envp);
}

static void middle_child_pipex(t_pipex *s_pipex, int i)
{
    dup2(STDIN_FILENO, s_pipex->read_from_fd);
    dup2(STDOUT_FILENO, s_pipex->pipe_fds[1]);
    // close();     //what to close?
    execve(s_pipex->paths[i], (const char *)s_pipex->cmds_w_flags[i], s_pipex->envp);
}

static void last_child_pipex(t_pipex *s_pipex, int i)
{
	int	outfile;

	outfile = open(s_pipex->argv[s_pipex->argc - 1], O_WRONLY);	//should also create that file if it does not exist
    dup2(STDIN_FILENO, s_pipex->read_from_fd);
    dup2(STDOUT_FILENO, outfile);
    // close();     //what to close?
    execve(s_pipex->paths[i], (const char *)s_pipex->cmds_w_flags[i], s_pipex->envp);
}

int	pipex(t_pipex *s_pipex)
{
	int		pid;
	int		i;
	int		argc;

	argc = s_pipex->argc;
	i = 0;
	while (i < argc - 3)
	{
		if (i != 0)
			s_pipex->read_from_fd = dup(s_pipex->pipe_fds[0]);
		if (i != argc - 3 - 1)
		{
			if (pipe(s_pipex->pipe_fds) == -1)
			{
				//handle error: piping failed
			}
		}
		pid = fork();
		if (pid == 0)
		{
			if (i == 0)
				first_child_pipex(s_pipex, i);
			else if (i < argc - 3 - 1)
			{
				middle_child_pipex(s_pipex, i);
			}
			else
				last_child_pipex(s_pipex, i);
		}
		i++;
	}
	close(s_pipex->pipe_fds[0]);
	close(s_pipex->pipe_fds[1]);
    //free_struct;
	return (0);
}
