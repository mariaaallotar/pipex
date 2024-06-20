/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 11:37:20 by maheleni          #+#    #+#             */
/*   Updated: 2024/06/18 11:37:22 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

//TODO: remove this inclusion
#include <stdio.h>

static int	find_path(char *command, char **env_paths, t_pipex *s_pipex, int index)
{
	char	*path;
	char	*command_path;
	int		i;

	i = 0;
	while (env_paths[i] != NULL)
	{
		path = ft_strjoin(env_paths[i], "/");
		if (path == NULL)
		{
			//TODO; handle error
		}
		command_path = ft_strjoin(path, command);
		if (command_path == NULL)
		{
			//TODO; handle error
		}
		free(path);
		if (access(command_path, F_OK) == 0)
		{
			s_pipex->paths[index] = command_path;
			//free_everything(paths);		//needs to be implemented to free every string that this points to
			return (1);
		}
		free(command_path);
		i++;
	}
	return (-1);
}

/*
* Returns 1 if all commands are paths
* 0 if even one is not
*/
static int	all_commands_paths(t_pipex *s_pipex)
{
	int		i;
	char	**paths;

	i = 0;
	paths = s_pipex->paths;
	while (s_pipex->cmds[i] != NULL)
	{
		if (access(paths[i], F_OK) != 0 || ft_strchr(paths[i], '/') == NULL)	//have both or just '/'?
			return (0);
		i++;
	}
	return (1);
}

static int	parse_paths(t_pipex *s_pipex)
{
	char	**envp;
	char	**env_paths;
	int		i;

	if (all_commands_paths(s_pipex))
		return (1);
	i = 0;
	envp = s_pipex->envp;
	while (envp[i] != NULL && ft_strnstr(envp[i], "PATH=", 5) == NULL)
		i++;
	if (envp[i] == NULL)	//no PATH found
	{
		//TODO: handle error
		return (-1);
	}
	env_paths = ft_split((const char *) (envp[i] + 5), ':');
	i = 0;
	while (s_pipex->cmds[i] != NULL)
	{
		if (ft_strchr(s_pipex->cmds[i], '/') != NULL)
			continue ;
		else if (find_path(s_pipex->cmds[i], env_paths, s_pipex, i) == -1)
		{
			//TODO: handle error: path to command not found
		}
		i++;
	}
	return (1);
}

/*
* parses trhough all commands given as arguments and save them in a two-
* dimensional array in the struct
* if the command happens to be a path to a program we save it as the path
*/
static int	parse_commands(t_pipex *s_pipex)
{
	int		i;

	i = 0;
	while (i < s_pipex->argc - 3)
	{
		s_pipex->cmds_w_flags[i] = mod_split(s_pipex->argv[i + 2], ' ', '\'');
		if (s_pipex->cmds_w_flags[i] == NULL)
		{
			//handle error: malloc failed
		}
		if (access(s_pipex->cmds_w_flags[i][0], F_OK) == 0)
			s_pipex->paths[i] = s_pipex->cmds_w_flags[i][0];
		else if (ft_strchr(s_pipex->cmds_w_flags[i][0], '/') != NULL)
			s_pipex->paths[i] = s_pipex->cmds_w_flags[i][0];
		s_pipex->cmds[i] = s_pipex->cmds_w_flags[i][0];
		i++;
	}
	return (1);
}

static void print_paths(t_pipex *s_pipex)
{
	int i;

	i = 0;
	printf("The path to every command:\n\n");	//change to ft_printf
	while (s_pipex->paths[i] != NULL)
	{
		printf("%s\n", s_pipex->paths[i]); //change to ft_printf
		i++;
	}
	printf("\n"); //change to ft_printf
}

static void print_commands(t_pipex *s_pipex)
{
	int i;
	int j;

	i = 0;
	printf("All commands and all its flags on seperate lines:\n\n");
	printf("First command and its flags:\n");
	while (s_pipex->cmds_w_flags[i] != NULL)
	{
		if (i != 0)
			printf("Next command and its flags:\n");
		j = 0;
		while (s_pipex->cmds_w_flags[i][j] != NULL)
		{
			printf("%s\n", s_pipex->cmds_w_flags[i][j]);
			j++;
		}
		i++;
	}
	printf("\n");
}

/*
* Checks that infile exists and we have read permission
* Calls for functons to parse commads and paths
*/
int	parse_args(t_pipex *s_pipex)
{
	if (access(s_pipex->argv[1], F_OK) == -1)
	{
		s_pipex->infile_ok = 0;
		//handle error: no such file or directory 
	}
	if (access(s_pipex->argv[1], R_OK) == -1)
	{
		s_pipex->infile_ok = 0;
		//handle error: read permission for infile denied
	}
	if (parse_commands(s_pipex) == -1)
	{
		//TODO: handle error
	}

	print_commands(s_pipex); //only for debugging

	if (parse_paths(s_pipex) == -1)
	{
		//TODO: handle error
	}

	print_paths(s_pipex); //only for debugging
	return (1);
}
