/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_info.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotak <yotak@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 10:30:16 by yotak             #+#    #+#             */
/*   Updated: 2022/06/21 19:50:06 by yotak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_info  *init_info(t_info *info)
{
    info->nbr_philos = 0;
    info->time_die = 0;
    info->time_eat = 0;
    info->time_sleep = 0;
    info->nbr_eat_must = -1;
    info->is_death = FALSE;
    info->timestamp = 0;
    info->forks = NULL;
    info->philo = NULL;
    info->m_forks = NULL;
    info->thread = NULL;
    return(info);
}

void    set_info(int argc, char *argv[], t_info *info)
{
    info = init_info(info);
    info->nbr_philos = ft_ato_pi(argv[1]);
    info->time_die = ft_ato_pi(argv[2]);
    info->time_eat = ft_ato_pi(argv[3]);
    info->time_sleep = ft_ato_pi(argv[4]);
    if (argc == 6)
        info->nbr_eat_must = ft_ato_pi(argv[5]);
    info->timestamp = get_time();
    set_forks_mutex(info);
    set_philo(info);
    set_forks_array(info);
    pthread_mutex_init(&info->m_print, NULL);
    pthread_mutex_init(&info->m_sleep, NULL);
    set_thread(info);
}

void    print_info(t_info *info)
{
    printf("======================[info]======================\n");
    printf("\033[0;92m🦄 1. number of philos : %d \033[0m\n", info->nbr_philos);
    printf("\033[0;92m🦄 2. time to die : %d \033[0m\n", info->time_die);
    printf("\033[0;92m🦄 3. time to eat : %d \033[0m\n", info->time_eat);
    printf("\033[0;92m🦄 4. time to sleep : %d \033[0m\n", info->time_sleep);
    printf("\033[0;92m🦄 opt. number of must eat : %d \033[0m\n", info->nbr_eat_must);
}
