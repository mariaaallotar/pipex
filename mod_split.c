/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mod_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheleni <maheleni@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/09 12:23:59 by maheleni          #+#    #+#             */
/*   Updated: 2024/06/09 12:24:02 by maheleni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/**
* Counts the amount of substrings in the string 's'
* Parameters:
*	*s - string the substrings are located in
*	c - delimiter character
*	except - character that pauses counting when encountering 'c'
* Returns:
*	How many substrings are in the substring
*/
static int	count_substrings(const char *s, char c, char except)
{
	int	count;
	int	in_substring;
	int	in_exception;

	count = 0;
	in_substring = 0;
	in_exception = 0;
	while (*s)
	{
		if (*s != c && !in_substring && !in_exception)
		{
			in_substring = 1;
			count++;
		}
		else if (*s == c && !in_exception)
			in_substring = 0;
		if (*s == except && !in_exception)
			in_exception = 1;
		else if (*s == except && in_exception)
			in_exception = 0;
		s++;
	}
	return (count);
}

/**
* Counts the length of a substring
* Parameters:
*	*s - string the substring is located in
*	c - delimiter character
*	except - 'c' char between 'except' chars are ignored
* Returns:
*	How many characters is in the substring
*/
static int	sub_length(char const *s, char c, char except)
{
	int	len;
	int	in_exception;

	len = 0;
	in_exception = 0;
	while (*s != '\0' && (*s != c || in_exception))
	{
		if (*s == except && in_exception)
			in_exception = 0;
		else if (*s == except && !in_exception)
			in_exception = 1;
		len++;
		s++;
	}
	return (len);
}

static void	*free_everything(char **mem, int i)
{
	while (i >= 0)
	{
		free(mem[i]);
		i--;
	}
	free(mem);
	return (NULL);
}

/**
* Allocates and returns an array of strings obtained by splitting 's' using
*	the character 'c' as a delimiter. 's' is split every time we encounter 'c',
*	unless we are between the 'e' (=except) chars. 
*	The array must end with a NULL pointer
* Parameters:
*	*s - string to be split
*	c - delimiter character
*	e - char that pauses splitting
* Returns:
*	Array of new strings resulting from the split
*	NULL if the allocation fails
*/
char	**mod_split(char const *s, char c, char e)
{
	char		**strings;
	int			sub_len;
	int			i;

	strings = malloc((count_substrings(s, c, e) + 1) * sizeof(char *));
	if (strings == NULL)
		return (NULL);
	i = 0;
	while (*s != '\0')
	{
		if (*s == c)
		{
			s++;
			continue ;
		}
		sub_len = sub_length(s, c, e);
		strings[i] = ft_substr(s, 0, sub_len);
		if (strings[i] == NULL)
			return (free_everything(strings, i));
		s = s + sub_len;
		i++;
	}
	strings[i] = NULL;
	return (strings);
}
