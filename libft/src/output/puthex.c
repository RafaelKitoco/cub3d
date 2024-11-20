/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   puthex.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgama <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 13:03:18 by cgama             #+#    #+#             */
/*   Updated: 2024/07/31 13:03:21 by cgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	putprefix(int is_upper)
{
	if (is_upper == 1)
		putstr("0X");
	else
		putstr("0x");
	return (2);
}

int	putx(char *nbstr, int n, int is_upper, t_flags flags)
{
	int	count;

	count = 0;
	if (flags.zero == 0 && flags.hash == 1 && n != 0)
		count += putprefix(is_upper);
	if (flags.precision >= 0)
		count += putspace(flags.precision - 1,
				ft_strlen(nbstr) - 1, 1);
	count += putstr(nbstr);
	return (count);
}

int	puthex(char *nbstr, int n, int is_upper, t_flags flags)
{
	int	count;

	count = 0;
	if (flags.zero == 1 && flags.hash == 1 && n != 0)
		count += putprefix(is_upper);
	if (flags.left == 1)
		count += putx(nbstr, n, is_upper, flags);
	if (flags.precision >= 0 && (size_t)flags.precision < ft_strlen(nbstr))
		flags.precision = ft_strlen(nbstr);
	if (flags.precision >= 0)
	{
		flags.width -= flags.precision;
		count += putspace(flags.width, 0, 0);
	}
	else
		count += putspace(flags.width,
				ft_strlen(nbstr) + (flags.hash * 2), flags.zero);
	if (flags.left == 0)
		count += putx(nbstr, n, is_upper, flags);
	return (count);
}

int	ft_puthex(unsigned int n, int is_upper, t_flags flags)
{
	char	*nbstr;
	int		count;

	count = 0;
	if (flags.precision == 0 && n == 0)
	{
		count += putspace(flags.width, 0, 0);
		return (count);
	}
	nbstr = xtoa(n, is_upper);
	if (!nbstr)
		return (0);
	count += puthex(nbstr, n, is_upper, flags);
	free(nbstr);
	return (count);
}
