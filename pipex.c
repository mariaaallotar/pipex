/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 12:51:07 by maheleni          #+#    #+#             */
/*   Updated: 2024/06/12 12:51:09 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//TODO: remove this inclusion
#include <stdio.h>

// int	pipex(int argc, char *argv[], char *envp[])
// {
// 	int		pid;
// 	int		i;

// 	if (pipe(s_pipex.pipe_fds) == -1)
// 	{
// 		//handle error: piping failed
// 	}
// 	i = 0;
// 	while (i < argc - 3)
// 	{
// 		pid = fork();
// 		if (pid == 0)
// 		{
// 			handle_child_processes();
// 			if (i == 0)
// 				first_child_pipex()
// 			else if (i < argc - 3 - 1)
// 				middle_child_pipex()
// 			else
// 				last_child_pipex();
// 		}
// 		free_struct;
// 		i++;
// 	}
// 	close(s_pipex.pipe_fds[0]);
// 	close(s_pipex.pipe_fds[1]);
// 	return (0);
// }

/*
* Initializes the struct used in pipex
*/
static void	init_s_pipex(int argc, char *argv[], char *envp[], t_pipex *s_pipex)
{
	s_pipex->argc = argc;
	s_pipex->argv = argv;
	s_pipex->envp = envp;
	s_pipex->infile_ok = 1;
	s_pipex->paths = (char **) malloc ((argc - 3) * sizeof(char *)); //needs to be freed
	if (s_pipex->paths == NULL)
	{
		//TODO: handle error: malloc failed
	}
	s_pipex->cmds = (char **) malloc ((argc - 3 + 1) * sizeof(char *));
	if (s_pipex->cmds == NULL)
	{
		//TODO: handle error: malloc failed
	}
	s_pipex->cmds[argc - 3] = NULL;
	s_pipex->cmds_w_flags = (char ***) malloc ((argc - 3 + 1) * sizeof(char *));
	if (s_pipex->cmds_w_flags == NULL)
	{
		//TODO: handle error: malloc failed
	}
	s_pipex->cmds_w_flags[argc - 3] = NULL;
}



int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	s_pipex;

	if (argc < 5)
	{
		printf("This progam needs four or more arguments."); //change to ft_printf
		return (1);
	}
	init_s_pipex(argc, argv, envp, &s_pipex);
	parse_args(&s_pipex);
	// return (pipex());
}
