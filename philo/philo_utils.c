/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotak <yotak@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 15:32:48 by yotak             #+#    #+#             */
/*   Updated: 2022/06/27 10:04:22 by yotak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return (current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
}

long	get_timestamp(t_info *info)
{
	long	start_time;

	start_time = info->main_start_time;
	return (get_time() - start_time);
}

void	philo_status_print(t_philo *ph)
{
	if (ph->info->is_death == FALSE)
	{
		pthread_mutex_lock(&ph->info->m_print);
		if (ph->status == TAKE_FORK)
			printf("%ld %d has taken a fork\n", ph->status_start, ph->idx + 1);
		else if (ph->status == EAT)
			printf("%ld %d is eating\n", ph->status_start, ph->idx + 1);
		else if (ph->status == SLEEP)
			printf("%ld %d is sleeping\n", ph->status_start, ph->idx + 1);
		else if (ph->status == THINK)
			printf("%ld %d is thinking\n", ph->status_start, ph->idx + 1);
		pthread_mutex_unlock(&ph->info->m_print);
	}
}

void	ft_usleep(int status_end_time)
{
	long	target_time;

	target_time = status_end_time + get_time();
	while (target_time > get_time())
		usleep(100);
}
