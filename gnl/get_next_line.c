/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgarizad <dgarizad@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 18:52:35 by dgarizad          #+#    #+#             */
/*   Updated: 2023/03/24 18:12:18 by dgarizad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#ifndef BUFFER_SIZE
# define BUFFER_SIZE	1
#endif

char	*ft_save_buffer(char *line)
{
	int		i;
	int		j;
	char	*newbuffer;

	i = 0;
	j = 0;
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

char	*ft_buffercat(char *buffer, char *local_buffer, int nread)
{
	unsigned int	len1;
	int				len2;
	char			*new_buffer;

	len1 = ft_strlen(buffer);
	new_buffer = (char *)ft_calloc(len1 + nread + 1, 1);
	if (!new_buffer)
		return (NULL);
	len1 = 0;
	while (buffer[len1] != '\0')
	{
		new_buffer[len1] = buffer[len1];
		len1++;
	}
	len2 = 0;
	while (len2 != nread)
	{
		new_buffer[len1 + len2] = local_buffer[len2];
		len2++;
	}
	free(buffer);
	buffer = NULL;
	return (new_buffer);
}

char	*ft_get_buffer(int fd, char *buffer, char *local_buffer, int nread)
{
	int	i;

	i = 0;
	while (nread > 0 && i++ >= 0)
	{
		nread = read(fd, local_buffer, BUFFER_SIZE);
		if (nread <= 0)
		{
			free (local_buffer);
			local_buffer = NULL;
			if ((i -1 == 0) && ft_strlen(buffer) == 0)
				return (NULL);
			return (buffer);
		}
		buffer = ft_buffercat(buffer, local_buffer, nread);
		if ((ft_strchr(local_buffer, '\n')) || nread < BUFFER_SIZE)
			break ;
	}
	free(local_buffer);
	local_buffer = NULL;
	return (buffer);
}

char	*ft_read_fd(int fd, char *buffer)
{
	int		nread;
	char	*local_buffer;

	nread = 1;
	local_buffer = (char *)ft_calloc(BUFFER_SIZE + 1, 1);
	if (!local_buffer)
		return (NULL);
	buffer = ft_get_buffer(fd, buffer, local_buffer, nread);
	return (buffer);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*buffer;

	if (read (fd, 0, 0) < 0)
	{
		if (buffer)
			free (buffer);
		buffer = NULL;
		return (NULL);
	}
	if (!buffer || ft_strlen(buffer) == 0)
		buffer = (char *)ft_calloc(BUFFER_SIZE + 1, 1);
	if (!buffer)
		return (NULL);
	line = ft_read_fd(fd, buffer);
	if (!line)
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	buffer = ft_save_buffer(line);
	if (ft_strchr(line, '\n'))
		line = ft_fix_line(line);
	return (line);
}

// int	main()
// {
// 	int		fd;
// 	int		i;

// 	i = 0;
// 	fd = open("./numbers.dict", O_RDONLY);
// 	while (i++ < 43)
// 	{
// 		printf("\n-----\n'%s'\n----\n",get_next_line(fd));
// 		getchar();
// 	}
// 	return (0);
// }
