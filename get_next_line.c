/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mny-aro- <mny-aro-@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 03:57:13 by mny-aro-          #+#    #+#             */
/*   Updated: 2026/03/01 16:18:18 by mny-aro-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*extract_line(char **stash)
{
	char	*line;
	char	*temp;
	int		len;

	if (ft_strchr(*stash, '\n'))
	{
		len = ft_strchr(*stash, '\n') - *stash + 1;
		line = ft_substr(*stash, 0, len);
		temp = ft_substr(*stash, len, (ft_strlen(*stash) - len));
		free(*stash);
		*stash = temp;
		return (line);
	}
	if (*stash == NULL || **stash == '\0')
		return (NULL);
	line = *stash;
	*stash = NULL;
	return (line);
}

static int	read_and_stash(int fd, char **stash)
{
	char	*buf;
	int		bytes_read;
	char	*temp;

	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (-1);
	bytes_read = read(fd, buf, BUFFER_SIZE);
	if (bytes_read <= 0)
		return (free(buf), bytes_read);
	buf[bytes_read] = '\0';
	temp = ft_strjoin(*stash, buf);
	free(buf);
	if (!temp)
	{
		*stash = NULL;
		return (-1);
	}
	*stash = temp;
	return (1);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	int			status;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	status = 1;
	while (ft_strchr(stash, '\n') == NULL && status > 0)
	{
		status = read_and_stash(fd, &stash);
		if (status == -1)
		{
			free(stash);
			return (stash = NULL, NULL);
		}
	}
	if (stash == NULL || *stash == '\0')
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	return (extract_line(&stash));
}
