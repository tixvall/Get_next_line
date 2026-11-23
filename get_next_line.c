/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mohfall <mohfall@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/25 16:54:57 by mohfall           #+#    #+#             */
/*   Updated: 2026/10/25 20:54:01 by mohfall          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

static char	*read_stash(int fd, char *stash)
{
	char	*buf;
	ssize_t	n;

	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (free(stash), NULL);
	buf[0] = '\0';
	n = 1;
	while (n > 0 && !ft_strchr(buf, '\n'))
	{
		n = read(fd, buf, BUFFER_SIZE);
		if (n < 0)
			return (free(buf), free(stash), NULL);
		buf[n] = '\0';
		stash = ft_strjoin(stash, buf);
		if (!stash)
			return (free(buf), NULL);
	}
	free(buf);
	return (stash);
}

static char	*extract_line(char *stash)
{
	size_t	i;

	if (!stash || !stash[0])
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i++;
	return (ft_substr(stash, 0, i));
}

static char	*clean_stash(char *stash)
{
	char	*nl;
	char	*rest;

	nl = ft_strchr(stash, '\n');
	if (!nl || !nl[1])
		return (free(stash), NULL);
	rest = ft_substr(nl + 1, 0, ft_strlen(nl + 1));
	free(stash);
	return (rest);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!ft_strchr(stash, '\n'))
		stash = read_stash(fd, stash);
	if (!stash)
		return (NULL);
	line = extract_line(stash);
	stash = clean_stash(stash);
	return (line);
}
