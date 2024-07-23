/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 14:44:10 by cdeville          #+#    #+#             */
/*   Updated: 2024/07/23 16:45:05 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers_bonus.h>

void	set_one_ate_enought(t_philo *philo)
{
	if (do_continue(philo))
		sem_post(philo->param->sem_everyone_ate);
}

t_bool	check_if_philo_died(t_philo *philo)
{
	long	timer;

	sem_wait(&(philo->sem_last_eat));
	timer = time_passed(philo->param->clock) - philo->last_eat;
	sem_post(&(philo->sem_last_eat));
	if (timer >= philo->param->time_to_die)
	{
		do_die(philo);
		return (TRUE);
	}
	return (FALSE);
}

t_bool	do_terminate(t_philo *philo)
{
	t_bool	terminate;

	sem_wait(&(philo->sem_terminate));
	terminate = philo->terminate;
	sem_post(&(philo->sem_terminate));
	return (terminate);
}

int	check_stop_conditions(t_philo *philo)
{
	while (1)
	{
		if (check_if_philo_died(philo))
			return (0);
		if (do_terminate(philo))
			return (0);
		usleep(5000);
		// old value == 50
	}
}

int	process_multi(t_philo *philo)
{
	pthread_t	actions;
	pthread_t	term_monitor;

	if (pthread_create(&term_monitor, NULL, pthread_term, philo))
		return (set_error(philo->param), 1);
	if (pthread_create(&actions, NULL, pthread_actions, philo))
		return (set_error(philo->param), 1);
	// print some error and join term
	check_stop_conditions(philo);
	if (pthread_join(actions, NULL) || pthread_join(term_monitor, NULL))
		return (set_error(philo->param), 1);
	clean_exit_child(philo->param);
	return (0);
}

int	process_one(t_philo *philo)
{
	pthread_t	actions;
	pthread_t	term_monitor;

	if (pthread_create(&term_monitor, NULL, pthread_term, philo))
		return (set_error(philo->param), 1);
	if (pthread_create(&actions, NULL, pthread_actions_for_one,
			philo))
		return (set_error(philo->param), 1);
	// print some error
	check_stop_conditions(philo);
	if (pthread_join(actions, NULL) || pthread_join(term_monitor, NULL))
		return (set_error(philo->param), 1);
	clean_exit_child(philo->param);
	return (0);
}
