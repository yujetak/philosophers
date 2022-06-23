/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotak <yotak@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 14:12:23 by yotak             #+#    #+#             */
/*   Updated: 2022/06/23 16:08:21 by yotak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    *philo_routine(void *philo)
{
    t_philo *ph;

    ph = (t_philo *)philo;
    if ((ph->idx % 2) == 0)
        usleep(100);
    while (ph->info->is_death == FALSE)
    {
        pthread_mutex_lock(&ph->info->m_forks[ph->right_fork]);
        pthread_mutex_lock(&ph->info->m_forks[ph->left_fork]);
        philo_get_fork(ph);
        philo_eat(ph);
        pthread_mutex_unlock(&ph->info->m_forks[ph->right_fork]);
        pthread_mutex_unlock(&ph->info->m_forks[ph->left_fork]);
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
    while (idx < info->nbr_philos)
    {
        if (pthread_create(&info->thread[idx], NULL, &philo_routine, &info->philo[idx]))
        {
            print_error("\033[0;91m ❌ Failed to create thread\033[0m\n");
            return (1);
        }
        idx += 1;
    }
    idx = 0;
    while (idx < info->nbr_philos)
    {
        if (pthread_join(info->thread[idx], NULL))
        {
            print_error("\033[0;91m ❌ Failed to join thread\033[0m\n");
            return (1);
        }
        if (info->is_death == TRUE)
            return (1);
        idx += 1;
    }
    return (0);
}
