/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotak <yotak@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 08:26:25 by yotak             #+#    #+#             */
/*   Updated: 2022/06/20 14:57:52 by yotak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int mails = 0;
pthread_mutex_t mutex;

void*   routine()
{
    for (int i = 0; i < 4200000; i++)
    {
        pthread_mutex_lock(&mutex);
        mails += 1;
        pthread_mutex_unlock(&mutex);
        // read mails
        // increment
        // write mails
    }
}
//  Philosophers with threads and mutexes --> Check Data races
int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;
    int *res;
    pthread_t   threads[4];
    pthread_mutex_init(&mutex, NULL);
    for (int t = 0; t < 4; t++)
    {
        // only one thread executing at a time
        if (pthread_create(threads + t, NULL, &routine, NULL) != 0)
        {
            perror("Faild to create thread\n");
            return (1);
        }
        printf("\033[0;92m🔫 Thread %d has started\033[0m\n", t);
    }
    for (int t = 0; t < 4; t++)
    {
        if (pthread_join(threads[t], NULL) != 0)
        {
            perror("Failed to terminate thread\n");
            return (2);
        }
        printf("\033[0;96m😈 Thread %d has finished execution\033[0m\n", t);
    }
    pthread_mutex_destroy(&mutex);
    printf("Number of mails : %d\n", mails);
    return (0);
}