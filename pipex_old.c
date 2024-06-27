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

	// printf("In first child-process\n");
	// printf("Infile ok? %d\n", s_pipex->infile_ok);
	infile = open(s_pipex->argv[1], O_RDONLY);
	if (infile == -1)
	{
		perror(NULL);
		//what chould the infile be? It needs to be changed to something, right?
	}
	else
		dup2(infile, STDIN_FILENO);
	dup2(s_pipex->pipe_fds[1], STDOUT_FILENO);
	close(infile);
	close(s_pipex->pipe_fds[1]);
	if (s_pipex->infile_ok)
    	execve(s_pipex->paths[0], (char * const*)s_pipex->cmds_w_flags[0], s_pipex->envp);
	else
		exit(0);
}

static void middle_child_pipex(t_pipex *s_pipex, int i)
{
	// printf("In middle child-process\n");
	dup2(s_pipex->read_from_fd, STDIN_FILENO);
	dup2(s_pipex->pipe_fds[1], STDOUT_FILENO);
    close(s_pipex->read_from_fd);
	close(s_pipex->pipe_fds[1]);	//are these the right ones to close?
    execve(s_pipex->paths[i], (char * const*)s_pipex->cmds_w_flags[i], s_pipex->envp);
}

static void last_child_pipex(t_pipex *s_pipex, int i)
{
	int		outfile;
	int		argc;
	char	*outfile_name;

	// printf("In last child-process\n");
	argc = s_pipex->argc;
	outfile_name = s_pipex->argv[argc - 1];
	if (ft_strncmp(outfile_name, "/dev/stdout", 11) != 0)
	{
		outfile = open(outfile_name, O_WRONLY | O_TRUNC | O_CREAT, 0644);
		if (outfile == -1)
		{
			exit(1);
		}
		dup2(outfile, STDOUT_FILENO);
		close(outfile);
	}
    dup2(s_pipex->read_from_fd, STDIN_FILENO);
    close(s_pipex->read_from_fd);
	perror("Error before last execve");
	if (execve(s_pipex->paths[i], (char * const*)s_pipex->cmds_w_flags[i], s_pipex->envp) == -1)
	{
		print("Errno in last child: %d\n", errno);
		exit(errno);
	}
}

void	pipex(t_pipex *s_pipex)
{
	int	pid;
	int	i;
	int	argc;
	int	exit_status;

	argc = s_pipex->argc;
	i = 0;
	while (i < argc - 3)
	{
		if (i != 0)
		{
			s_pipex->read_from_fd = dup(s_pipex->pipe_fds[0]);
			close(s_pipex->pipe_fds[0]);
			close(s_pipex->pipe_fds[1]);
		}
		if (i != argc - 3 - 1)
		{
			if (pipe(s_pipex->pipe_fds) == -1)
			{
				//handle error: piping failed
			}
		}
		else if (pid < 0)
        {
            // Handle error: fork failed
            perror(NULL);
            exit(EXIT_FAILURE);
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
		waitpid(pid, &exit_status, 0);
		if (i != 0)
			close(s_pipex->read_from_fd);
		i++;
	}
	//free_struct;
	if (WIFEXITED(exit_status))
	{
		perror("Last error in parent");
        exit (WEXITSTATUS(exit_status));
	}
	else
        exit (EXIT_FAILURE);
}
