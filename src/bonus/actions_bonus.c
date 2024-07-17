/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 14:46:14 by cdeville          #+#    #+#             */
/*   Updated: 2024/07/17 18:08:10 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers_bonus.h>

int	do_die(t_philo *philo)
{
	if (sem_post(philo->param->sem_is_dead))
		return (set_error(philo->param), 1);
	// if (sem_wait(&(philo->sem_terminate)))
	// 	return (set_error(philo->param), 1);
	// philo->terminate = TRUE;
	usleep(50);
	do_print(DEAD, philo);
	return (0);
}

int	do_eat(t_philo *philo)
{
	//verif error
	// printf("do_eat called by %ld\n", philo->philo_number);
	// // a retirer
	if (do_continue(philo) == FALSE)
	{
		if (sem_post(philo->param->forks_count))
			return (set_error(philo->param), 1);
		if (sem_post(philo->param->forks_count))
			return (set_error(philo->param), 1);
		if (sem_post(philo->param->philo_eating))
			return (set_error(philo->param), 1);
		return (0);
	}
	if (sem_wait(&(philo->sem_last_eat)))
		return (set_error(philo->param), 1);
	philo->last_eat = time_passed(philo->param->clock);
	if (sem_post(&(philo->sem_last_eat)))
		return (set_error(philo->param), 1);
	if (do_continue(philo))
		do_print(EAT, philo);
	usleep(philo->param->time_to_eat * 1000);
	if (sem_wait(&(philo->sem_last_eat)))
		return (set_error(philo->param), 1);
	philo->last_eat = time_passed(philo->param->clock);
	if (sem_post(&(philo->sem_last_eat)))
		return (set_error(philo->param), 1);
	if (sem_post(philo->param->forks_count)
		|| sem_post(philo->param->forks_count)
		|| sem_post(philo->param->philo_eating))
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
