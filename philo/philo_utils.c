/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotak <yotak@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/26 15:32:48 by yotak             #+#    #+#             */
/*   Updated: 2022/06/26 21:26:15 by yotak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_time(void)
{
	struct timeval  current_time;

	gettimeofday(&current_time, NULL);
	return (current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
}

long	get_timestamp(t_info *info)
{
	long	start_time;

	// pthread_mutex_lock(&info->m_time);
	start_time = info->main_start_time;
	// pthread_mutex_unlock(&info->m_time);
	return (get_time() - start_time);
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

	// printf("philo[%d] 1\n", philo->idx);
	pthread_mutex_lock(&philo->m_eat);
	philo->eat_cnt += 1;
	// printf("philo[%d] 1.5\n", philo->idx);
	philo->status_start = get_timestamp(philo->info);
	// printf("philo[%d] 2\n", philo->idx);
	philo->status = EAT;
	// pthread_mutex_lock(&philo->info->m_time);
	eat_time = philo->info->time_eat;
	// pthread_mutex_unlock(&philo->info->m_time);
	// printf("philo[%d] 3\n", philo->idx);
	philo_status_print(philo);
	// printf("philo[%d] 4\n", philo->idx);
	pthread_mutex_unlock(&philo->m_eat);
	ft_usleep(eat_time);
	// printf("philo[%d] 5\n", philo->idx);
	philo->status_start = 0;
	philo->info->forks[philo->left_fork] = ON_TABLE;
	philo->info->forks[philo->right_fork] = ON_TABLE;
}

void	philo_sleep(t_philo *philo)
{
	int sleep_time;

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
	if (philo->info->time_die < ((get_timestamp(philo->info) - philo->last_eat)))
	{
		pthread_mutex_lock(&philo->info->m_death);
		philo->info->is_death = TRUE;
		pthread_mutex_unlock(&philo->info->m_death);
		printf("%ld %d died\n", get_timestamp(philo->info), philo->idx + 1);
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
		if ((unsigned int)info->philo[idx]->eat_cnt < info->nbr_eat_must)
			return (FALSE);
		idx += 1;
	}
	return (TRUE);
}
