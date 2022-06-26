/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotak <yotak@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 14:12:23 by yotak             #+#    #+#             */
/*   Updated: 2022/06/26 21:28:14 by yotak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    *philo_routine(void *philo)
{
    t_philo *ph;

    ph = (t_philo *)philo;
    pthread_mutex_lock(&ph->info->m_start_line);
    pthread_mutex_unlock(&ph->info->m_start_line);
	if (ph->info->nbr_philos == 1)
	{
		usleep(100);
		return ((void *) 0);
	}
    if ((ph->idx % 2) == 0)
        usleep(100);
    while (ph->info->is_death == FALSE)
    {
        pthread_mutex_lock(&ph->info->m_forks[ph->right_fork]);
        pthread_mutex_lock(&ph->info->m_forks[ph->left_fork]);
        philo_get_fork(ph);
        philo_eat(ph);
		ph->last_eat = get_timestamp(ph->info);
        pthread_mutex_unlock(&ph->info->m_forks[ph->left_fork]);
        pthread_mutex_unlock(&ph->info->m_forks[ph->right_fork]);
        philo_sleep(ph);
        philo_think(ph);
        usleep(100);
    }
    return ((void *) 0);
}

int run_philo(t_info *info)
{
    int idx;

    idx = 0;
    pthread_mutex_lock(&info->m_start_line);
    while (idx < info->nbr_philos)
    {
        if (pthread_create(&info->thread[idx], NULL, &philo_routine, info->philo[idx]))
        {
            print_error("\033[0;91m ❌ Failed to create thread\033[0m\n");
            return (1);
        }
        idx += 1;
    }
    pthread_mutex_unlock(&info->m_start_line);
    idx = 0;
    // 무한반복문 -> if 조건 체크로 break! 프로그램 끝날 때까지 계속 체크해야
    while (idx < info->nbr_philos || (unsigned int)info->philo[idx]->eat_cnt < info->nbr_eat_must)
    {
		usleep(100);
		pthread_mutex_lock(&info->m_time);
        if ((info->time_die < (get_timestamp(info) - info->philo[idx]->last_eat)))
		{
			pthread_mutex_lock(&info->m_print);
			printf("%ld %d died\n", get_timestamp(info), info->philo[idx]->idx + 1);
            pthread_mutex_unlock(&info->m_print);
			return(1) ;
		}
		pthread_mutex_unlock(&info->m_time);
		if (info->nbr_philos > 1)
		{
			idx += 1;
			idx = idx % info->nbr_philos;
		}
    }
    idx = 0;
    while (idx < info->nbr_philos)
    {
		printf("1\n");
        if (pthread_join(info->thread[idx], NULL))
        {
            print_error("\033[0;91m ❌ Failed to join thread\033[0m\n");
            return (1);
        }
        idx += 1;
    }
    return (0);
}
