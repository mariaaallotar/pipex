/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 11:05:16 by maheleni          #+#    #+#             */
/*   Updated: 2024/07/13 11:05:20 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_str_arr(char **str_arr)
{
	int	i;

	i = 0;
	while (str_arr[i] != NULL)
	{
		free(str_arr[i]);
		i++;
	}
	free(str_arr);
}

static int	pipex(char *argv[], char *envp[])
{
	int	fds[2];
	int	pids[2];
	int	status;
	int	i;

	if (pipe(fds) == -1)
		error(NULL);
	i = 0;
	while (i < 2)
	{
		pids[i] = fork();
		if (pids[i] == -1)
			error(NULL);
		if (pids[i] == 0 && i == 0)
			first_child_process(argv, envp, fds);
		else if (pids[i] == 0)
			last_child_process(argv, envp, fds);
		if (i == 0)
			close(fds[1]);
		i++;
	}
	close(fds[0]);
	waitpid(pids[0], &status, 0);
	waitpid(pids[1], &status, 0);
	return (status);
}

int	main(int argc, char *argv[], char *envp[])
{
	int	status;

	if (argc == 5)
	{
		status = pipex(argv, envp);
		if (WIFEXITED(status))
		{
			exit (WEXITSTATUS(status));
		}
		exit (EXIT_FAILURE);
	}
	ft_putstr_fd("Usage: ./pipex <file1> <cmd1> <cmd2> <file2>\n"
		"Ex: ./pipex infile.txt \"ls -l\" \"wc\" outfile.txt\n", 1);
	exit (EXIT_SUCCESS);
}
