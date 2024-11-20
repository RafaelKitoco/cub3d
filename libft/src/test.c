/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgama <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:42:40 by cgama             #+#    #+#             */
/*   Updated: 2024/11/15 15:42:43 by cgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*make re bonus && 
cc src/test.c libft.a -Iinclude && 
clear && 
valgrind --leak-check=full --show-leak-kinds=all ./a.out
*/

#include "libft.h"

void	print_file(char *path)
{
	char	*str;
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd <= -1)
		ft_printf("Not found file!\n");
	str = get_next_line(fd);
	while (str && *str)
	{
		ft_printf("%s", str);
		str = get_next_line(fd);
	}
}

int	main(int argc, char **argv)
{
	char	*str;
	t_list	*list;

	str = "Hello World!";
	list = ft_lstnew(str);
	list->next = ft_lstnew("Hello World!0");
	list->next->next = ft_lstnew("Hello World!1");
	list->next->next->next = ft_lstnew("Hello World!3");
	if (!list)
		return (1);
	while (list)
	{
		ft_putstr_fd(list->content, 1);
		ft_putstr_fd("\n", 1);
		list = list->next;
	}
	ft_printf("\n");
	if (argc == 1 || !argv[1][0])
		print_file(".gitignore");
	else
		print_file(argv[1]);
	ft_free_collector();
	return (0);
}
