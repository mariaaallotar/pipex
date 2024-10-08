/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_processes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 11:16:21 by maheleni          #+#    #+#             */
/*   Updated: 2024/10/08 11:00:08 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	execute(char *cmd, char *envp[])
{
	char	**cmd_array;
	char	*path;

	if (*cmd == '\0')
	{
		errno = 127;
		cmd_error("");
	}
	cmd_array = mod_split(cmd, ' ', '\'');
	path = get_path(cmd_array[0], envp);
	if (path == NULL)
	{
		free_str_arr(cmd_array);
		cmd_error(cmd);
	}
	if (execve(path, cmd_array, envp) == -1)
	{
		free(path);
		free_str_arr(cmd_array);
		error(NULL);
	}
}

void	first_child_process(char *argv[], char *envp[], int fds[])
{
	int	infile;

	infile = open(argv[1], O_RDONLY);
	if (infile == -1)
	{
		//this needs to close pipe
		error(argv[1]);
	}
	dup2(infile, STDIN_FILENO);
	close(infile);
	dup2(fds[1], STDOUT_FILENO);
	close(fds[1]);
	close(fds[0]);
	execute(argv[2], envp);
}

void	last_child_process(char *argv[], char *envp[], int fds[])
{
	char	*outfile_name;
	int		outfile;

	outfile_name = argv[4];
	outfile = open(outfile_name, O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (outfile == -1)
	{
		//this needs to close pipe
		error(outfile_name);
	}
	dup2(outfile, STDOUT_FILENO);
	close(outfile);
	dup2(fds[0], STDIN_FILENO);
	close(fds[0]);
	close(fds[1]);
	execute(argv[3], envp);
}
