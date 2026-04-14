/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mny-aro- <mny-aro-@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/01 11:33:44 by mny-aro-          #+#    #+#             */
/*   Updated: 2026/03/01 16:19:21 by mny-aro-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*new_stash;
	int		total_size;
	int		i;
	int		j;

	if (!s1 && !s2)
		return (NULL);
	if (!s2)
		return (s1);
	if (!s1)
		return (ft_strdup(s2));
	total_size = ft_strlen(s1) + ft_strlen(s2);
	new_stash = malloc(sizeof(char) * (total_size + 1));
	if (!new_stash)
		return (NULL);
	i = -1;
	j = 0;
	while (s1[++i])
		new_stash[j++] = s1[i];
	i = -1;
	while (s2[++i])
		new_stash[j++] = s2[i];
	new_stash[j] = '\0';
	return (free(s1), new_stash);
}

char	*ft_strchr(char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i])
	{
		if (s[i] == (char)c)
			return (&s[i]);
		i++;
	}
	if ((char)c == '\0')
		return (&s[i]);
	return (NULL);
}

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;
	size_t	sub_len;

	if (!s)
		return (NULL);
	i = ft_strlen(s);
	if (start >= i)
		return (ft_strdup(""));
	sub_len = len;
	if (sub_len > i - start)
		sub_len = i - start;
	sub = malloc((sub_len + 1) * sizeof(char));
	if (!sub)
		return (NULL);
	i = 0;
	while (i < sub_len && s[start])
		sub[i++] = s[start++];
	sub[i] = '\0';
	return (sub);
}

char	*ft_strdup(char *s)
{
	char	*dup;
	size_t	i;

	if (!s)
		return (NULL);
	dup = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!dup)
		return (NULL);
	i = 0;
	while (s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}
