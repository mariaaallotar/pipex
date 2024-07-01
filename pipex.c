/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 10:54:16 by maheleni          #+#    #+#             */
/*   Updated: 2024/06/27 10:54:18 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error()
{
	perror(NULL);
	exit(errno);
}

static char *find_path(char *cmd, char *envp[])
{
	char	**env_paths;
    char    *path;
    char    *cmd_path;
	int		i;

    if (access(cmd, F_OK) == 0)
    {
        if (access(cmd, X_OK) == 0)
            return (cmd);
        else
            return (NULL);
    }
	i = 0;
	while (envp[i] != NULL && ft_strnstr(envp[i], "PATH=", 5) == NULL)
		i++;
	if (envp[i] == NULL)
	{
        errno = ENOENT;
        return (NULL);
	}
	env_paths = ft_split((const char *) (envp[i] + 5), ':');
	i = 0;
	while (env_paths[i])
	{
		path = ft_strjoin(env_paths[i], "/");
		cmd_path = ft_strjoin(path, cmd);
		free(path);
		if (access(cmd_path, F_OK) == 0)
			return (cmd_path);
		free(cmd_path);
		i++;
	}
    ft_putstr_fd("Command not found\n", 2);
	return (NULL);
}

void    execute(char *cmd, char *envp[])
{
	char	**cmd_array;
	char	*path;
    int 	i;
	
    if (*cmd == '\0')
    {
        ft_putstr_fd("Command not found\n", 2);
        error();
    }
	cmd_array = mod_split(cmd, ' ', '\'');
	path = find_path(cmd_array[0], envp);
    i = 0;
	if (path == NULL)
	{
		while (cmd_array[i])
        {
			free(cmd_array[i]);
            i++;
        }
		free(cmd_array);
		error();
	}
	if (execve(path, cmd_array, envp) == -1)
    {
		error();
    }
}

void child_process(char *argv[], char *envp[], int fds[])
{
    int infile;

    infile = open(argv[1], O_RDONLY);
    if (infile == -1)
    {
        perror(NULL);
        exit(errno);
    }
    dup2(infile, STDIN_FILENO);
    close(infile);
	dup2(fds[1], STDOUT_FILENO);
	close(fds[1]);
    close(fds[0]);
    execute(argv[2], envp);
}

void	parent_process(char *argv[], char *envp[], int fds[], int outfile)
{
	if (outfile == -1)
		exit(1);
    dup2(outfile, STDOUT_FILENO);
	close(outfile);
    dup2(fds[0], STDIN_FILENO);
    close(fds[0]);
    close(fds[1]);
    execute(argv[3], envp);
}

int main(int argc, char *argv[], char *envp[])
{
    int outfile;
    int fds[2];
    int pid;
    int status;

    if (argc == 5)
    {
        outfile = open(argv[argc - 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
        if (outfile == -1)
            perror(NULL);
        if (pipe(fds) == -1)
            error();
        pid = fork();
        if (pid == -1)
            error();
        else if (pid == 0)
            child_process(argv, envp, fds);
        wait(&status);
        parent_process(argv, envp, fds, outfile);
        return (EXIT_SUCCESS);
    }
    ft_putstr_fd("Usage: ./pipex <file1> <cmd1> <cmd2> <file2>\n", 1);
    ft_putstr_fd("Ex: ./pipex infile.txt \"ls -l\" \"wc\" outfile.txt\n", 1);
    return (EXIT_SUCCESS);
}
