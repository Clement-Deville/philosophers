/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 12:54:47 by cdeville          #+#    #+#             */
/*   Updated: 2024/04/20 17:43:10 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

int	do_die(t_philo *philo)
{
	pthread_mutex_lock(&(philo->param->mutex_is_dead));
	if (philo->param->is_dead == TRUE)
	{
		pthread_mutex_unlock(&(philo->param->mutex_is_dead));
		return (0);
	}
	philo->param->is_dead = TRUE;
	usleep(50);
	do_print(DEAD, philo);
	pthread_mutex_unlock(&(philo->param->mutex_is_dead));
	return (0);
}

int	do_eat(t_philo *philo)
{
	philo->last_eat = time_passed(philo->param->clock);
	if (is_someone_is_dead(philo->param) == FALSE)
	{
		do_print(EAT, philo);
		usleep(philo->param->time_to_eat * 1000);
	}
	philo->last_eat = time_passed(philo->param->clock);
	if (pthread_mutex_unlock(philo->l_fork))
		return (ft_putstr_fd("Mutex unlock error\n", 2), 1);
	if (pthread_mutex_unlock(philo->r_fork))
		return (ft_putstr_fd("Mutex unlock error\n", 2), 1);
	return (0);
}

int	do_sleep(t_philo *philo)
{
	if (is_someone_is_dead(philo->param) == FALSE)
	{
		do_print(SLEEP, philo);
		usleep(philo->param->time_to_sleep * 1000);
	}
	return (0);
}

int	do_think(t_philo *philo)
{
	if (is_someone_is_dead(philo->param) == FALSE)
		do_print(THINK, philo);
	return (0);
}
