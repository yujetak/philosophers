/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotak <yotak@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 18:28:36 by yotak             #+#    #+#             */
/*   Updated: 2022/06/27 18:28:37 by yotak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_arg(int argc, char *argv[])
{
	int	idx;

	if ((argc == 5) || (argc == 6))
	{
		idx = 1;
		while (argv[idx])
		{
			if (ft_atoi(argv[idx]) == -1)
			{
				print_error("❌ Please input POSITIVE INTETGERs\n");
				return (1);
			}
			idx += 1;
		}
	}
	else
	{
		print_error("❌ ./philo [philosophers] [die] [eat] [sleep] [opt]\n");
		return (1);
	}
	return (0);
}
