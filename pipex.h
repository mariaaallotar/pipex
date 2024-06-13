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

char	**mod_split(char const *s, char c, char except);

typedef struct s_pipex
{
	int		argc
	char	*argv[]
	char	*envp[];
	int		infile_ok;
	int		pipe_fds[2];
	char	**paths;			//needs to be freed
	char	**commands;
	char	***commands_w_flags;
}	t_pipex;

#endif