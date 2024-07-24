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

# include <stdio.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>
# include "libft/libft.h"

void	first_child_process(char *argv[], char *envp[], int fds[]);
void	last_child_process(char *argv[], char *envp[], int fds[]);
char	**mod_split(char const *s, char c, char except);
char	*get_path(char *cmd, char *envp[]);
void	cmd_error(char *str);
void	error(char *str);
void	free_str_arr(char **str_arr);

#endif