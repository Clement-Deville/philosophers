/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 15:02:34 by cdeville          #+#    #+#             */
/*   Updated: 2024/07/09 15:14:54 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers_bonus.h>

int	take_forks(t_philo *philo)
{
	t_philo_param	*param;

	param = philo->param;
	if (sem_wait(&(param->philo_eating)))
		return (perror("sem_wait"), 1);
	if (sem_wait(&(param->forks_count)))
		return (sem_post(&(param->philo_eating)), perror("sem_wait"), 1);
	if (sem_wait(&(param->forks_count)))
		return (sem_post(&(param->philo_eating)),
		sem_post(&(param->philo_eating)),
		perror("sem_wait"), 1);
	return (0);
}
