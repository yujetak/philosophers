/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotak <yotak@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 08:51:57 by yotak             #+#    #+#             */
/*   Updated: 2022/06/27 09:49:07 by yotak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	is_int(long long nbr)
{
	if ((nbr < -2147483648) || (nbr > 2147483647))
		return (FALSE);
	return (TRUE);
}

int	is_nbr(const char c)
{
	if ((c < '0') || (c > '9'))
		return (FALSE);
	return (TRUE);
}

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	if (!str)
		return (0);
	while (str[len])
		len++;
	return (len);
}

int	ft_atoi(const char *str)
{
	long long	i;
	long long	pi;

	i = 0;
	pi = 0;
	if (!str)
		return (0);
	while (str[i] && ((str[i] >= 9 && str[i] <= 13) || str[i] == 32))
		i += 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			return (-1);
		i += 1;
	}
	while (str[i])
	{
		if (is_nbr(str[i]) == FALSE)
			return (-1);
		pi = pi * 10 + (str[i] - 48);
		i += 1;
	}
	if (is_int(pi) == TRUE)
		return (pi);
	return (-1);
}
