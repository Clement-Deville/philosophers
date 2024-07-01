/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 10:29:03 by cdeville          #+#    #+#             */
/*   Updated: 2024/07/01 13:58:41 by cdeville         ###   ########.fr       */
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
	int				error;
	pthread_mutex_t	*forks;
	pthread_mutex_t	mutex_is_dead;
	pthread_mutex_t	mutex_everyone_ate;
	pthread_mutex_t	mutex_error;
	pthread_mutex_t	print;
}	t_philo_param;

// ACTIONS

int		do_die(t_philo *philo);
int		do_eat(t_philo *philo);
int		do_sleep(t_philo *philo);
int		do_think(t_philo *philo);

// CHECK

t_bool	is_someone_is_dead(t_philo_param *param);
int		check_if_someone_died(t_philo_param *param);
t_bool	do_continue(t_philo *philo);

// ERROR

void	set_error(t_philo_param *param);
t_bool	found_error(t_philo_param *param);

// FORKS

int		take_forks(t_philo *philo);

// INIT

int		init(t_philo_param *param, int argc, char *argv[]);

// MONITORING

int		check_stop_conditions(t_philo_param *param);

// PRINT

int		do_print(int message_id, t_philo *philo);

// THREAD

void	*pthread_fct(void *argument);
int		join_all(t_philo_param param);
int		join_valids(t_philo_param param, int size);

// TIME

long	get_time(void);
long	time_passed(const struct timeval start);

// UTILS

void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
int		ft_atoi(const char *nptr);

#endif
