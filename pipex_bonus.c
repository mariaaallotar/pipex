

int main(int argc, char *argv[], char *envp[])
{
	int	outfile;
	int	pid;
	int	status;
	int	i;

	if (argc >= 5)
	{
		outfile = open(argv[argc - 1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
        if (outfile == -1)
            perror(NULL);
		i = 0;
		while (i < argc - 3)
		{
			if (pipe(fds) == -1)
				error();
			pid = fork();
			if (pid == -1)
				error();
			else if (pid == 0)
				child_process(argv, envp, fds, i);
			wait(&status);
		}
        parent_process(argv, envp, fds, outfile);
        return (EXIT_SUCCESS);
	}
}