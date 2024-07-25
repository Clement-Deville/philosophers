/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 10:29:03 by cdeville          #+#    #+#             */
/*   Updated: 2024/07/25 17:05:35 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdlib.h>
# include <stdio.h>

# define TRUE 1
# define FALSE 0

# define DEAD 0
# define FORK 1
# define EAT 2
# define SLEEP 3
# define THINK 4
# define EVERYONE_ATE 5
# define CRITIC_ERROR 6

typedef int	t_bool;

typedef struct s_philo{
	long					philo_number;
	pthread_mutex_t			*l_fork;
	pthread_mutex_t			*r_fork;
	long					last_eat;
	pthread_mutex_t			mutex_last_eat;
	t_bool					ate_enought;
	pthread_mutex_t			mutex_ate_enought;
	struct s_philo_param	*param;
}	t_philo;

typedef struct s_philo_param{
	long			number_of_philosophers;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			max_eat;
	struct timeval	clock;
	pthread_t		*threads;
	t_philo			*philo_tab;
	t_bool			is_dead;
	t_bool			everyone_ate;
	t_bool			ready;
	int				error;
	pthread_mutex_t	*forks;
	pthread_mutex_t	mutex_is_dead;
	pthread_mutex_t	mutex_everyone_ate;
	pthread_mutex_t	mutex_error;
	pthread_mutex_t	print;
	pthread_mutex_t	mutex_ready;
}	t_philo_param;

// ACTIONS

int		do_die(t_philo *philo);
int		do_eat(t_philo *philo);
int		do_sleep(t_philo *philo);
int		do_think(t_philo *philo);
void	odd_regulate(t_philo *philo);

// CHECK

t_bool	someone_is_dead(t_philo_param *param);
int		check_if_someone_died(t_philo_param *param);
t_bool	do_continue(t_philo *philo);

// CLEAR

int		destroy_mutex_init_error(t_philo_param *param);
void	clean_init_error(t_philo_param *param);
int		destroy_mutex(t_philo_param *param);
int		clean_exit(t_philo_param *param);

// CREATE_PHILO

void	set_philo_param(t_philo_param *param);
int		set_philo_mutex(t_philo_param *param);
int		create_philo(t_philo_param *param);

// ERROR

void	set_error(t_philo_param *param);
t_bool	found_error(t_philo_param *param);

// FORKS

int		take_forks(t_philo *philo);

// INIT

int		init(t_philo_param *param, int argc, char *argv[]);

// is_valid_arg

t_bool	is_pos_int(char *arg);
t_bool	is_valid_parameters(int argc, char *argv[]);
int		number_size(char *number);

// MONITORING

int		check_stop_conditions(t_philo_param *param);

// PRINT

int		do_print(int message_id, t_philo *philo);

// THREAD

void	*pthread_fct(void *argument);
void	*pthread_fct_for_one(void *argument);
int		join_all(t_philo_param *param);
int		join_valids(t_philo_param *param, int size);

// TIME

long	get_time(void);
long	time_passed(const struct timeval start);

// UTILS

void	ft_putstr_fd(char *s, int fd);
int		ft_atoi(const char *nptr);

#endif
