/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 15:56:38 by cdeville          #+#    #+#             */
/*   Updated: 2024/07/25 16:03:59 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers_bonus.h>

int	check_stop_conditions(t_philo *philo)
{
	while (1)
	{
		if (check_if_philo_died(philo))
			return (0);
		if (do_terminate(philo))
			return (0);
		usleep(50);
	}
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
