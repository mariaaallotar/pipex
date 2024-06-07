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

typedef struct s_pipex
{
	int		pipe_fds[2];
	pid_t	pid;			//PID of child (in parent)
	char	*path;
	char	*command;
	char	*envp[];
}	t_pipex;

#endif