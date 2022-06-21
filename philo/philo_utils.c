/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotak <yotak@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 10:55:22 by yotak             #+#    #+#             */
/*   Updated: 2022/06/21 20:40:01 by yotak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long    get_time(void)
{
    struct timeval  current_time;
    
    gettimeofday(&current_time, NULL);
    return (current_time.tv_sec * 1000 + current_time.tv_usec / 100);
}

void    philo_status_print(t_philo *philo)
{
    pthread_mutex_lock(&philo->info->m_print);
    if (philo->status == TAKE_FORK)
        printf("🍴%ldms %d has taken a fork\n", get_time(), philo->idx);
    else if (philo->status == EAT)
        printf("🍽 %ldms %d is eating", 
}

void    philo_get_fork(t_philo *philo)
{
    //철학자 상태 갱신
    philo->status = TAKE_FORK;
    philo_status_print(philo);
    //포크를 들었다
    philo->info->forks[philo->left_fork] = IN_HAND;
    philo->info->forks[philo->right_fork] = IN_HAND;
    //print
}

void    philo_eat(t_philo *philo)
{
    philo->eat_cnt += 1;
    philo->start_eat = get_time();
    //마지막으로 먹은 시간 갱신
    philo->last_eat = get_time();
}