/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgama <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 09:45:18 by cgama             #+#    #+#             */
/*   Updated: 2024/09/16 13:48:26 by cgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int			ft_found_error(int fd);
static char			*ft_slice(char **str);

char	*get_next_line(int fd)
{
	int			size;
	char		*buffer;
	char		*support;
	static char	*string;

	if (ft_found_error(fd))
		return (NULL);
	buffer = ft_malloc(sizeof(char), (BUFFER_SIZE + 1));
	size = read(fd, buffer, BUFFER_SIZE);
	while (size > 0)
	{
		buffer[size] = '\0';
		if (!string)
			string = ft_strdup(buffer);
		else
		{
			support = ft_strjoin(string, buffer);
			string = support;
		}
		if (ft_strchr(string, '\n'))
			break ;
		size = read(fd, buffer, BUFFER_SIZE);
	}
	return (ft_slice(&string));
}

static int	ft_found_error(int fd)
{
	if (fd == -1 || BUFFER_SIZE <= 0)
		return (1);
	return (0);
}

static char	*ft_slice(char **str)
{
	int		index;
	char	*ret;
	char	*sup;

	index = 0;
	if (!str[0])
		return (NULL);
	while (str[0][index] != '\n' && str[0][index] != '\0')
		index++;
	ret = ft_substr(str[0], 0, index + 1);
	sup = ft_strdup(str[0]);
	str[0] = ft_substr(sup, index + 1, ft_strlen(sup));
	return (ret);
}
