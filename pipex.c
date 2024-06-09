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

int	parse_command(char *command, t_pipex *s_pipex)
{
	//command: split with space unless in single quotescfc 
	s_pipex->command_w_flags = mod_split(command, ' ', '\'');
	s_pipex->command = s_pipex->command_w_flags[0];
	return (1);
}

int	parse_path(char *envp[], t_pipex *s_pipex)
{
	char	**paths;
	int		i;
	char	*command_path;

	//pathname: split env with : and call access with F_OK, get the one that return 0
	i = 0;
	while (ft_strnstr(envp[i], "PATH=", 5) == NULL) //what happens if there for some reason is not a PATH?
	{
		i++;
	}
	paths = ft_split((const char *) (envp[i] + 5), ':');
	i = 0;
	while (paths[i] != NULL)
	{
		command_path = ft_strjoin(paths[i], s_pipex->command);
		if (access(command_path, F_OK) == 0)
		{
			s_pipex->path = command_path;
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
	parse_command(argv[2], &s_pipex);

	int i = 0;
	while (s_pipex.command_w_flags[i] != NULL)
	{
		printf("%s\n", s_pipex.command_w_flags[i]);
		i++;
	}

	parse_path(envp, &s_pipex);
	printf("%s\n", s_pipex.path);
}
