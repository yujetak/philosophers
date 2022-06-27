/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotak <yotak@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 09:17:57 by yotak             #+#    #+#             */
/*   Updated: 2022/06/28 08:21:53 by yotak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_info	*info;

	info = (t_info *)malloc(sizeof(t_info));
	if (check_arg(argc, argv))
		return (1);
	if (set_info(argc, argv, info))
		return (1);
	if (run_philo(info))
		return (1);
	return (0);
}

void	print_error(const char *msg)
{
	write(2, msg, ft_strlen(msg));
}
