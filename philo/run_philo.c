/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_philo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotak <yotak@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 14:12:23 by yotak             #+#    #+#             */
/*   Updated: 2022/06/20 16:04:34 by yotak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    *fork(void *philo)
{
    t_philo *ph;

    ph = (t_philo *)philo;

}

void    run_philo(t_info *info)
{
    int p_create;
    int p_join;
    int idx;

    idx = 0;
    while (idx < info->nbr_philos)
    {
        p_create = pthread_create(info->thread[idx], NULL, &fork, &info->philo[idx]);
        if (p_create != 0)
        {
            print_error("❌ Failed to create thread\n");
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
            print_error("❌ Failed to join thread\n");
            return (1);
        }
        idx += 1;
    }
}