/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkristie <kukinpower@ya.ru>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 20:22:52 by mkristie          #+#    #+#             */
/*   Updated: 2020/06/28 05:37:32 by mkristie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static int		ft_intlen_with_minus(int num)
{
	int		numlen;

	numlen = 0;
	if (num == 0)
	{
		numlen = 1;
	}
	if (num < 0)
	{
		numlen++;
		num = -1 * num;
	}
	while (num != 0)
	{
		num = num / 10;
		numlen++;
	}
	return (numlen);
}

char			*ft_itoa(int n)
{
	int		nlen;
	char	*s;
	long	num;

	nlen = 0;
	num = (long)n;
	nlen = ft_intlen_with_minus(n);
	if (!(s = malloc(nlen + 1)))
		return (NULL);
	s[nlen] = '\0';
	if (num == 0)
		s[0] = '0';
	if (num < 0)
	{
		s[0] = '-';
		num = -num;
	}
	nlen--;
	while (nlen >= 0 && num != 0)
	{
		s[nlen] = num % 10 + '0';
		num = num / 10;
		nlen--;
	}
	return (s);
}
