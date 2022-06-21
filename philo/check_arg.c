/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotak <yotak@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 09:11:04 by yotak             #+#    #+#             */
/*   Updated: 2022/06/21 10:45:13 by yotak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int check_arg(int argc, char *argv[])
{
    int idx;

    if ((argc == 5) || (argc == 6))
    {
        idx = 1;
        while (argv[idx])
        {
            if (ft_ato_pi(argv[idx]) == -1)
            {
                print_error("\033[0;91m ❌ Please input POSITIVE INTETGERs\033[0m\n");
                return (1);
            }
            idx += 1;
        }
    }
    else
    {
        print_error("\033[0;91m ❌ ./philo [philosophers] [die] [eat] [sleep] [opt]\033[0m\n");
        return (1);
    }
    return (0);
}
