/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 17:30:32 by cdeville          #+#    #+#             */
/*   Updated: 2024/07/25 16:02:46 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H

# include <semaphore.h>
# include <pthread.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdlib.h>
# include <stdio.h>
# include <signal.h>
# include <sys/wait.h>
# include <string.h>

# define TRUE 1
# define FALSE 0

# define DEAD 0
# define FORK 1
# define EAT 2
# define SLEEP 3
# define THINK 4
# define EVERYONE_ATE 5
# define CRITIC_ERROR 6

# define S_FORKS "/forks_count"
# define S_IS_DEAD "/is_dead"
# define S_EVERY "/everyone_ate"
# define S_ERR "/error"
# define S_PRINT "/print"
# define S_EATING "/philo_eating"
# define S_TAB "/pid_tab"
# define S_START "/start"
# define S_GLOBAL "/global_term"
# define S_CAN_DIE "/can_die"

typedef int	t_bool;

typedef struct s_philo{
	long					philo_number;
	long					last_eat;
	sem_t					sem_last_eat;
	t_bool					ate_enought;
	sem_t					sem_ate_enought;
	sem_t					sem_terminate;
	sem_t					sem_error;
	t_bool					error;
	t_bool					terminate;
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
	t_bool			stop;
	sem_t			sem_stop;
	t_bool			everyone_ate;
	int				error;
	sem_t			*forks_count;
	sem_t			*philo_eating;
	sem_t			*sem_is_dead;
	sem_t			*sem_everyone_ate;
	sem_t			*sem_print;
	pthread_t		eat_monitor;
	pthread_t		dead_monitor;
	pthread_t		error_monitor;
	sem_t			*sem_pid_tab;
	sem_t			*sem_global_terminate;
	sem_t			*sem_can_die;
	sem_t			*sem_error;
	sem_t			*sem_start;
}	t_philo_param;

// ACTIONS

int		do_die(t_philo *philo);
int		do_eat(t_philo *philo);
int		do_sleep(t_philo *philo);
int		do_think(t_philo *philo);
void	odd_regulate(t_philo *philo);

// CHECKS

int		check_stop_conditions(t_philo *philo);
t_bool	check_if_philo_died(t_philo *philo);

// CLEAR

void	clean_init_error(t_philo_param *param);
int		clean_exit(t_philo_param *param);
int		clean_exit_child(t_philo_param *param);
void	destroy_philo_sem(t_philo_param *param);

// CREATE_PHILO

int		create_philo(t_philo_param *param);

// DO_CONTINUE

int		do_continue(t_philo *philo);

// ERRORS

void	set_error(t_philo_param *param);

// FORKS

int		take_forks(t_philo *philo);

// INIT

int		init(t_philo_param *param, int argc, char *argv[]);
void	close_sem(t_philo_param *param);
int		unlink_sem(void);

// IS_VALID_ARG

t_bool	is_valid_parameters(int argc, char *argv[]);

// GLOBAL_MONITORING

int		init_global_monitoring(t_philo_param *param);
int		join_monitoring(t_philo_param *param);
int		term_childs(t_philo_param *param);

// PRINT

void	do_print(int message_id, t_philo *philo);

// PROCESS

int		process_one(t_philo *philo);
int		process_multi(t_philo *philo);
t_bool	do_terminate(t_philo *philo);
void	set_one_ate_enought(t_philo *philo);

// PTHREAD

void	*pthread_dead(void *argument);
void	*pthread_error(void *argument);
void	*pthread_eat(void *argument);
void	*pthread_term(void *argument);
void	*pthread_actions(void *argument);
void	*pthread_actions_for_one(void *argument);

// PTHREAD_FOR_ONE

void	*pthread_actions_for_one(void *argument);

// SEM_UTILS

int		unlink_sem(void);
void	close_sem(t_philo_param *param);
int		open_sem_others(t_philo_param *param);
int		init_sem(t_philo_param *param);
int		init_sem_child(t_philo_param *param);

// TIME

long	time_passed(const struct timeval start);
long	get_time(void);

// UTILS

void	ft_putstr_fd(char *s, int fd);
int		ft_atoi(const char *nptr);

// WAIT

int		kill_all_childs(t_philo_param *param);
int		wait_for_all(t_philo_param *param, int count);

#endif
