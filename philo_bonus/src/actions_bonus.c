/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 14:46:14 by cdeville          #+#    #+#             */
/*   Updated: 2024/07/25 18:00:09 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers_bonus.h>

int	do_die(t_philo *philo)
{
	sem_post(philo->param->sem_is_dead);
	if (do_continue(philo))
		do_print(DEAD, philo);
	return (0);
}

int	do_eat(t_philo *philo)
{
	if (do_continue(philo) == FALSE)
	{
		sem_post(philo->param->forks_count);
		sem_post(philo->param->forks_count);
		sem_post(philo->param->philo_eating);
		return (0);
	}
	sem_wait(&(philo->sem_last_eat));
	philo->last_eat = time_passed(philo->param->clock);
	sem_post(&(philo->sem_last_eat));
	if (do_continue(philo))
		do_print(EAT, philo);
	usleep(philo->param->time_to_eat * 1000);
	sem_post(philo->param->forks_count);
	sem_post(philo->param->forks_count);
	sem_post(philo->param->philo_eating);
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
