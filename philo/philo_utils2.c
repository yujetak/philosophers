/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotak <yotak@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 09:14:35 by yotak             #+#    #+#             */
/*   Updated: 2022/06/27 10:07:39 by yotak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_get_fork(t_philo *philo)
{
	philo->status = TAKE_FORK;
	philo_status_print(philo);
	philo->info->forks[philo->left_fork] = IN_HAND;
	philo->info->forks[philo->right_fork] = IN_HAND;
}

void	philo_eat(t_philo *philo)
{
	long	eat_time;

	pthread_mutex_lock(&philo->m_eat);
	philo->eat_cnt += 1;
	philo->status_start = get_timestamp(philo->info);
	philo->last_eat = get_timestamp(philo->info);
	philo->status = EAT;
	eat_time = philo->info->time_eat;
	philo_status_print(philo);
	pthread_mutex_unlock(&philo->m_eat);
	ft_usleep(eat_time);
	philo->status_start = 0;
	philo->info->forks[philo->left_fork] = ON_TABLE;
	philo->info->forks[philo->right_fork] = ON_TABLE;
}

void	philo_sleep(t_philo *philo)
{
	int	sleep_time;

	philo->status = SLEEP;
	sleep_time = philo->info->time_sleep;
	philo->status_start = get_timestamp(philo->info);
	philo_status_print(philo);
	philo->status_start = 0;
	ft_usleep(sleep_time);
}

void	philo_think(t_philo *philo)
{
	philo->status = THINK;
	philo->status_start = get_timestamp(philo->info);
	philo_status_print(philo);
}
