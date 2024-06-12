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

//TODO: check errors
int	create_pipe(t_pipex	*s_pipex, char *infile, char *outfile)
{
	int	infile_fd;
	int	outfile_fd;

	if (pipe(s_pipex->pipe_fds) < 0)
	{
		//TODO: handle error
	}
	infile_fd = open(infile, O_RDONLY);
	if (infile_fd == -1)
	{
		//handle error
	}
	dup2(stdin, infile_fd);
	close(stdin);
	dup2(stdout, s_pipex->pipe_fds[1]);
	close(stdout);
	outfile_fd = open(outfile, O_WRONLY | O_CREAT, 0644); //check this and make more clear?
	if (outfile_fd == -1)
	{
		//handle error
	}
	dup2(stdin, infile_fd);
	close(stdin);
	dup2(stdout, s_pipex->pipe_fds[1]);
	close(stdout);
	return (1);
}

int	parse_command(char *command, t_pipex *s_pipex)
{
	s_pipex->command_w_flags = mod_split(command, ' ', '\'');
	if (s_pipex->command_w_flags == NULL)
		return (-1);
	if (access(s_pipex->command_w_flags[0], X_OK) == 0)
		s_pipex->path = s_pipex->command_w_flags[0]
	s_pipex->command = s_pipex->command_w_flags[0];
	return (1);
}

int	parse_path(char *envp[], t_pipex *s_pipex)
{
	char	**paths;
	char	*command_path;
	char	*path;
	int		i;

	if (s_pipe->path != NULL)
		return (1);
	i = 0;
	while (envp[i] != NULL && ft_strnstr(envp[i], "PATH=", 5) == NULL)
		i++;
	if (envp[i] != NULL)
	{
		//TODO: handle error
		return (-1);
	}
	paths = ft_split((const char *) (envp[i] + 5), ':');
	i = 0;
	while (paths[i] != NULL)
	{
		path = ft_strjoin(paths[i], "/");
		command_path = ft_strjoin(path, s_pipex->command);
		free(path);
		if (access(command_path, X_OK) == 0)
		{
			s_pipex->path = command_path;
			//free_everything(paths);		//needs to be implemented to free every string that this points to
			//handle error
			return (-1);
		}
		free(command_path);
		i++;
	}
	return (-1);
}

static void print_command(t_pipex *s_pipex)
{
	int i

	i = 0;
	printf("Command and all flags on seperate lines:\n\n");	//change to ft_printf
	while (s_pipex.command_w_flags[i] != NULL)
	{
		printf("%s\n", s_pipex.command_w_flags[i]); //change to ft_printf
		i++;
	}
	printf("\n"); //change to ft_printf
}

int	check_args(int argc, char *argv[], char *envp[], t_pipex *s_pipex)
{
	if (argc != 5)
	{
		printf("This progam needs exactly four arguments."); //change to ft_printf
		return (0);
	}
	if (access(argv[1], R_OK) == -1)
	{
		//TODO: handle error
		//no need to free anything
	}
	if (parse_command(argv[2], &s_pipex) == -1)
	{
		//TODO: handle error
		//no need to free anything
	}
	print_command(&s_pipex); //only for debugging
	if (parse_path(envp, &s_pipex) == -1)
	{
		//TODO: handle error
	}

	printf("Path to that command:\n");	//only for debugging
	printf("%s\n", s_pipex.path);		//only for debugging
}

//TODO: remove this inclusion
#include <stdio.h>

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	s_pipex;
	int		ret_value;

	ret_vlaue = check_args(argc, argv, envp, &s_pipex);
	if ( ret_value == -1)
	{
		//handle exit?
	}
	ret_value = pipe(s_pipex.pipe_fds);
	if ( ret_value == -1)
	{
		//handle exit?
	}
}
