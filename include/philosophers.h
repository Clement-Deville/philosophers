/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 10:29:03 by cdeville          #+#    #+#             */
/*   Updated: 2024/04/19 16:54:46 by cdeville         ###   ########.fr       */
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

typedef int	t_bool;

typedef struct s_philo{
	long			philo_number;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	long			last_eat;
	void			*param;
}	t_philo;

typedef struct s_philo_param{
	long			number_of_philosophers;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			number_of_times_each_philosopher_must_eat;
	t_philo			*philo_tab;
	pthread_mutex_t	*forks;
	pthread_t		*threads;
	pthread_mutex_t	mutex_is_dead;
	pthread_mutex_t	print;
	t_bool			is_dead;
	struct timeval	clock;
}	t_philo_param;

// CHECK

int		check_if_someone_died(t_philo_param *param);

// UTILS

void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
int		ft_atoi(const char *nptr);
long	get_time(void);

// PRINT

int		do_print(int message_id, t_philo *philo);

// THREAD

void	*pthread_fct(void *argument);
int		join_all(t_philo_param param);
long	time_passed(struct timeval start);
int		do_die(t_philo *philo);

// INIT

int		init(t_philo_param *param, int argc, char *argv[]);
#endif
