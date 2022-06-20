/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotak <yotak@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 08:21:15 by yotak             #+#    #+#             */
/*   Updated: 2022/06/20 16:17:11 by yotak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> //printf 
#include <stdlib.h> //malloc free exit
#include <unistd.h> //fork usleep -> 어느정도 적당히(적게는 안됨) while문 내에서라면? 100이상은 줘야!
#include <signal.h> //kill
#include <pthread.h> //pthread_*
// if error occured, return not zero
#include <sys/time.h> //gettimeofday -> google!
#include <semaphore.h> //sem_*

#define FALSE 0
#define TRUE 1

enum e_status
{
    EAT,
    SLEEP,
    THINK
};

typedef struct s_info   t_info;
typedef struct s_philo  t_philo;

struct s_info
{
    int             nbr_philos;
    int             time_die;
    int             time_eat;
    int             time_sleep;
    int             nbr_eat_must;
    struct s_philo  *philo;    
    pthread_mutex_t *forks;
    pthread_t       *thread;
};

struct s_philo
{
    int             idx;
    int             status;
    int             eat_cnt;
    pthread_mutex_t *left_fork;
    pthread_mutex_t *right_fork;
};

/* philo.c */
void    print_error(const char *msg);
/* check_arg.c */
int     check_arg(int argc, char *argv[]);
/* check_arg_utils.c */
int     is_nbr(const char c);
size_t	ft_strlen(const char *str);
int     ft_ato_pi(const char *str);
/* struct_info.c */
t_info  *init_info(t_info *info);
void    set_info(int argc, char *argv[], t_info *info);
void    print_info(t_info *info);
/* struct_philosopher.c */
void    set_forks(t_info *info);
void    set_philo(t_info *info);
void    set_thread(t_info *info);
/* run_philo.c */
void    run_philo(t_info *info);
/* free.c */
void    free_info(t_info *info);