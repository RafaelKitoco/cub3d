/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putpointer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgama <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 13:03:45 by cgama             #+#    #+#             */
/*   Updated: 2024/07/31 13:03:47 by cgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	putnbr(unsigned long int n)
{
	if (n >= 16)
	{
		putnbr(n / 16);
		putnbr(n % 16);
	}
	else
	{
		if (n < 10)
			ft_putchar(n + '0');
		else if (n >= 10)
			ft_putchar((n - 10) + 'a');
	}
}

int	putpointer_pre(unsigned long int n)
{
	int	count;

	count = 0;
	if (n == 0)
	{
		count += putstr(NULL);
		return (count);
	}
	count += putstr("0x");
	putnbr(n);
	count += pointerlen(n);
	return (count);
}

int	putpointer(unsigned long int n, t_flags flags)
{
	int	count;

	count = 0;
	if (n == 0)
		flags.width -= ft_strlen(NULL) - 1;
	else
		flags.width -= 2;
	if (flags.left == 1)
		count += putpointer_pre(n);
	count += putspace(flags.width, pointerlen(n), 0);
	if (flags.left == 0)
		count += putpointer_pre(n);
	return (count);
}
