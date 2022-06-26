/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotak <yotak@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 15:32:48 by yotak             #+#    #+#             */
/*   Updated: 2022/06/26 15:51:46 by yotak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval  current_time;

	gettimeofday(&current_time, NULL);
	return (current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
}

long	get_timestamp(long main_start_time)
{
	long	current_time;

	current_time = get_time();
	return (current_time - main_start_time);
}

void	philo_status_print(t_philo *philo)
{
	if (philo->info->is_death == FALSE)
	{
		pthread_mutex_lock(&philo->info->m_print);
		if (philo->status == TAKE_FORK)
			printf("%ld %d has taken a fork\n", philo->status_start, philo->idx + 1);
		else if (philo->status == EAT)
			printf("%ld %d is eating\n", philo->status_start, philo->idx + 1);
		else if (philo->status == SLEEP)
			printf("%ld %d is sleeping\n", philo->status_start, philo->idx + 1);
		else if (philo->status == THINK)
			printf("%ld %d is thinking\n", philo->status_start, philo->idx + 1);
		pthread_mutex_unlock(&philo->info->m_print);
	}
}

void	philo_get_fork(t_philo *philo)
{
	philo->status = TAKE_FORK;
	philo_status_print(philo);
	philo->info->forks[philo->left_fork] = IN_HAND;
	philo->info->forks[philo->right_fork] = IN_HAND;
}

void	ft_usleep(int status_end_time)
{
	long	target_time;

	target_time = status_end_time + get_time();
	while (target_time > get_time())
		usleep(100);
}

void	philo_eat(t_philo *philo)
{
	long eat_time;

	philo->status = EAT;
	eat_time = philo->info->time_eat;
	philo->eat_cnt += 1;
	philo->status_start = get_timestamp(philo->info->main_start_time);
	philo->last_eat = philo->status_start;
	philo_status_print(philo);
	ft_usleep(eat_time);
	philo->status_start = 0;
	philo->info->forks[philo->left_fork] = ON_TABLE;
	philo->info->forks[philo->right_fork] = ON_TABLE;
}

void	philo_sleep(t_philo *philo)
{
	int sleep_time;

	philo->status = SLEEP;
	sleep_time = philo->info->time_sleep;
	philo->status_start = get_timestamp(philo->info->main_start_time);
	philo_status_print(philo);
	philo->status_start = 0;
	ft_usleep(sleep_time);
}

void	philo_think(t_philo *philo)
{
	philo->status = THINK;
	philo->status_start = get_timestamp(philo->info->main_start_time);
	philo_status_print(philo);
}

int is_philo_death(t_philo *philo)
{
	// int	die_time;
	// int	 is_death;

	// pthread_mutex_lock(&philo->info->m_death);
	// is_death = philo->info->is_death;
	// pthread_mutex_unlock(&philo->info->m_death);
	// pthread_mutex_lock(&philo->info->m_time);
	// die_time = philo->info->time_die;
	// pthread_mutex_unlock(&philo->info->m_time);
	if (philo->info->time_die < ((get_timestamp(philo->info->main_start_time) - philo->last_eat)))
	{
		pthread_mutex_lock(&philo->info->m_death);
		philo->info->is_death = TRUE;
		pthread_mutex_unlock(&philo->info->m_death);
		printf("%ld %d died\n", get_timestamp(philo->info->main_start_time), philo->idx + 1);
		return (TRUE);
	}
	return (FALSE);
}

int is_all_eat(t_info *info)
{
	int	idx;

	idx = 0;
	while(idx < info->nbr_philos)
	{
		if (info->philo[idx].eat_cnt < (int)info->nbr_eat_must)
			return (FALSE);
		idx += 1;
	}
	return (TRUE);
}
