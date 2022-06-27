/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_info.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotak <yotak@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 09:25:41 by yotak             #+#    #+#             */
/*   Updated: 2022/06/27 12:17:08 by yotak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	init_info_mutex(t_info *in)
{
	if (set_forks_mutex(in))
		return (1);
	if (pthread_mutex_init(&in->m_print, NULL))
		return (1);
	if (pthread_mutex_init(&in->m_time, NULL))
		return (1);
	if (pthread_mutex_init(&in->m_death, NULL))
		return (1);
	if (pthread_mutex_init(&in->m_start_line, NULL))
		return (1);
	return (0);
}

static int	init_info(t_info *in)
{
	memset((void *)in, 0, sizeof(t_info));
	if (!in)
		return (1);
	in->nbr_eat_must = INT32_MAX;
	return (0);
}

int	set_info(int argc, char *argv[], t_info *info)
{
	if (init_info(info))
		return (1);
	info->nbr_philos = ft_atoi(argv[1]);
	info->time_die = ft_atoi(argv[2]);
	info->time_eat = ft_atoi(argv[3]);
	info->time_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		info->nbr_eat_must = ft_atoi(argv[5]);
	info->main_start_time = get_time();
	if (set_philo(info))
		return (1);
	if (set_forks_array(info))
		return (1);
	if (set_thread(info))
		return (1);
	if (init_info_mutex(info))
		return (1);
	return (0);
}
