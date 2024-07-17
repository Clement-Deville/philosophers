/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 14:44:10 by cdeville          #+#    #+#             */
/*   Updated: 2024/07/17 17:57:52 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers_bonus.h>

int	set_one_ate_enought(t_philo *philo)
{
	if (sem_post(philo->param->sem_everyone_ate))
		return (set_error(philo->param), 1);
	return (0);
}

t_bool	check_if_philo_died(t_philo *philo)
{
	long	timer;

	if (sem_wait(&(philo->sem_last_eat)))
		return (set_error(philo->param), FALSE);
	timer = time_passed(philo->param->clock) - philo->last_eat;
	if (sem_post(&(philo->sem_last_eat)))
		return (set_error(philo->param), FALSE);
	if (timer >= philo->param->time_to_die)
	{
		do_die(philo);
		return (TRUE);
	}
	return (FALSE);
}

int	found_error(t_philo *philo)
{
	(void)philo;
	return (FALSE);
}

t_bool	do_terminate(t_philo *philo)
{
	t_bool	terminate;

	if (sem_wait(&(philo->sem_terminate)))
		return (set_error(philo->param), FALSE);
	terminate = philo->terminate;
	if (sem_post(&(philo->sem_terminate)))
		return (set_error(philo->param), FALSE);
	return (terminate);
}

int	check_stop_conditions(t_philo *philo)
{
	while (1)
	{
		if (check_if_philo_died(philo))
			return (0);
		if (found_error(philo))
			return (1);
		if (do_terminate(philo))
			return (0);
		usleep(50);
	}
}

void	*pthread_actions(void *argument)
{
	int		count;
	t_philo	*philo;

	philo = (t_philo *)argument;
	count = 0;
	while (do_continue(philo) == TRUE)
	{
		if (take_forks(philo))
			return (NULL);
		do_eat(philo);
		do_sleep(philo);
		do_think(philo);
		count++;
		if (count == philo->param->max_eat)
			set_one_ate_enought(philo);
	}
	return (NULL);
}

void	*pthread_term(void *argument)
{
	t_philo	*philo;

	philo = (t_philo *)argument;
	if (sem_wait(philo->param->sem_global_terminate))
		return (set_error(philo->param), NULL);
	if (sem_wait(&(philo->sem_terminate)))
		return (set_error(philo->param), NULL);
	philo->terminate = TRUE;
	if (sem_post(&(philo->sem_terminate)))
		return (set_error(philo->param), NULL);
	return (NULL);
}

int	process_multi(t_philo *philo)
{
	pthread_t	actions;
	pthread_t	term_monitor;
	int			error;

	if (pthread_create(&term_monitor, NULL, pthread_term, philo))
		return (1);
	if (pthread_create(&actions, NULL, pthread_actions, philo))
		return (1);
	// print some error
	error = check_stop_conditions(philo);
	if (pthread_join(actions, NULL) || pthread_join(term_monitor, NULL))
		return (perror("pthread_join"), 1);
	return (error);
}
