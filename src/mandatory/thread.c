/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:41:40 by cdeville          #+#    #+#             */
/*   Updated: 2024/04/20 17:28:53 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

int	set_one_ate_enought(t_philo *philo)
{
	if (pthread_mutex_lock(&(philo->mutex_ate_enought)))
		return (set_error(philo->param), 1);
	philo->ate_enought = TRUE;
	if (pthread_mutex_unlock(&(philo->mutex_ate_enought)))
		return (set_error(philo->param), 1);
	return (0);
}

void	*pthread_fct(void *argument)
{
	t_philo			*philo;
	int				count;

	count = 0;
	philo = (t_philo *)argument;
	while (do_continue(philo) == TRUE)
	{
		take_forks(philo);
		do_eat(philo);
		do_sleep(philo);
		do_think(philo);
		count++;
		if (count >= philo->param->max_eat)
			set_one_ate_enought(philo);
	}
	return (NULL);
}

int	join_valids(t_philo_param param, int size)
{
	int	status;
	int	return_status;
	int	thread_return;

	status = 0;
	return_status = 0;
	thread_return = 0;
	while (size >= 0)
	{
		status = pthread_join(param.threads[size], (void **)&thread_return);
		if (status)
		{
			ft_putstr_fd("Error when joining\n", 2);
			return_status = status;
		}
		if (thread_return)
			return_status = thread_return;
		size--;
	}
	return (return_status);
}

int	join_all(t_philo_param param)
{
	int	i;
	int	status;
	int	return_status;
	int	thread_return;

	i = 0;
	status = 0;
	return_status = 0;
	thread_return = 0;
	while (i < param.number_of_philosophers)
	{
		status = pthread_join(param.threads[i], (void **)&thread_return);
		if (status)
		{
			ft_putstr_fd("Error when joining\n", 2);
			return_status = status;
		}
		if (thread_return)
			return_status = thread_return;
		i++;
	}
	return (return_status);
}
