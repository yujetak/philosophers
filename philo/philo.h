/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotak <yotak@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 08:21:15 by yotak             #+#    #+#             */
/*   Updated: 2022/06/23 16:23:16 by yotak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h> //printf
#include <stdlib.h> //malloc free
#include <unistd.h> //fork usleep -> 어느정도 적당히(적게는 안됨) while문 내에서라면? 100이상은 줘야!
#include <string.h> //memset
// #include <signal.h> //(bonus)kill
#include <pthread.h> //pthread_*
// if error occured, return not zero
#include <sys/time.h> //gettimeofday -> google!
// #include <semaphore.h> //(bonus_sem_*

enum e_bool
{
    FALSE,
    TRUE
};

enum e_philo_status
{
    THINK,
    TAKE_FORK,
    EAT,
    SLEEP
};

enum e_fork_status
{
    ON_TABLE,
    IN_HAND
};

typedef struct s_info   t_info;
typedef struct s_philo  t_philo;

struct s_info
{
    int             nbr_philos;
    int            time_die;
    int            time_eat;
    int            time_sleep;
    unsigned int    nbr_eat_must;
    int             is_death;
    long            main_start_time;
    int             *forks;
    pthread_mutex_t *m_forks;
    struct s_philo  *philo;
    pthread_mutex_t m_print;
    pthread_mutex_t m_sleep;
    pthread_mutex_t m_time;
    pthread_mutex_t m_death;
    pthread_t       *thread;
};

struct s_philo
{
    int             idx;
    int             left_fork;
    int             right_fork;
    int             status;
    int             eat_cnt;
    long            status_start;
    long            last_eat;
    t_info          *info;
};

/* philo.c */
void    print_error(const char *msg);
/* philo_utils.c */
long    get_time(void);
void    philo_status_print(t_philo *philo);
void    philo_get_fork(t_philo *philo);
void    ft_usleep(int status_end_time);
void    philo_eat(t_philo *philo);
void    philo_sleep(t_philo *philo);
void    philo_think(t_philo *philo);
int     is_philo_death(t_philo *philo);
/* check_arg.c */
int     check_arg(int argc, char *argv[]);
/* check_arg_utils.c */
int     is_nbr(const char c);
size_t	ft_strlen(const char *str);
int     ft_ato_pi(const char *str);
/* struct_info.c */
void    init_info(t_info *info);
void    set_info(int argc, char *argv[], t_info *info);
void    print_info(t_info *info);
void    print_philo_info(t_info *info);
/* struct_philosopher.c */
void    set_forks_mutex(t_info *info);
void    set_forks_array(t_info *info);
void    set_philo(t_info *info);
void    set_thread(t_info *info);
/* run_philo.c */
int     run_philo(t_info *info);
/* free.c */
void    free_info(t_info *info);
