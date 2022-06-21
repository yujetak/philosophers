/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotak <yotak@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 13:08:58 by yotak             #+#    #+#             */
/*   Updated: 2022/06/21 20:04:42 by yotak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char *argv[])
{
    t_info  *info;

    info = (t_info *)malloc(sizeof(t_info));
    if (check_arg(argc, argv))
        return (1);
    set_info(argc, argv, info);
    if (run_philo(info))
        return (1);
    // print_info(info);
    // check_philo_death(info);
    free_info(info);
    return (0);
}

void    print_error(const char *msg)
{
    write(2, msg, ft_strlen(msg));
}
