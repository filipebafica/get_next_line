/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbafica <fbafica@student.42sp.org.br>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/01 16:08:00 by fbafica           #+#    #+#             */
/*   Updated: 2021/07/10 13:55:10 by fbafica          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	get_len(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		++i;
	}
	return (i);
}

int	get_chrlen(const char *s, int c)
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

char	*ft_strjoin(char const *s1, char const *s2)
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

char	*ft_substr(char const *s, unsigned int start, size_t len)
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

char	*ft_strchr(const char *s, int c)
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
