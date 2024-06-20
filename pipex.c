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

static void first_child_pipex(t_pipex s_pipex, int i)
{
    dup2(STDIN_FILENO, s_pipex->argv[1]);
    dup2(STDOUT_FILENO, s_pipex->fds[1]);
    // close();     //what to close?
    execve(s_pipex->paths[i], (const char)s_pipex->cmds_w_flags[i], s_pipex->envp);
}

static void middle_child_pipex(t_pipex s_pipex, int i)
{
    dup2(STDIN_FILENO, s_pipex->fds[0]);
    dup2(STDOUT_FILENO, fds[1]);
    // close();     //what to close?
    execve(s_pipex->paths[i], (const char)s_pipex->cmds_w_flags[i], s_pipex->envp);
}

int	pipex(t_pipex s_pipex)
{
	int		pid;
	int		i;

	if (pipe(s_pipex.pipe_fds) == -1)
	{
		//handle error: piping failed
	}
	i = 0;
	while (i < argc - 3)
	{
        s_pipex->read_from_fd = dup(s_pipex->fds[0]);
		pid = fork();
		if (pid == 0)
		{
			// handle_child_processes();    //what was I thinking here?
			if (i == 0)
				first_child_pipex(s_pipex, i)
			else if (i < argc - 3 - 1)
				middle_child_pipex(s_pipex, i)
			else
				last_child_pipex(s_pipex, i);
		}
		i++;
	}
	close(s_pipex.pipe_fds[0]);
	close(s_pipex.pipe_fds[1]);
    free_struct;
	return (0);
}
