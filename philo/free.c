/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotak <yotak@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 13:56:51 by yotak             #+#    #+#             */
/*   Updated: 2022/06/28 14:06:37 by yotak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	free_info(t_info *info)
{
	int	idx;

	idx = 0;
	while (idx < info->nbr_philos)
	{
		if (pthread_mutex_destroy(&info->m_forks[idx]) \
			|| pthread_mutex_destroy(&info->philo[idx]->m_eat) \
			|| pthread_mutex_destroy(&info->philo[idx]->m_last_eat))
			return (1);
		idx += 1;
	}
	if (pthread_mutex_destroy(&info->m_print) \
		|| pthread_mutex_destroy(&info->m_start_line) \
		|| pthread_mutex_destroy(&info->m_time) \
		|| pthread_mutex_destroy(&info->m_death))
		return (1);
	free(info->forks);
	free(*(info->philo));
	free(info->thread);
	free(info);
	return (0);
}
