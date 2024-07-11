/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 14:44:10 by cdeville          #+#    #+#             */
/*   Updated: 2024/07/11 17:13:50 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers_bonus.h>

int	set_one_ate_enought(t_philo *philo)
{
	if (sem_wait(&(philo->sem_ate_enought)))
		return (set_error(philo->param), 1);
	philo->ate_enought = TRUE;
	if (sem_post(&(philo->sem_ate_enought)))
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
		do_die(&(philo));
		return (TRUE);
	}
	return (FALSE);
}

int	check_stop_conditions(t_philo *philo)
{
	while (1)
	{
		if (check_if_philo_died(philo))
			return (0);
		if (found_error(philo))
			return (1);
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

int	process_multi(t_philo *philo)
{
	pthread_t	actions;
	int			error;

	if (pthread_create(&actions, NULL, pthread_actions, philo))
		return (1);
	// print some error
	error = check_stop_conditions(&philo);
	if (pthread_join(actions, NULL))
		return (perror("pthread_join"), 1);
}

int	wait_for_all();

int	wait_valids();
