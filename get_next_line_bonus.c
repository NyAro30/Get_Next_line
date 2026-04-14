/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mny-aro- <mny-aro-@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 10:28:33 by mny-aro-          #+#    #+#             */
/*   Updated: 2026/03/01 16:19:06 by mny-aro-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*extract_line(char **stash_ptr)
{
	char	*line;
	char	*temp;
	int		len;

	if (ft_strchr(*stash_ptr, '\n'))
	{
		len = ft_strchr(*stash_ptr, '\n') - *stash_ptr + 1;
		line = ft_substr(*stash_ptr, 0, len);
		temp = ft_substr(*stash_ptr, len, (ft_strlen(*stash_ptr) - len));
		free(*stash_ptr);
		*stash_ptr = temp;
		return (line);
	}
	if (*stash_ptr == NULL || **stash_ptr == '\0')
		return (NULL);
	line = *stash_ptr;
	*stash_ptr = NULL;
	return (line);
}

static int	read_and_stash_bonus(int fd, char **stash)
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
	static char	*stash[MAX_FD];
	int			status;

	if (fd < 0 || fd >= MAX_FD || BUFFER_SIZE <= 0)
		return (NULL);
	status = 1;
	while (ft_strchr(stash[fd], '\n') == NULL && status > 0)
	{
		status = read_and_stash_bonus(fd, &stash[fd]);
		if (status == -1)
		{
			free(stash[fd]);
			return (stash[fd] = NULL, NULL);
		}
	}
	if (stash[fd] == NULL || *stash[fd] == '\0')
	{
		free(stash[fd]);
		stash[fd] = NULL;
		return (NULL);
	}
	return (extract_line(&stash[fd]));
}
