/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotak <yotak@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/19 13:08:58 by yotak             #+#    #+#             */
/*   Updated: 2022/06/24 14:39:24 by yotak            ###   ########.fr       */
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
    run_philo(info);
    return (0);
}

void    print_error(const char *msg)
{
    write(2, msg, ft_strlen(msg));
}
