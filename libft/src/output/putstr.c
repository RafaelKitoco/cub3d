/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   putstr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgama <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 13:04:02 by cgama             #+#    #+#             */
/*   Updated: 2024/07/31 13:04:08 by cgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	putstring(const char *str, t_flags flags)
{
	int	count;

	count = 0;
	if (flags.precision >= 0)
	{
		count += putspace(flags.precision, ft_strlen(str), 0);
		count += put_pre(str, flags.precision);
	}
	else
		count += put_pre(str, ft_strlen(str));
	return (count);
}

int	put_str(const char *str, t_flags flags)
{
	int	count;

	count = 0;
	if (str == NULL && flags.precision >= 0 && flags.precision < 6)
	{
		count += putspace(flags.width, 0, 0);
		return (count);
	}
	if (str == NULL)
		str = "(null)";
	if (flags.precision >= 0 && (size_t)flags.precision > ft_strlen(str))
		flags.precision = ft_strlen(str);
	if (flags.left == 1)
		count += putstring(str, flags);
	if (flags.precision >= 0)
		count += putspace(flags.width, flags.precision, 0);
	else
		count += putspace(flags.width, ft_strlen(str), 0);
	if (flags.left == 0)
		count += putstring(str, flags);
	return (count);
}

int	put_pre(const char *str, int precision)
{
	int	count;

	count = 0;
	while (str[count] && count < precision)
		write(1, &str[count++], 1);
	return (count);
}

int	putstr(const char *str)
{
	int	len;

	if (str == NULL)
	{
		write(1, "(null)", 6);
		return (6);
	}
	len = 0;
	while (str[len])
		len++;
	write(1, str, len);
	return (len);
}
