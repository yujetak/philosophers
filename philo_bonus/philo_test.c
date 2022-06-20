/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_test.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotak <yotak@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 19:45:53 by yotak             #+#    #+#             */
/*   Updated: 2022/06/20 15:06:44 by yotak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <time.h>

void    ft_printerr(char *err_msg)
{
    int len = 0;
    while (err_msg[len])
        len++;
    write(2, err_msg, len);
}

void*   roll_dice()
{ 
    int value = (rand() % 6) + 1;
    int* result = malloc(sizeof(int));
    *result = value;
    // printf("%d\n", value);
    printf("Thread result : %p\n", result);
    return ((void*) result);
}

int main()
{
    int*    res;
    srand(time(NULL));
    pthread_t   th;
    if (pthread_create(&th, NULL, &roll_dice, NULL) != 0)
        return 1;
    if (pthread_detach(th) != 0)
        return 2;
    printf("Thread result : %p\n", res);
    printf("Result : %d\n", *res);
    // (de)allocate free in the same function, same memory place
    // free(res);
    return 0;
}