/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotak <yotak@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 14:12:23 by yotak             #+#    #+#             */
/*   Updated: 2022/06/21 20:19:25 by yotak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void    *philo_routine(t_philo *ph)
{
    if ((ph->idx % 2) == 0)
        usleep(100);
    while (&ph->info_is_death == TRUE)
    {
        pthread_mutex_lock(&ph->info->m_forks[ph->right_fork]);
        pthread_mutex_lock(&ph->info->m_forks[ph->left_fork]);
        //포크 잡고
        philo_get_fork(ph);
        //먹고
        //자고
        usleep(100);
        pthread_mutex_unlock(&ph->info->m_forks[ph->right_fork]);
        pthread_mutex_unlock(&ph->info->m_forks[ph->left_fork]);
    }
    return ((void *) 0);
}

int run_philo(t_info *info)
{
    int p_create;
    int p_join;
    int idx;

    idx = 0;
    while (idx < info->nbr_philos)
    {
        p_create = pthread_create(&info->thread[idx], NULL, &philo_routine, &info->philo[idx]);
        if (p_create != 0)
        {
            print_error("\033[0;91m ❌ Failed to create thread\033[0m\n");
            return (1);
        }
        idx += 1;
    }
    idx = 0;
    while (idx < info->nbr_philos)
    {
        p_join = pthread_join(info->thread[idx], NULL);
        if (p_join != 0)
        {
            print_error("\033[0;91m ❌ Failed to join thread\033[0m\n");
            return (1);
        }
        idx += 1;
    }
    return (0);
}