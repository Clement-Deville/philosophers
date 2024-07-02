/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 12:56:47 by cdeville          #+#    #+#             */
/*   Updated: 2024/07/02 15:16:19 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

int	take_left(t_philo *philo)
{
	if (pthread_mutex_lock(philo->l_fork))
	{
		set_error(philo->param);
		if (philo->philo_number % 2 == 1)
			pthread_mutex_unlock(philo->r_fork);
		return (1);
	}
	if (do_continue(philo))
		do_print(FORK, philo);
	return (0);
}

int	take_right(t_philo *philo)
{
	if (pthread_mutex_lock(philo->r_fork))
	{
		set_error(philo->param);
		if (philo->philo_number % 2 == 0)
			pthread_mutex_unlock(philo->l_fork);
		return (1);
	}
	if (do_continue(philo))
		do_print(FORK, philo);
	return (0);
}

int	take_forks(t_philo *philo)
{
	if (philo->philo_number % 2 == 0)
	{
		if (take_left(philo) || take_right(philo))
			return (1);
	}
	else
	{
		if (take_right(philo) || take_left(philo))
			return (1);
	}
	return (0);
}
