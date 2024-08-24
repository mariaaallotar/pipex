/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/13 11:18:17 by maheleni          #+#    #+#             */
/*   Updated: 2024/08/24 10:57:50 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	cmd_error(char *str)
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
