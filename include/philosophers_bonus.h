/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 17:30:32 by cdeville          #+#    #+#             */
/*   Updated: 2024/07/03 16:43:53 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H

# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>
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
	long					last_eat;
	sem_t					*sem_last_eat;
	t_bool					ate_enought;
	sem_t					*sem_ate_enought;
	struct s_philo_param	*param;
}	t_philo;

typedef struct s_philo_param{
	long			number_of_philosophers;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			max_eat;
	struct timeval	clock;
	int				*pid_tab;
	t_philo			*philo_tab;
	t_bool			is_dead;
	t_bool			everyone_ate;
	int				error;
	sem_t			*forks;
	sem_t			*sem_is_dead;
	sem_t			*sem_everyone_ate;
	sem_t			*sem_error;
	sem_t			*sem_print;
}	t_philo_param;

// MAIN

void	destroy_error(t_philo_param *param);

// CLEAR

void	clean_init_error(t_philo_param *param);

// CREATE_PHILO

int		create_philo(t_philo_param *param);

// IS_VALID_ARG

t_bool	is_valid_parameters(int argc, char *argv[]);

// UTILS

void	ft_putstr_fd(char *s, int fd);
int		ft_atoi(const char *nptr);

#endif
