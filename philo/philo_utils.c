/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotak <yotak@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 10:55:22 by yotak             #+#    #+#             */
/*   Updated: 2022/06/21 20:15:55 by yotak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long    get_time(void)
{
    struct timeval  current_time;
    
    gettimeofday(&current_time, NULL);
    return (current_time.tv_sec * 1000 + current_time.tv_usec / 100);
}

void    philo_get_fork(t_philo *philo)
{
    //먹은 횟수 +1
    philo->eat_cnt += 1;
    philo->info->forks[philo->left_fork] = IN_HAND;
    philo->info->forks[philo->right_fork] = IN_HAND;
    
    //마지막으로 먹은 시간 갱신
    philo->last_eat = get_time();
}