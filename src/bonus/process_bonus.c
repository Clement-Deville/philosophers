/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 14:44:10 by cdeville          #+#    #+#             */
/*   Updated: 2024/07/25 17:59:44 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers_bonus.h>

void	set_one_ate_enought(t_philo *philo)
{
	if (do_continue(philo))
		sem_post(philo->param->sem_everyone_ate);
}

t_bool	do_terminate(t_philo *philo)
{
	t_bool	terminate;

	sem_wait(&(philo->sem_terminate));
	terminate = philo->terminate;
	sem_post(&(philo->sem_terminate));
	return (terminate);
}

int	process_multi(t_philo *philo)
{
	pthread_t	actions;
	pthread_t	term_monitor;

	if (pthread_create(&term_monitor, NULL, pthread_term, philo))
		return (perror("pthread_create"), set_error(philo->param), 1);
	if (pthread_create(&actions, NULL, pthread_actions, philo))
		return (perror("pthread_create"), pthread_join(term_monitor, NULL),
			set_error(philo->param), 1);
	check_stop_conditions(philo);
	if (pthread_join(actions, NULL) || pthread_join(term_monitor, NULL))
		return (perror("pthread_join"), set_error(philo->param), 1);
	clean_exit_child(philo->param);
	return (0);
}

int	process_one(t_philo *philo)
{
	pthread_t	actions;
	pthread_t	term_monitor;

	if (pthread_create(&term_monitor, NULL, pthread_term, philo))
		return (perror("pthread_create"), set_error(philo->param),
			clean_exit_child(philo->param), 1);
	if (pthread_create(&actions, NULL, pthread_actions_for_one,
			philo))
		return (perror("pthread_create"), set_error(philo->param),
			pthread_join(term_monitor, NULL),
			clean_exit_child(philo->param), 1);
	check_stop_conditions(philo);
	if (pthread_join(actions, NULL) || pthread_join(term_monitor, NULL))
		return (set_error(philo->param), clean_exit_child(philo->param), 1);
	clean_exit_child(philo->param);
	return (0);
}
