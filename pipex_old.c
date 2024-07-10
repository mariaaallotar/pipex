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

void    cmd_error(char *str)
{
	// dup2(STDERR_FILENO, STDOUT_FILENO);
	// if (errno == 127)
	// {
	// 	ft_printf("Command not found: %s\n", str);
	// 	exit(errno);
	// }
	// else
	// 	ft_printf("%s: %s\n", strerror(errno), str);
	// if (errno == EACCES || errno == EISDIR)
	// {
	// 	exit(126);
	// }
	// else if (ft_strchr(str, '/') != NULL)
	// {
	// 	exit (127);
	// }
	// exit(127);
}

void	error(char *str)
{
	// dup2(STDERR_FILENO, STDOUT_FILENO);
	// if (errno == 127)
	// {
	// 	ft_printf("Command not found: %s\n", str);
	// 	exit(errno);
	// }
	// else
	// 	ft_printf("%s: %s\n", strerror(errno), str);
	// if (errno == EACCES || errno == EISDIR)
	// {
	// 	exit(126);
	// }
	// else if (ft_strchr(str, '/') != NULL)
	// {
	// 	exit (127);
	// }
	// exit(1);
}

void	free_str_arr(char **str_arr)
{
	// int	i;

	// i = 0;
	// while(str_arr[i] != NULL)
	// {
	// 	free(str_arr[i]);
	// 	i++;
	// }
	// free(str_arr);
}

int is_dir(char *str)
{
	// while(*str != '\0')
	// {
	//     str++;
	// }
	// str--;
	// if (*str == '/')
	//     return (1);
	// return (0);
}

static char *get_envp_path(char *envp[])
{
	// int i;

	// i = 0;
	// while (envp[i] != NULL && ft_strnstr(envp[i], "PATH=", 5) == NULL)
	// 	i++;
	// if (envp[i] == NULL)
	// {
	// 	errno = ENOENT;
	// 	return (NULL);
	// }
	// return (envp[i]);
}

static char *find_path(char *cmd, char *envp[])
{
	// char    *envp_path;
	// char	**env_paths;
	// char    *path;
	// char    *cmd_path;
	// int		i;

	// if (cmd == NULL)
	// {
	//     errno = 127;
	//     return (NULL);
	// }
	// if (access(cmd, F_OK) == 0)
	// {
	//     if (is_dir(cmd))
	//         errno = EISDIR;
	//     else if (access(cmd, X_OK) == 0)
	//         return (cmd);
	//     return (NULL);
	// }
	// if (ft_strchr(cmd, '/') != NULL)
	// {
	//     errno = ENOENT;
	//     return (NULL);
	// }
	// envp_path = get_envp_path(envp);
	// if (envp_path == NULL)
	// {
	//     errno = ENOENT;
	//     return (NULL);
	// }
	// env_paths = ft_split((const char *) (envp_path + 5), ':');
	// i = 0;
	// while (env_paths[i])
	// {
	// 	path = ft_strjoin(env_paths[i], "/");
	// 	cmd_path = ft_strjoin(path, cmd);
	// 	free(path);
	// 	if (access(cmd_path, F_OK) == 0)
	//     {
	//         free_str_arr(env_paths);
	// 		return (cmd_path);
	//     }
	// 	free(cmd_path);
	// 	i++;
	// }
	// errno = 127;
	// free_str_arr(env_paths);
	// return (NULL);
}

void    execute(char *cmd, char *envp[])
{
	// char	**cmd_array;
	// char	*path;
	
	// if (*cmd == '\0')
	// {
	// 	errno = 127;
	//     cmd_error("");
	// }
	// cmd_array = mod_split(cmd, ' ', '\'');
	// path = find_path(cmd_array[0], envp);
	// if (path == NULL)
	// {
	// 	free_str_arr(cmd_array);
	// 	cmd_error(cmd);
	// }
	// if (execve(path, cmd_array, envp) == -1)
	// {
	// 	free(path);
	// 	free_str_arr(cmd_array);
	// 	error(NULL);
	// }
}

void child_process(char *argv[], char *envp[], int fds[])
{
	int infile;

	// infile = open(argv[1], O_RDONLY);
	// if (infile == -1)
	// {
	//     error(argv[1]);
	// }
	// dup2(infile, STDIN_FILENO);
	// close(infile);
	// dup2(fds[1], STDOUT_FILENO);
	// close(fds[1]);
	// close(fds[0]);
	// execute(argv[2], envp);
}

void	parent_process(char *argv[], char *envp[], int fds[], int outfile)
{
	// if (outfile == -1)
	// 	exit(1);
	// dup2(outfile, STDOUT_FILENO);
	// close(outfile);
	// dup2(fds[0], STDIN_FILENO);
	// close(fds[0]);
	// close(fds[1]);
	// execute(argv[3], envp);
}

int main(int argc, char *argv[], char *envp[])
{
	int outfile;
	// int fds[2];
	// int pids[2];
	// int status;

	if (argc == 5)
	{
		// outfile = open(argv[argc - 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
		// if (outfile == -1)
		//     ft_printf("%s: %s\n", strerror(errno), argv[argc - 1]);
		// if (pipe(fds) == -1)
		//     error(NULL);
		// pids[0] = fork();
		// if (pids[0] == -1)
		//     error(NULL);
		// else if (pids[0] == 0)
		//     child_process(argv, envp, fds);
		// close(fds[1]);
		// pids[1] = fork();
		// if (pids[1] == -1)
		//     error(NULL);
		// else if (pids[1] == 0)
		//     parent_process(argv, envp, fds, outfile);
		// close(fds[0]);
		// waitpid(pids[0], &status, 0);
		// waitpid(pids[1], &status, 0);
		// if (WIFEXITED(status))
		// {
		//     exit (WEXITSTATUS(status));
		// }
		// exit (EXIT_FAILURE);
	}
	// ft_printf("Usage: ./pipex <file1> <cmd1> <cmd2> <file2>\n");
	// ft_printf("Ex: ./pipex infile.txt \"ls -l\" \"wc\" outfile.txt\n");
	// exit (EXIT_SUCCESS);
}
