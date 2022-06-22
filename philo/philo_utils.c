/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotak <yotak@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/21 10:55:22 by yotak             #+#    #+#             */
/*   Updated: 2022/06/22 10:51:57 by yotak            ###   ########.fr       */
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
    {
        philo->status_start = get_time();
        printf("🍽 %ldms %d is eating", philo->status_start, philo->idx);
    }
    else if (philo->status == SLEEP)
        printf("🛌 %ldms %d is sleeping", get_time(), philo->idx);
    else if (philo->status == THINK)
        printf("🤔 %ldms %d is thinking", get_time(), philo->idx);
    pthread_mutex_unlock(&philo->info->m_print);
}

void    philo_get_left_fork(t_philo *philo)
{
    //철학자 상태 갱신
    philo->status = TAKE_FORK;
    philo_status_print(philo);
    //포크를 들었다
    philo->info->forks[philo->left_fork] = IN_HAND;
}

void    philo_get_right_fork(t_philo *philo)
{
    //철학자 상태 갱신
    philo->status = TAKE_FORK;
    philo_status_print(philo);
    //포크를 들었다
    philo->info->forks[philo->right_fork] = IN_HAND;
}

void    ft_usleep(int status_end_time)
{
    long    target_time;

    target_time = status_end_time + get_time();
    while (target_time > get_time())
        usleep(100);
}

void    philo_eat(t_philo *philo)
{
    int die->time;

    pthread_mutex_lock(&philo->info->m_time);
    die->time = philo->info->time_eat;
    pthread_mutex_unlock(&philo->info->m_time);
    philo->status_start = get_time();
    philo->status = EAT;
    philo->eat_cnt += 1;
    philo_status_print(philo);
    // 모니터링에서 status를 바꿔준다면 상태도 뮤텍스를 걸어야!
    // 🥕 공유변수를 지역변수로 받아오고 뮤텍스걸고 사용하기
    // 방법2. ft_sleep()
    // 목표시각 = 상태 소요 시간 + 현재시각
    // while(목표시간 > 현재시각)
    // usleep(100)
    ft_usleep(die->time);
    philo->last_eat = get_time();
    philo->status_start = 0;
    philo->info->forks[philo->left_fork] = ON_TABLE;
    philo->info->forks[philo->right_fork] = ON_TABLE;
}

void    philo_sleep(t_philo *philo)
{
    int sleep_time;

    philo->status = SLEEP;
    pthread_mutex_lock(&philo->info->m_time);
    sleep_time = philo->info->time_sleep;
    pthread_mutex_unlock(&philo->info->m_time);
    philo->status_start = get_time();
    philo_status_print(philo);
    ft_usleep(sleep_time);
}

void    is_philo_death(t_philo *philo)
{
    int is_death;
    int die_time;

    pthread_mutex_lock(&philo->info->m_death);
    is_death = philo->info->is_death;
    pthread_mutex_unlock(&philo->info->m_death);
    pthread_mutex_lock(&philo->info->m_time);
    die_time = philo->info->time_die;
    pthread_mutex_unlock(&philo->info->m_time);
    if (is_death == TRUE || ((get_time() - philo->last_eat) > die_time))
    {
        pthread_mutex_lock(&philo->info->m_death);
        philo->info->is_death = TRUE;
        pthread_mutex_unlock(&philo->info->m_death);
        printf("⚰️ %ldms %d is died\n", get_time(), philo->idx);
        return (TRUE);
    }
    return (FALSE);
}