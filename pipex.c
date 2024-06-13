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

int	pipex(int argc, char *argv[], char *envp[])
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
		pid = fork();
		if (pid == 0)
		{
			handle_child_processes();
			if (i == 0)
				first_child_pipex()
			else if (i < argc - 3 - 1)
				middle_child_pipex()
			else
				last_child_pipex();
		}
		free_struct;
		i++;
	}
	close(s_pipex.pipe_fds[0]);
	close(s_pipex.pipe_fds[1]);
	return (0);
}

int	parse_paths(t_pipex *s_pipex)
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

int	parse_commands(t_pipex *s_pipex)
{
	int	i;

	i = 0;
	while (i < s_pipex->argc - 3)
	{
		s_pipex->command_w_flags[i] = mod_split(s_pipex->argv[i + 2], ' ', '\'');
		if (s_pipex->command_w_flags[i] == NULL)
		{
			//handle error: malloc failed
		}
		if (access(s_pipex->command_w_flags[i][0], X_OK) == 0)
			s_pipex->paths[i] = s_pipex->command_w_flags[i][0];
		s_pipex->commands[i] = s_pipex->command_w_flags[i][0];
		i++;
	}
	return (1);
}

int	parse_args(t_pipex *s_pipex)
{
	if (access(argv[1], F_OK) == -1)
	{
		s_pipex->infile_ok = 0;
		//handle error: no such file or directory 
	}
	if (access(argv[1], R_OK) == -1)
	{
		s_pipex->infile_ok = 0;
		//handle error: read permission for infile denied
	}
	if (parse_commands(&s_pipex) == -1)
	{
		//TODO: handle error
	}
	// print_command(&s_pipex); //only for debugging
	if (parse_paths(&s_pipex) == -1)
	{
		//TODO: handle error
	}

	printf("Path to that command:\n");	//only for debugging
	printf("%s\n", s_pipex.path);		//only for debugging
}

void	init_s_pipex(int argc, char *argv[], char *envp[], t_pipex *s_pipex)
{
	s_pipex->argc = argc;
	s_pipex->argv = argv;
	s_pipex->envp = envp;
	s_pipex->infile_ok = 1;
	s_pipex->paths = NULL;			//needs to be freed
	s_pipex->commands = NULL;
	s_pipex->commands_w_flags = NULL;
}

//TODO: remove this inclusion
#include <stdio.h>

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	s_pipex;

	if (argc != 5)
	{
		printf("This progam needs exactly four arguments."); //change to ft_printf
		return (1);
	}
	init_s_pipex(argc, argv, envp, &s_pipex);
	parse_args(&s_pipex);
	return (pipex());
}
