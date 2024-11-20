/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putunsigned.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgama <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 06:16:18 by cgama             #+#    #+#             */
/*   Updated: 2024/07/31 13:04:29 by cgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	put_u(char *nbstr, t_flags flags)
{
	int	count;

	count = 0;
	if (flags.precision >= 0)
		count += putspace(flags.precision - 1,
				ft_strlen(nbstr) - 1, 1);
	count += putstr(nbstr);
	return (count);
}

int	putunint(char *nbstr, t_flags flags)
{
	int	count;

	count = 0;
	if (flags.left == 1)
		count += put_u(nbstr, flags);
	if (flags.precision >= 0 && (size_t)flags.precision < ft_strlen(nbstr))
		flags.precision = ft_strlen(nbstr);
	if (flags.precision >= 0)
	{
		flags.width -= flags.precision;
		count += putspace(flags.width, 0, 0);
	}
	else
		count += putspace(flags.width, ft_strlen(nbstr), flags.zero);
	if (flags.left == 0)
		count += put_u(nbstr, flags);
	return (count);
}

int	putunsigned(unsigned n, t_flags flags)
{
	char	*nbstr;
	int		count;

	count = 0;
	if (flags.precision == 0 && n == 0)
	{
		count += putspace(flags.width, 0, 0);
		return (count);
	}
	nbstr = utoa(n);
	if (!nbstr)
		return (0);
	count += putunint(nbstr, flags);
	free(nbstr);
	return (count);
}
