/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_sginal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgama <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 14:31:43 by cgama             #+#    #+#             */
/*   Updated: 2024/11/18 14:31:46 by cgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	handle_newline(int sig)
{
	(void)sig;
	ft_putchar_fd('\n', 1);
	ft_free_collector();
	usleep(5000);
	exit(0);
}

void	set_signals(void)
{
	signal(SIGINT, handle_newline);
	signal(SIGQUIT, SIG_IGN);
}
