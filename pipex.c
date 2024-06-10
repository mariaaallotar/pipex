/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 15:44:01 by maheleni          #+#    #+#             */
/*   Updated: 2024/06/06 15:44:03 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	create_pipe(t_pipex	*s_pipex, char *infile, char *outfile)
{
	int	infile_fd;
	int	outfile_fd;

	if (pipe(s_pipex->pipe_fds) < 0)
	{
		//TODO: handle error
	}
	infile_fd = open(infile, O_RDONLY);
	dup2(s_pipex->pipe_fds[0], infile_fd);
	close(s_pipex->pipe_fds[0]);
	close(infile_fd);	 //should this be closed?
	//TODO: check that outfile exists, if not create one
	outfile_fd = open(outfile, O_RDWR);
	dup2(s_pipex->pipe_fds[1], outfile_fd);
	close(s_pipex->pipe_fds[1]);
	close(outfile_fd);	//should this be closed?
	return (1);
}

int	parse_command(char *command, t_pipex *s_pipex)
{
	//what happens if command is a path?

	s_pipex->command_w_flags = mod_split(command, ' ', '\'');
	if (s_pipex->command_w_flags == NULL)
		return (-1);
	s_pipex->command = s_pipex->command_w_flags[0];
	return (1);
}

int	parse_path(char *envp[], t_pipex *s_pipex)	//25 lines
{
	char	**paths;
	char	*command_path;
	char	*path;
	int		i;

	//what happens if there is no PATH= variable in envp
	i = 0;
	while (ft_strnstr(envp[i], "PATH=", 5) == NULL)
		i++;
	paths = ft_split((const char *) (envp[i] + 5), ':');
	i = 0;
	while (paths[i] != NULL)
	{
		path = ft_strjoin(paths[i], "/");
		command_path = ft_strjoin(path, s_pipex->command);
		free(path);
		if (access(command_path, F_OK) == 0)
		{
			s_pipex->path = command_path;
			//free_everything(paths);		//needs to be implemented to free every string that this points to
			return (1);
		}
		free(command_path);
		i++;
	}
	return (-1);
}

//TODO: remove this inclusion
#include <stdio.h>

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	s_pipex;

	if (argc != 5)
	{
		printf("This progam needs exactly four arguments."); //change to ft_printf
		return (0);
	}
	if (parse_command(argv[2], &s_pipex) == -1)
	{
		//TODO: handle error
		//no need to free anything
	}

	// int i = 0;
	// printf("Command and all flags on seperate lines:\n\n");
	// while (s_pipex.command_w_flags[i] != NULL)
	// {
	// 	printf("%s\n", s_pipex.command_w_flags[i]);
	// 	i++;
	// }
	// printf("\n");

	if (parse_path(envp, &s_pipex))
	{
		//TODO: hadle error
		//free 
	}

	printf("Path to that command:\n");
	printf("%s\n", s_pipex.path);

	create_pipe(&s_pipex, argv[1], argv[4]);
}
