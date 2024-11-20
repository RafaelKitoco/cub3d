/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpambo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 11:30:35 by rpambo            #+#    #+#             */
/*   Updated: 2024/11/08 11:31:13 by rpambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./headers/cub3d.h"

char	*ft_strdup(const char *s1)
{
    char	*str;
    int		i;

    i = 0;
    while (s1[i])
        i++;
    str = (char *)malloc(sizeof(char) * (i + 1));
    if (!str)
        return (0);
    i = 0;
    while (s1[i])
    {
        str[i] = s1[i];
        i++;
    }
    str[i] = '\0';
    return (str);
}

//ft_itoa
char	*ft_itoa(int n)
{
    char	*str;
    int		len;
    long	nbr;

    nbr = n;
    len = 0;
    if (nbr == 0)
        return (ft_strdup("0"));
    if (nbr < 0)
    {
        nbr = -nbr;
        len++;
    }
    while (n != 0)
    {
        n = n / 10;
        len++;
    }
    str = (char *)malloc(sizeof(char) * (len + 1));
    if (!str)
        return (0);
    str[len] = '\0';
    while (nbr != 0)
    {
        str[--len] = nbr % 10 + '0';
        nbr = nbr / 10;
    }
    if (len == 1)
        str[0] = '-';
    return (str);
}
