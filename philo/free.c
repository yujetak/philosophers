/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotak <yotak@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 09:05:13 by yotak             #+#    #+#             */
/*   Updated: 2022/06/27 09:31:06 by yotak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_info(t_info *info)
{
	int	idx;

	idx = 0;
	while (idx < info->nbr_philos)
	{
		pthread_mutex_destroy(&info->m_forks[idx]);
		pthread_mutex_destroy(&info->philo[idx]->m_eat);
		idx += 1;
	}
	pthread_mutex_destroy(&info->m_death);
	pthread_mutex_destroy(&info->m_print);
	pthread_mutex_destroy(&info->m_start_line);
	pthread_mutex_destroy(&info->m_time);
	pthread_mutex_destroy(&info->m_death);
	free(info->forks);
	free(info->m_forks);
	free(*(info->philo));
	free(info->thread);
	free(info);
}
