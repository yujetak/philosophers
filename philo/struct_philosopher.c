/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_philosopher.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotak <yotak@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 13:24:44 by yotak             #+#    #+#             */
/*   Updated: 2022/06/20 16:17:08 by yotak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    set_forks(t_info *info)
{
    int idx;

    idx = 0;
    while (idx < info->nbr_philos)
    {
        pthread_mutex_init(&info->forks[idx], NULL);
        idx += 1;
    }
}

void    set_philo(t_info *info)
{
    t_philo         *ph;
    int             idx;

    idx = 0;
    ph = (t_philo *)malloc(sizeof(t_philo) * info->nbr_philos);
    while (idx < info->nbr_philos)
    {
        ph[idx].idx = idx;
        ph[idx].eat_cnt = 0;
        ph[idx].status = THINK;
        if (idx == info->nbr_philos - 1)
            ph[idx].left_fork = &info->forks[0];
        else
            ph[idx].left_fork = &info->forks[idx + 1];
        ph[idx].right_fork = &info->forks[idx];
        idx += 1;
    }
    info->philo = ph;
}

void    set_thread(t_info *info)
{
    pthread_t   *th;

    th = (pthread_t *)malloc(sizeof(pthread_t) * info->nbr_philos);
    info->thread = th;
}