/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 18:52:35 by dgarizad          #+#    #+#             */
/*   Updated: 2023/01/19 20:09:47 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#ifndef BUFFER_SIZE
# define BUFFER_SIZE	1
#endif

static char	*ft_save_buffer(char *line)
{
	int		i;
	int		j;
	char	*newbuffer;

	i = 0;
	j = 0;
	newbuffer = NULL;
	if (!(ft_strchr(line, '\n')))
		return (NULL);
	while (line[i] != '\n')
		i++;
	newbuffer = (char *)ft_calloc(ft_strlen(line) - i, 1);
	if (!newbuffer)
		return (NULL);
	while (line[i + 1 + j] != '\0')
	{
		newbuffer[j] = line[i + 1 + j];
		j++;
	}
	if (ft_strlen(newbuffer) == 0)
	{
		free(newbuffer);
		newbuffer = NULL;
	}
	return (newbuffer);
}

static char	*ft_buffercat(char *buffer, char *local_buffer, int *nread)
{
	unsigned int	len1;
	int				len2;
	char			*new_buffer;

	len1 = ft_strlen(buffer);
	new_buffer = (char *)ft_calloc(len1 + *nread + 1, 1);
	if (!new_buffer)
		return (NULL);
	len1 = 0;
	while (buffer[len1] != '\0')
	{
		new_buffer[len1] = buffer[len1];
		len1++;
	}
	len2 = 0;
	while (len2 != *nread)
	{
		new_buffer[len1 + len2] = local_buffer[len2];
		len2++;
	}
	free(buffer);
	buffer = new_buffer;
	new_buffer = NULL;
	return (buffer);
}

static char	*ft_get_buffer(int fd, char *buffer, char *local_buffer, int *nread)
{
	int	i;

	i = 0;
	while (*nread > 0 && i++ >= 0)
	{
		*nread = read(fd, local_buffer, BUFFER_SIZE);
		if (*nread <= 0)
		{
			if ((i -1 == 0) && ft_strlen(buffer) == 0)
				return (NULL);
			return (buffer);
		}
		buffer = ft_buffercat(buffer, local_buffer, nread);
		if (!buffer)
			return (NULL);
		if ((ft_strchr(buffer, '\n')) || *nread < BUFFER_SIZE)
			break ;
	}
	return (buffer);
}

static char	*ft_read_fd(int fd, char *buffer)
{
	int		nread;
	char	local_buffer[BUFFER_SIZE + 1];

	nread = 1;
	local_buffer[BUFFER_SIZE] = '\0';
	buffer = ft_get_buffer(fd, buffer, local_buffer, &nread);
	return (buffer);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*buffer[1024];

	if (read (fd, 0, 0) < 0)
	{
		if (buffer[fd])
			free (buffer[fd]);
		buffer[fd] = NULL;
		return (NULL);
	}
	if (!buffer[fd])
		buffer[fd] = (char *)ft_calloc(BUFFER_SIZE + 1, 1);
	if (!buffer[fd])
		return (NULL);
	line = ft_read_fd(fd, buffer[fd]);
	if (!line)
	{
		free(buffer[fd]);
		buffer[fd] = NULL;
		return (NULL);
	}
	buffer[fd] = ft_save_buffer(line);
	if (ft_strchr(line, '\n'))
		line = ft_fix_line(line);
	return (line);
}
// void ft_void(void)
// {
// 	system("leaks -q a.out");
// }
// int	main()
// {
// 	int		fd;
// 	int		i;
// 	char *str;

// 	i = 0;
// 	fd = open("./numbers.dict", O_RDONLY);
// 	while (i++ < 3)
// 	{
// 		str = get_next_line(fd);
// 		//printf("\n-----\n'%s'\n----\n",str);
// 		free(str);
// 		getchar();
// 	}
// 	atexit(ft_void);
// 	return (0);
// }
