/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 12:56:47 by cdeville          #+#    #+#             */
/*   Updated: 2024/04/20 17:44:31 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

int	take_left(t_philo *philo)
{
	if (pthread_mutex_lock(philo->l_fork))
		return (ft_putstr_fd("Mutex lock error\n", 2), 1);
	if (is_someone_is_dead(philo->param) == FALSE)
		do_print(FORK, philo);
	return (0);
}

int	take_right(t_philo *philo)
{
	if (pthread_mutex_lock(philo->r_fork))
		return (ft_putstr_fd("Mutex lock error\n", 2), 1);
	if (is_someone_is_dead(philo->param) == FALSE)
		do_print(FORK, philo);
	return (0);
}

int	take_forks(t_philo *philo)
{
	if (philo->philo_number % 2 == 0)
	{
		take_left(philo);
		take_right(philo);
	}
	else
	{
		take_right(philo);
		take_left(philo);
	}
	return (0);
}
