/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotak <yotak@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 09:28:44 by yotak             #+#    #+#             */
/*   Updated: 2022/06/27 12:19:31 by yotak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	set_thread(t_info *info)
{
	info->thread = (pthread_t *)malloc \
					(sizeof(pthread_t) * info->nbr_philos + 1);
	if (!(info->thread))
		return (1);
	return (0);
}

int	set_forks_mutex(t_info *info)
{
	int	idx;

	idx = 0;
	info->m_forks = (pthread_mutex_t *)malloc \
					(sizeof(pthread_mutex_t) * info->nbr_philos);
	if (!(info->m_forks))
		return (1);
	while (idx < info->nbr_philos)
	{
		if (pthread_mutex_init(&info->m_forks[idx], NULL))
			return (1);
		idx += 1;
	}
	return (0);
}

int	set_forks_array(t_info *info)
{
	int	idx;

	idx = 0;
	info->forks = (int *)malloc(sizeof(int) * info->nbr_philos);
	if (!(info->forks))
		return (1);
	while (idx < info->nbr_philos)
	{
		info->forks[idx] = ON_TABLE;
		idx += 1;
	}
	return (0);
}

int	set_philo(t_info *info)
{
	int	idx;

	idx = 0;
	info->philo = (t_philo **)malloc(sizeof(t_philo *) * info->nbr_philos);
	if (!(info->philo))
		return (1);
	while (idx < info->nbr_philos)
	{
		info->philo[idx] = (t_philo *)malloc(sizeof(t_philo));
		info->philo[idx]->idx = idx;
		info->philo[idx]->status = THINK;
		info->philo[idx]->eat_cnt = 0;
		info->philo[idx]->status_start = 0;
		info->philo[idx]->last_eat = get_timestamp(info);
		info->philo[idx]->info = info;
		if (pthread_mutex_init(&info->philo[idx]->m_eat, NULL))
			return (1);
		if (pthread_mutex_init(&info->philo[idx]->m_last_eat, NULL))
			return (1);
		if (idx == info->nbr_philos - 1)
			info->philo[idx]->left_fork = 0;
		else
			info->philo[idx]->left_fork = idx + 1;
		info->philo[idx]->right_fork = idx;
		idx += 1;
	}
	return (0);
}
