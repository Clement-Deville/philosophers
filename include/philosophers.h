/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 10:29:03 by cdeville          #+#    #+#             */
/*   Updated: 2024/04/17 14:44:04 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <unistd.h>

# include <stdlib.h>
# include <stdio.h>

# define TRUE 0
# define FALSE 1

typedef int	t_bool;

typedef struct s_philo{
	long			philo_number;
	pthread_mutex_t	l_fork;
	pthread_mutex_t	r_fork;
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
}	t_philo_param;

// UTILS

void	ft_putstr_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
int		ft_atoi(const char *nptr);

// THREAD

void	*pthread_fct(void *argument);
int		join_all(t_philo_param param);

// INIT

int		init(t_philo_param *param, int argc, char *argv[]);
#endif
