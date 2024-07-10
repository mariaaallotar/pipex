#include "pipex.h"

void    cmd_error(char *str)
{
	if (errno == 127)
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(errno);
	}
	else
		perror(str);
	if (errno == EACCES || errno == EISDIR)
	{
		exit(126);
	}
	else if (ft_strchr(str, '/') != NULL)
	{
		exit (127);
	}
	exit(127);
}

void	error(char *str)
{
	perror(str);
	if (errno == EISDIR)
	{
		exit(126);
	}
	else if (ft_strchr(str, '/') != NULL)
	{
		exit (127);
	}
	exit(1);
}

int is_dir(char *str)
{
	while(*str != '\0')
	{
		str++;
	}
	str--;
	if (*str == '/')
		return (1);
	return (0);
}

void	free_str_arr(char **str_arr)
{
	int	i;

	i = 0;
	while(str_arr[i] != NULL)
	{
		free(str_arr[i]);
		i++;
	}
	free(str_arr);
}

char *get_envp_path(char *envp[])
{
	int i;

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

char	*find_command_path(char *cmd, char *envp_path)
{
	char	**env_paths;
	char    *path;
	char    *cmd_path;
	int		i;

	env_paths = ft_split((const char *) (envp_path + 5), ':');
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

char	*find_path(char *cmd, char *envp[])
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

void    execute(char *cmd, char *envp[])
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
	int infile;

	infile = open(argv[1], O_RDONLY);
	if (infile == -1)
	{
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
		error(outfile_name);
	dup2(outfile, STDOUT_FILENO);
	close(outfile);
	dup2(fds[0], STDIN_FILENO);
	close(fds[0]);
	close(fds[1]);
	execute(argv[3], envp);
}

int	pipex(int argc, char *argv[], char *envp[])
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

int main(int argc, char *argv[], char *envp[])
{
	int	i;
	int	status;

	if (argc == 5)
	{
		status = pipex(argc, argv, envp);
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
