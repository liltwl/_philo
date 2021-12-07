/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libftools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaouil <otaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/07 03:56:40 by otaouil           #+#    #+#             */
/*   Updated: 2021/12/07 04:12:23 by otaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
	return (1);
}

int	ft_putnbr_fd(unsigned int n, int fd)
{
	int		i;

	i = 0;
	if (n < 10)
		i += ft_putchar_fd(n + '0', fd);
	else if (n >= 10)
	{
		i += ft_putnbr_fd(n / 10, fd);
		i += ft_putchar_fd(n % 10 + '0', fd);
	}
	return (i);
}

int	ft_atoi(const char *str)
{
	long	m;
	char	*p;
	int		i;

	p = (char *)str;
	m = 0;
	i = 0;
	if (p[i] == '-' || p[i] == '+')
	{
		if (p[(i)++] == '-')
			ft_print("error : Invalid arguments", NULL, 0, 7);
	}
	while (p[i] && p[i] >= '0' && p[i] <= '9')
	{
		m = (m * 10) + (p[(i)++] - 48);
		if (m > 2147483647)
			ft_print("error : Invalid arguments", NULL, 0, 7);
	}
	if (p[i] && !(p[i] >= '0' && p[i] <= '9'))
		ft_print("error : Invalid arguments", NULL, 0, 7);
	return (m);
}
