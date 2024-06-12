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

int	parse_args(char *file, char *command, char *envp[], t_pipex *s_pipex)
{
	if (access(argv[1], R_OK) == -1)
	{
		//TODO: handle error
	}
	if (parse_command(command, &s_pipex) == -1)
	{
		//TODO: handle error
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
	int		pid;
	int		i;

	if (argc != 5)
	{
		printf("This progam needs exactly four arguments."); //change to ft_printf
		return (1);
	}
	if (access(argv[1], R_OK) == -1)
	{
		//handle error
	}
	if (pipe(s_pipex.pipe_fds) == -1)
	{
		//handle error
	}
	i = 0;
	while (i < argc -3)
	{
		pid = fork();
		if (pid == 0)
		{
			if (i == 0)
				parse_args(argv[1], argv[2], envp, &s_pipex);
			else
				parse_args(argv[4], argv[3], envp, &s_pipex);
		}
		free_struct;
		i++;
	}
	close(s_pipex.pipe_fds[0]);
	close(s_pipex.pipe_fds[1]);
}
