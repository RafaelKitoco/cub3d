/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_memory.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgama <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 10:13:41 by cgama             #+#    #+#             */
/*   Updated: 2024/10/29 10:13:46 by cgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_del(void *ptr)
{
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
	}
}

static t_list	*ft_new(void *content)
{
	t_list	*list;

	list = malloc(sizeof(t_list));
	if (!list)
		return (NULL);
	list->content = content;
	list->next = NULL;
	return (list);
}

static void	*manage_memory(void *ptr, bool clean)
{
	static t_list	*garbage_list;

	if (clean)
	{
		ft_lstclear(&garbage_list, ft_del);
		return (NULL);
	}
	else
	{	
		set_signals();
		ft_lstadd_back(&garbage_list, ft_new(ptr));
		return (ptr);
	}
}

void	*ft_malloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = malloc(count * size);
	manage_memory(ptr, false);
	return (ptr);
}

void	ft_free_collector(void)
{
	manage_memory(NULL, true);
}
