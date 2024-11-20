/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgama <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 06:10:42 by cgama             #+#    #+#             */
/*   Updated: 2024/07/28 06:10:44 by cgama            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	printer(char type, va_list args, t_flags flags)
{
	int	count;

	count = 0;
	if (type == '%')
		count += printchar('%', flags);
	else if (type == 'c')
		count += printchar(va_arg(args, int), flags);
	else if (type == 's')
		count += put_str(va_arg(args, const char *), flags);
	else if (type == 'd' || type == 'i')
		count += putint(va_arg(args, int), flags);
	else if (type == 'x')
		count += ft_puthex(va_arg(args, unsigned int), 0, flags);
	else if (type == 'X')
		count += ft_puthex(va_arg(args, unsigned int), 1, flags);
	else if (type == 'u')
		count += putunsigned(va_arg(args, unsigned int), flags);
	else if (type == 'p')
		count += putpointer((unsigned long int)va_arg(args, void *), flags);
	return (count);
}

int	extract_flags(const char *str, int i, va_list args, t_flags *flags)
{
	while (str[++i] && ft_isflag(str[i]))
	{
		if (str[i] == '-')
			*flags = setleft(*flags);
		if (str[i] == '#')
			flags->hash = 1;
		if (str[i] == ' ')
			flags->space = 1;
		if (str[i] == '+')
			flags->plus = 1;
		if (str[i] == '0' && flags->left == 0 && flags->width == 0)
			flags->zero = 1;
		if (str[i] == '.')
			i = setprecision(str, i, args, flags);
		if (str[i] == '*')
			*flags = setwidth(args, *flags);
		if (ft_isdigit(str[i]))
			*flags = setdigit(str[i], *flags);
		if (ft_istype(str[i]))
		{
			flags->spec = str[i];
			break ;
		}
	}
	return (i);
}

int	processor(char *str, va_list args)
{
	int		i;
	int		stoped_i;
	int		count;
	t_flags	flags;

	i = -1;
	count = 0;
	while (str[++i])
	{
		flags = initflags();
		if (str[i] == '%' && str[i + 1] != '\0')
		{
			stoped_i = extract_flags(str, i, args, &flags);
			if (flags.spec > 0)
				i = stoped_i;
			if (str[i] != '\0' && flags.spec > 0 && ft_istype(str[i]))
				count += printer(str[i], args, flags);
			else if (str[i] != '\0')
				count += ft_putchar(str[i]);
		}
		else
			count += ft_putchar(str[i]);
	}
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list		args;
	int			count;
	char		*str;

	if (!format || *format == '\0')
		return (0);
	str = (char *)format;
	if (!str || *str == '\0')
		return (0);
	count = 0;
	va_start(args, format);
	count = processor(str, args);
	va_end(args);
	return (count);
}
