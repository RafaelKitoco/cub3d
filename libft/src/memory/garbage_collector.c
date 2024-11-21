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
		ft_printf("Clearing garbage list...\n");
        ft_lstclear(&garbage_list, ft_del);
        ft_printf("Garbage list cleared.\n");
		return (NULL);
	}
	else
	{	t_list *new_node = ft_new(ptr);
        if (!new_node || !ptr)
        {
            ft_printf("Failed to allocate memory for new node.\n");
            return (NULL);
        }
		set_signals();
		ft_lstadd_back(&garbage_list, new_node);
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
