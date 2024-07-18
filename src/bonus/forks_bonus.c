/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 15:02:34 by cdeville          #+#    #+#             */
/*   Updated: 2024/07/18 17:38:04 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers_bonus.h>

int	take_forks(t_philo *philo)
{
	t_philo_param	*param;

	param = philo->param;
	sem_wait(param->philo_eating);
	sem_wait(param->forks_count);
	sem_wait(param->forks_count);
	if (do_continue(philo) == FALSE)
		return (sem_post(param->philo_eating),
			sem_post(param->forks_count),
			sem_post(param->forks_count), 0);
	do_print(FORK, philo);
	do_print(FORK, philo);
	return (0);
}
