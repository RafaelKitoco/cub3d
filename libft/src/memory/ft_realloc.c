/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgama <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/21 12:26:31 by cgama             #+#    #+#             */
/*   Updated: 2024/11/21 12:26:35 by cgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_memdel(void **ap)
{
	if (ap != NULL)
	{
		free(*ap);
		*ap = NULL;
	}
}

void	*ft_realloc(void *ptr, size_t size)
{
	char *new;

	if (!ptr)
		new = malloc(size);
	if (!size && ptr)
	{
		ft_memdel(ptr);
		return (ptr);
	}
	new = (char *)malloc(size);
	if (!new)
		return (NULL);
	ft_memcpy(new, ptr, size);
	ft_memdel(&ptr);
	ptr = new;
	return (ptr);
}