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

static void first_child_pipex(t_pipex *s_pipex)
{
	int infile;

	printf("In first child\n");
	infile = open(s_pipex->argv[1], O_RDONLY);
	dup2(infile, STDIN_FILENO);
	dup2(s_pipex->pipe_fds[1], STDOUT_FILENO);
    // close();     //what to close?
	int i = 0;
	while(s_pipex->cmds_w_flags[0][i] != NULL)
	{
		printf("%s\n", s_pipex->cmds_w_flags[0][i]);
		i++;
	}
    if (execve(s_pipex->paths[0], (char * const*)s_pipex->cmds_w_flags[0], s_pipex->envp) == -1)
	{
		perror("execve");
	}
}

static void middle_child_pipex(t_pipex *s_pipex, int i)
{
	printf("In middle child\n");
	dup2(s_pipex->read_from_fd, STDIN_FILENO);
	dup2(s_pipex->pipe_fds[1], STDOUT_FILENO);
    // close();     //what to close?
    execve(s_pipex->paths[i], (char * const*)s_pipex->cmds_w_flags[i], s_pipex->envp);
}

static void last_child_pipex(t_pipex *s_pipex, int i)
{
	int		outfile;
	int		argc;
	char	*outfile_name;

	printf("In last child\n");
	argc = s_pipex->argc;
	outfile_name = s_pipex->argv[argc - 1];
	outfile = open(outfile_name, O_CREAT | O_WRONLY, 0644);	//check that the permissions are correct
    dup2(s_pipex->read_from_fd, STDIN_FILENO);
	dup2(outfile, STDOUT_FILENO);
    // close();     //what to close?
    execve(s_pipex->paths[i], (char * const*)s_pipex->cmds_w_flags[i], s_pipex->envp);
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
				first_child_pipex(s_pipex);
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
