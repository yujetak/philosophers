/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_info.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotak <yotak@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 10:30:16 by yotak             #+#    #+#             */
/*   Updated: 2022/06/26 20:51:51 by yotak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	 init_info(t_info *info)
{
    memset((void *)info, 0, sizeof(t_info));
	if (!info)
		return (1);
    info->nbr_eat_must = -1;
	return (0);
}

int	set_info(int argc, char *argv[], t_info *info)
{
    if (init_info(info))
		return (1);
    info->nbr_philos = ft_ato_pi(argv[1]);
    info->time_die = ft_ato_pi(argv[2]);
    info->time_eat = ft_ato_pi(argv[3]);
    info->time_sleep = ft_ato_pi(argv[4]);
    if (argc == 6)
        info->nbr_eat_must = ft_ato_pi(argv[5]);
    info->main_start_time = get_time();
    if (set_forks_mutex(info))
		return (1);
    if (set_philo(info))
		return (1);
    if (set_forks_array(info))
		return (1);
    if (pthread_mutex_init(&info->m_print, NULL))
		return (1);
    if (pthread_mutex_init(&info->m_time, NULL))
		return (1);
	if (pthread_mutex_init(&info->m_death, NULL))
		return (1);
    if (pthread_mutex_init(&info->m_start_line, NULL))
		return (1);
    if (set_thread(info))
		return (1);
	return (0);
}

// void    print_info(t_info *info)
// {
//     printf("======================[info]======================\n");
//     printf("\033[0;92m🦄 1. number of philos : %d \033[0m\n", info->nbr_philos);
//     printf("\033[0;92m🦄 2. time to die : %ld \033[0m\n", info->time_die);
//     printf("\033[0;92m🦄 3. time to eat : %ld \033[0m\n", info->time_eat);
//     printf("\033[0;92m🦄 4. time to sleep : %ld \033[0m\n", info->time_sleep);
//     printf("\033[0;92m🦄 opt. number of must eat : %d \033[0m\n", info->nbr_eat_must);
// }

// void    print_philo_info(t_info *info)
// {
//     t_philo *ph;
//     int     idx;

//     idx = 0;
//     while (idx < info->nbr_philos)
//     {
//         ph = &info->philo[idx];
//         printf("Q. ph : %p, &info->philo[idx] : %p\n", ph, &info->philo[idx]);
//         printf("======================[info->philo - %d]======================\n", ph->idx);
//         printf("🍴1. status %d\n", ph->status);
//         printf("🍴2. left_fork %d\n", ph->left_fork);
//         printf("🍴3. right_fork %d\n", ph->right_fork);
//         printf("🍴4. eat_cnt %d\n", ph->eat_cnt);
//         idx += 1;
//     }
//}
