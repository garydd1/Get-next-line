/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 20:14:16 by dgarizad          #+#    #+#             */
/*   Updated: 2023/01/19 20:10:46 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

unsigned int	ft_strlen(const char *s)
{
	unsigned int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == 0)
		return ((char *)(s + i));
	else
		return (0);
	return ((char *)s);
}

void	ft_bzero(void *s, size_t n)
{
	unsigned int	i;

	if (n == 0)
		return ;
	i = 0;
	while (i < n)
	{
		*((char *)(s + i)) = '\0';
		i++;
	}
}
/**
 * @brief Do the allocation with all fields set to 0
 * 
 * @param count 
 * @param size 
 * @return void* 
 */

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = malloc(count * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, count * size);
	return (ptr);
}

/**
 * @brief takes the buffer(named line as parameter) and reallocs in a new
 line only the caracters until the first '\n'.
 * 
 * @param line 
 * @return char* 
 returns the reallocated line, the received line is freed.
 */

char	*ft_fix_line(char *line)
{
	int		i;
	int		j;
	char	*newline;

	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
		i++;
	newline = (char *)ft_calloc(i + 2, 1);
	if (!newline)
	{
		free(line);
		return (NULL);
	}
	j = 0;
	while (line[j] != '\0')
	{
		if (j <= i)
			newline[j] = line[j];
		j++;
	}
	free(line);
	line = NULL;
	return (newline);
}
