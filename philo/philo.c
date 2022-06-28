/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotak <yotak@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 09:17:57 by yotak             #+#    #+#             */
/*   Updated: 2022/06/28 13:57:24 by yotak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_info	*info;

	info = (t_info *)malloc(sizeof(t_info));
	if (!info)
		return (1);
	if (check_arg(argc, argv))
		return (1);
	if (set_info(argc, argv, info))
		return (1);
	if (run_philo(info))
		return (1);
	if (free_info(info))
		return (1);
	return (0);
}

void	print_error(const char *msg)
{
	write(2, msg, ft_strlen(msg));
}
