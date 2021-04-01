/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pfile <pfile@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 18:42:34 by pfile             #+#    #+#             */
/*   Updated: 2021/01/28 02:13:11 by pfile            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int		ft_atoi(const char *str)
{
	int		k;
	int		nb;

	nb = 0;
	k = 1;
	while (*str == 32 || (*str > 8 && *str < 14))
		++str;
	if (*str == 43 || *str == 45)
		if (*str++ == 45)
			k = -1;
	while (ft_isdigit(*str))
		nb = nb * 10 + (*str++ - 48);
	return (nb * k);
}

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*len;

	if (!(len = (unsigned char *)malloc(count * size)))
		return (0);
	memset(len, 0, count * size);
	return (len);
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		ft_putchar(str[i]);
		i++;
	}
}

int		ft_isdigit(int c)
{
	return (c > 47 && c < 58);
}
