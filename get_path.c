/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 11:19:27 by maheleni          #+#    #+#             */
/*   Updated: 2024/07/13 11:19:28 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	is_dir(char *str)
{
	while (*str != '\0')
	{
		str++;
	}
	str--;
	if (*str == '/')
		return (1);
	return (0);
}

static char	*get_envp_path(char *envp[])
{
	int	i;

	i = 0;
	while (envp[i] != NULL && ft_strnstr(envp[i], "PATH=", 5) == NULL)
		i++;
	if (envp[i] == NULL)
	{
		errno = ENOENT;
		return (NULL);
	}
	return (envp[i]);
}

static char	*find_command_path(char *cmd, char *envp_path)
{
	char	**env_paths;
	char	*path;
	char	*cmd_path;
	int		i;

	env_paths = ft_split((const char *)(envp_path + 5), ':');
	i = 0;
	while (env_paths[i])
	{
		path = ft_strjoin(env_paths[i], "/");
		cmd_path = ft_strjoin(path, cmd);
		free(path);
		if (access(cmd_path, F_OK) == 0)
		{
			free_str_arr(env_paths);
			return (cmd_path);
		}
		free(cmd_path);
		i++;
	}
	errno = 127;
	free_str_arr(env_paths);
	return (NULL);
}

static char	*find_path(char *cmd, char *envp[])
{
	char	*envp_path;

	envp_path = get_envp_path(envp);
	if (envp_path == NULL)
	{
		errno = ENOENT;
		return (NULL);
	}
	return (find_command_path(cmd, envp_path));
}

char	*get_path(char *cmd, char *envp[])
{
	if (cmd == NULL)
	{
		errno = 127;
		return (NULL);
	}
	if (access(cmd, F_OK) == 0)
	{
		if (is_dir(cmd))
			errno = EISDIR;
		else if (access(cmd, X_OK) == 0)
			return (cmd);
		return (NULL);
	}
	if (ft_strchr(cmd, '/') != NULL)
	{
		errno = ENOENT;
		return (NULL);
	}
	return (find_path(cmd, envp));
}
