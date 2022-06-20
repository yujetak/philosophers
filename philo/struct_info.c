/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_info.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotak <yotak@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 10:30:16 by yotak             #+#    #+#             */
/*   Updated: 2022/06/20 15:59:27 by yotak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_info  *init_info(t_info *info)
{
    info = (t_info *)malloc(sizeof(t_info));
    info->nbr_philos = 0;
    info->time_die = 0;
    info->time_eat = 0;
    info->time_sleep = 0;
    info->nbr_eat_must = -1;
    info->forks = NULL;
    info->thread = NULL;
    return(info);
}

void    set_info(int argc, char *argv[], t_info *info)
{
    t_info  *info;

    info = NULL;
    info = init_info(info);
    info->nbr_philos = ft_ato_pi(argv[1]);
    info->time_die = ft_ato_pi(argv[2]);
    info->time_eat = ft_ato_pi(argv[3]);
    info->time_sleep = ft_ato_pi(argv[4]);
    if (argc == 6)
        info->nbr_eat_must = ft_ato_pi(argv[5]); 
    set_forks(info);
    set_thread(info);
}

void    print_info(t_info *info)
{
    printf("📬 [info]\n");
    printf("1. number of philos : %d\n", info->nbr_philos);
    printf("2. time to die : %d\n", info->time_die);
    printf("3. time to eat : %d\n", info->time_eat);
    printf("4. time to sleep : %d\n", info->time_sleep);
    printf("opt. number of must eat : %d\n", info->nbr_eat_must);
}
