/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yotak <yotak@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 09:56:03 by yotak             #+#    #+#             */
/*   Updated: 2022/06/27 20:08:13 by yotak            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
//printf
# include <stdlib.h>
//malloc free
# include <unistd.h>
//usleep
# include <string.h>
//memset
# include <pthread.h>
//pthread_*
# include <sys/time.h>
//gettimeofday

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

typedef struct s_info	t_info;
typedef struct s_philo	t_philo;

struct s_info
{
	int				nbr_philos;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				nbr_eat_must;
	int				is_death;
	long			main_start_time;
	int				*forks;
	pthread_mutex_t	*m_forks;
	struct s_philo	**philo;
	pthread_mutex_t	m_print;
	pthread_mutex_t	m_start_line;
	pthread_mutex_t	m_time;
	pthread_mutex_t	m_death;
	pthread_t		*thread;
};

struct s_philo
{
	int				idx;
	int				left_fork;
	int				right_fork;
	int				status;
	int				eat_cnt;
	long			last_eat;
	pthread_mutex_t	m_eat;
	pthread_mutex_t	m_last_eat;
	t_info			*info;
};

/* philo.c */
void	print_error(const char *msg);
/* check_arg.c */
int		check_arg(int argc, char *argv[]);
/* check_arg_utils.c */
int		ft_atoi(const char *str);
size_t	ft_strlen(const char *str);
/* run_philo.c */
int		run_philo(t_info *in);
void	*routine(void *philo);
int		ft_pthread_join(t_info *in);
int		is_philo_death(t_philo *ph);
int		is_all_philo_eat(t_info *in);
/* philo_utils.c */
long	get_time(void);
long	get_timestamp(t_info *info);
void	philo_status_print(t_philo *ph);
void	ft_usleep(int status_end_time);
int		check_philo_terminate(t_info *in);
/* philo_utils2.c */
void	*no_country_for_alone_philo(t_philo *philo);
void	philo_get_fork(t_philo *philo);
void	philo_eat(t_philo *philo);
void	philo_sleep(t_philo *philo);
void	philo_think(t_philo *philo);
/* free.c */
void	free_info(t_info *info);
/* struct_info.c */
int		set_info(int argc, char *argv[], t_info *info);
/* set_info.c */
int		set_philo(t_info *info);
int		set_forks_array(t_info *info);
int		set_forks_mutex(t_info *info);
int		set_thread(t_info *info);

#endif
