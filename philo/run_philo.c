/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotak <yotak@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 09:04:45 by yotak             #+#    #+#             */
/*   Updated: 2022/06/27 09:50:43 by yotak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *philo)
{
	t_philo	*ph;

	ph = (t_philo *)philo;
	pthread_mutex_lock(&ph->info->m_start_line);
	pthread_mutex_unlock(&ph->info->m_start_line);
	if (ph->info->nbr_philos == 1)
		return ((void *) 0);
	if ((ph->idx % 2) == 0)
		usleep(100);
	while (ph->info->is_death == FALSE)
	{
		pthread_mutex_lock(&ph->info->m_forks[ph->right_fork]);
		pthread_mutex_lock(&ph->info->m_forks[ph->left_fork]);
		philo_get_fork(ph);
		philo_eat(ph);
		pthread_mutex_unlock(&ph->info->m_forks[ph->left_fork]);
		pthread_mutex_unlock(&ph->info->m_forks[ph->right_fork]);
		philo_sleep(ph);
		philo_think(ph);
		usleep(100);
	}
	return ((void *) 0);
}

int	ft_pthread_join(t_info *in)
{
	int	idx;

	idx = 0;
	while (idx < in->nbr_philos)
	{
		if (pthread_join(in->thread[idx], NULL))
		{
			print_error("❌ Failed to join thread\n");
			return (1);
		}
		idx += 1;
	}
	return (0);
}

int	run_philo(t_info *in)
{
	int	idx;

	idx = 0;
	pthread_mutex_lock(&in->m_start_line);
	while (idx < in->nbr_philos)
	{
		if (pthread_create(&in->thread[idx], NULL, &routine, in->philo[idx]))
		{
			print_error("❌ Failed to create thread\n");
			return (1);
		}
		idx += 1;
	}
	pthread_mutex_unlock(&in->m_start_line);
	if (is_philo_death(in) || is_all_philo_eat(in))
		return (1);
	if (ft_pthread_join(in))
		return (1);
	return (0);
}

int	is_philo_death(t_info *in)
{
	int	idx;

	idx = 0;
	while (idx < in->nbr_philos)
	{
		usleep(100);
		pthread_mutex_lock(&in->m_time);
		if ((in->time_die < (get_timestamp(in) - in->philo[idx]->last_eat)))
		{
			pthread_mutex_lock(&in->m_print);
			printf("%ld %d died\n", get_timestamp(in), in->philo[idx]->idx + 1);
			pthread_mutex_unlock(&in->m_print);
			return (1);
		}
		pthread_mutex_unlock(&in->m_time);
		if (in->nbr_philos > 1)
		{
			idx += 1;
			idx = idx % in->nbr_philos;
		}
	}
	return (0);
}

int	is_all_philo_eat(t_info *in)
{
	int	idx;

	idx = 0;
	while (idx < in->nbr_philos)
	{
		if (in->philo[idx]->eat_cnt < in->nbr_eat_must)
			return (FALSE);
		idx += 1;
	}
	printf("all philo eat enough\n");
	return (TRUE);
}
