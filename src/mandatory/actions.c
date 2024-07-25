/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 12:54:47 by cdeville          #+#    #+#             */
/*   Updated: 2024/07/25 18:00:31 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

int	do_die(t_philo *philo)
{
	if (pthread_mutex_lock(&(philo->param->mutex_is_dead)))
		return (set_error(philo->param), 1);
	if (philo->param->is_dead == TRUE)
	{
		if (pthread_mutex_unlock(&(philo->param->mutex_is_dead)))
			return (set_error(philo->param), 1);
		return (0);
	}
	philo->param->is_dead = TRUE;
	usleep(50);
	do_print(DEAD, philo);
	if (pthread_mutex_unlock(&(philo->param->mutex_is_dead)))
		return (set_error(philo->param), 1);
	return (0);
}

int	do_eat(t_philo *philo)
{
	if (do_continue(philo) == FALSE)
	{
		if (pthread_mutex_unlock(philo->l_fork))
			return (set_error(philo->param), 1);
		if (pthread_mutex_unlock(philo->r_fork))
			return (set_error(philo->param), 1);
		return (0);
	}
	if (pthread_mutex_lock(&(philo->mutex_last_eat)))
		return (set_error(philo->param), 1);
	philo->last_eat = time_passed(philo->param->clock);
	if (pthread_mutex_unlock(&(philo->mutex_last_eat)))
		return (set_error(philo->param), 1);
	if (do_continue(philo))
		do_print(EAT, philo);
	usleep(philo->param->time_to_eat * 1000);
	if (pthread_mutex_unlock(philo->l_fork)
		|| pthread_mutex_unlock(philo->r_fork))
		return (set_error(philo->param), 1);
	return (0);
}

int	do_sleep(t_philo *philo)
{
	if (do_continue(philo))
	{
		do_print(SLEEP, philo);
		usleep(philo->param->time_to_sleep * 1000);
	}
	return (0);
}

int	do_think(t_philo *philo)
{
	if (do_continue(philo))
		do_print(THINK, philo);
	return (0);
}

void	odd_regulate(t_philo *philo)
{
	if (philo->param->number_of_philosophers % 2 == 0)
		return ;
	if (philo->param->time_to_sleep > 2 * philo->param->time_to_eat)
		return ;
	usleep(philo->param->time_to_eat * 1000);
}
