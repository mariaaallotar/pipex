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

int	parse_args(char *command, char *envp[], t_pipex *s_pipex)
{
	char	**paths;
	int		i;
	//pathname: split env with : and call access with F_OK, get the one that return 0
	i = 0;
	while (ft_strcmp(envp[i], "PATH=", 5) == NULL)
	{
		i++;
	}
	paths = ft_split(envp[i], ":");
	i = 0;
	while (paths[i] != NULL)
	{
		if (access(paths[i], F_OK))
		{
			s_pipex.path = paths[i];
			break ;
		}
		i++;
	}
	//command: split with space unless in single quotes
}

int	main(int argc, char *argv[], char *envp[])
{
	t_pipex	s_pipex;

	if (argc != 5)
	{
		ft_printf("This progam needs exactly four arguments.");
		return (0);
	}
	parse_args(argv[1], envp, &s_pipex);
}
