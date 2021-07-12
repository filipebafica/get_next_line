/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbafica <fbafica@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/29 20:01:02 by fbafica           #+#    #+#             */
/*   Updated: 2021/07/11 22:51:18 by fbafica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "get_next_line.h"

static int	get_len(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		++i;
	}
	return (i);
}

static int	get_chrlen(const char *s, int c)
{
	int	len;
	int	i;
	int	j;

	len = get_len(s);
	i = 0;
	j = 0;
	while (i < len)
	{
		if (s[i] == (unsigned char)c)
		{
			++j;
			break ;
		}
		++i;
	}
	if (j == 0)
		return (j);
	else
		return (i);
}

static char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_string;
	int		len;
	int		i;
	int		j;

	i = 0;
	j = 0;
	len = get_len(s1) + get_len(s2);
	new_string = malloc(len + 1);
	if (!new_string)
		return (NULL);
	while (s1[i] != '\0')
	{
		new_string[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		new_string[i] = s2[j];
		i++;
		j++;
	}
	new_string[i] = '\0';
	return (new_string);
}

static char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substring;
	size_t	s_len;
	size_t	size;
	size_t	i;

	s_len = get_len(s);
	size = 0;
	if (len > (s_len - start))
		size = s_len - start;
	else
		size = len;
	if (s == NULL)
		return (NULL);
	else
		substring = malloc((size + 1) * sizeof(char));
	if (!substring)
		return (NULL);
	i = 0;
	while (i < size)
	{
		substring[i] = s[i + start];
		++i;
	}
	substring[i] = '\0';
	return (substring);
}

static char	*ft_strchr(const char *s, int c)
{
	int	len;
	int	i;
	int	j;

	len = get_len(s);
	i = 0;
	j = 0;
	while (i <= len)
	{
		if (s[i] == (unsigned char)c)
		{
			++j;
			break ;
		}
		++i;
	}
	if (j == 0)
		return ((char *) '\0');
	else
		return ((char *)s + i);
}

static void	check_saved(char ***saved)
{
	if (**saved)
	{
		free(**saved);
		**saved = NULL;
	}
}

static void	saved_cut(char ***saved, int start)
{
	char	*temp;
	int		cut_len;

	cut_len = get_len(**saved) - start;
	temp = ft_substr(**saved, 0, get_len(**saved));
	free(**saved);
	**saved = ft_substr(temp, start, cut_len);
	free(temp);
}

static int	fill_line(char ***line, char **saved)
{
	int	len;

	if (*saved)
	{
		if (!ft_strchr(*saved, '\n'))
		{
			len = get_len(*saved);
			**line = ft_substr(*saved, 0, len);
			saved_cut(&saved, len);
			check_saved(&saved);
			return (0);
		}
		len = get_chrlen(*saved, '\n');
		**line = ft_substr(*saved, 0, len);
		saved_cut(&saved, len + 1);
		return (1);
	}
	else
	{
		**line = ft_substr("", 0, 0);
		check_saved(&saved);
		return (0);
	}
}

static void	saved_update(char **buffer, char **saved)
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
