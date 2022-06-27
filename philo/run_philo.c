/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotak <yotak@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 18:01:59 by yotak             #+#    #+#             */
/*   Updated: 2022/06/27 20:08:19 by yotak            ###   ########.fr       */
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
		return (no_country_for_alone_philo(ph));
	if ((ph->idx % 2) == 0)
		usleep(80);
	while (1)
	{
		pthread_mutex_lock(&ph->info->m_death);
		if (ph->info->is_death == TRUE || ph->info->nbr_eat_must <= ph->eat_cnt)
		{
			pthread_mutex_unlock(&ph->info->m_death);
			break ;
		}
		pthread_mutex_unlock(&ph->info->m_death);
		philo_get_fork(ph);
		philo_eat(ph);
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
	check_philo_terminate(in);
	if (ft_pthread_join(in))
		return (1);
	return (0);
}

int	is_philo_death(t_philo *ph)
{
	pthread_mutex_lock(&ph->m_last_eat);
	if ((ph->info->time_die < (get_timestamp(ph->info) - ph->last_eat)))
	{
		pthread_mutex_unlock(&ph->m_last_eat);
		pthread_mutex_lock(&ph->info->m_death);
		ph->info->is_death = TRUE;
		pthread_mutex_unlock(&ph->info->m_death);
		printf("%ld %d died\n", get_timestamp(ph->info), ph->idx + 1);
		return (TRUE);
	}
	pthread_mutex_unlock(&ph->m_last_eat);
	return (FALSE);
}

int	is_all_philo_eat(t_info *in)
{
	int	idx;

	idx = 0;
	while (idx < in->nbr_philos)
	{
		pthread_mutex_lock(&in->philo[idx]->m_eat);
		if (in->philo[idx]->eat_cnt < in->nbr_eat_must)
		{
			pthread_mutex_unlock(&in->philo[idx]->m_eat);
			return (FALSE);
		}
		pthread_mutex_unlock(&in->philo[idx]->m_eat);
		idx += 1;
	}
	return (TRUE);
}
