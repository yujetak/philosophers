/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_philosopher.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotak <yotak@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 13:24:44 by yotak             #+#    #+#             */
/*   Updated: 2022/06/21 19:54:46 by yotak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    set_forks_mutex(t_info *info)
{
    int idx;

    idx = 0;
    info->m_forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * info->nbr_philos);
    while (idx < info->nbr_philos)
    {
        pthread_mutex_init(&info->m_forks[idx], NULL);
        idx += 1;
    }
}

void    set_forks_array(t_info *info)
{
    int idx;

    idx = 0;
    info->forks = (int *)malloc(sizeof(int) * info->nbr_philos);
    while (idx < info->nbr_philos)
    {
        info->forks[idx] = ON_TABLE;
        idx += 1;
    }
}

void    set_philo(t_info *info)
{
    int idx;

    idx = 0;
    info->philo = (t_philo *)malloc(sizeof(t_philo) * info->nbr_philos);
    while (idx < info->nbr_philos)
    {
        info->philo[idx].idx = idx;
        info->philo[idx].status = THINK;
        info->philo[idx].eat_cnt = 0;
        info->philo[idx].last_eat = 0;
        info->philo[idx].info_is_death = &info->is_death;
        info->philo[idx].info = info;
        if (idx == info->nbr_philos - 1)
            info->philo[idx].left_fork = 0;
        else
            info->philo[idx].left_fork = idx + 1;
        info->philo[idx].right_fork = idx;
        idx += 1;
    }
}

void    set_thread(t_info *info)
{
    info->thread = (pthread_t *)malloc(sizeof(pthread_t) * info->nbr_philos);
}