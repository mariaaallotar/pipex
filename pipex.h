/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 10:33:21 by maheleni          #+#    #+#             */
/*   Updated: 2024/06/07 10:33:23 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "libft/libft.h"

typedef struct s_pipex
{
	int		argc;
	char	**argv;
	char	**envp;
	int		infile_ok;
	int		pipe_fds[2];
	int		read_from_fd;
	char	**paths;			//needs to be freed
	char	**cmds;
	char	***cmds_w_flags;
}	t_pipex;

char	**mod_split(char const *s, char c, char except);
int		parse_args(t_pipex *s_pipex);

#endif