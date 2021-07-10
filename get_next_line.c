/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbafica <fbafica@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 20:01:02 by fbafica           #+#    #+#             */
/*   Updated: 2021/07/10 14:28:24 by fbafica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"

void	check_saved(char ***saved)
{
	if (**saved)
	{
		free(**saved);
		**saved = NULL;
	}
}

void	saved_cut(char ***saved, int start)
{
	char	*temp;
	int		cut_len;

	cut_len = get_len(**saved) - start;
	temp = ft_substr(**saved, 0, get_len(**saved));
	free(**saved);
	**saved = ft_substr(temp, start, cut_len);
	free(temp);
}

int	fill_line(char ***line, char **saved)
{
	int	len;

	if (*saved)
	{
		if (ft_strchr(*saved, '\n'))
		{
			len = get_chrlen(*saved, '\n');
			**line = ft_substr(*saved, 0, len);
			saved_cut(&saved, len + 1);
			return (1);
		}
		else
		{
			len = get_len(*saved);
			**line = ft_substr(*saved, 0, len);
			saved_cut(&saved, len);
			return (0);
		}
	}
	else
	{
		**line = ft_substr("", 0, 0);
		check_saved(&saved);
		return (0);
	}
}

void	saved_update(char **buffer, char **saved)
{
	char	*temp;

	temp = ft_strjoin(*saved, *buffer);
	free(*saved);
	*saved = ft_substr(temp, 0, get_len(temp));
	free(temp);
}

int	get_next_line(int fd, char **line)
{
	static char	*saved = NULL;
	char		*buffer;
	int			read_call;

	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	buffer = malloc(BUFFER_SIZE + 1);
	read_call = read(fd, buffer, BUFFER_SIZE);
	while (read_call > 0)
	{
		buffer[read_call] = '\0';
		if (!saved)
			saved = ft_substr(buffer, 0, get_len(buffer));
		else
			saved_update(&buffer, &saved);
		if (get_chrlen(buffer, '\n'))
			break ;
		read_call = read(fd, buffer, BUFFER_SIZE);
	}
	free(buffer);
	if (read_call == -1)
		return (-1);
	return (fill_line(&line, &saved));
}
