/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:41:40 by cdeville          #+#    #+#             */
/*   Updated: 2024/07/24 14:10:58 by cdeville         ###   ########.fr       */
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

void	odd_regulate(t_philo *philo)
{
	long	time;

	if (philo->param->number_of_philosophers % 2 == 0)
		return ;
	pthread_mutex_lock(&(philo->mutex_last_eat));
	time = time_passed(philo->param->clock) - philo->last_eat;
	pthread_mutex_unlock(&(philo->mutex_last_eat));
	if (time <= (1.1 * (philo->param->time_to_eat
				+ philo->param->time_to_eat)))
		usleep((philo->param->time_to_eat
				+ philo->param->time_to_eat) * 500);
}

void	*pthread_fct(void *argument)
{
	t_philo			*philo;
	int				count;

	count = 0;
	philo = (t_philo *)argument;
	while (do_continue(philo) == TRUE)
	{
		if (take_forks(philo))
			return (NULL);
		do_eat(philo);
		do_sleep(philo);
		do_think(philo);
		count++;
		if (count == philo->param->max_eat)
			set_one_ate_enought(philo);
		odd_regulate(philo);
	}
	return (NULL);
}

void	*pthread_fct_for_one(void *argument)
{
	t_philo			*philo;

	philo = (t_philo *)argument;
	if (pthread_mutex_lock(philo->r_fork))
	{
		set_error(philo->param);
		return (NULL);
	}
	if (pthread_mutex_unlock(philo->r_fork))
	{
		set_error(philo->param);
		return (NULL);
	}
	do_print(FORK, philo);
	return (NULL);
}

int	join_valids(t_philo_param *param, int size)
{
	int	status;
	int	return_status;

	status = 0;
	return_status = 0;
	while (size >= 0)
	{
		status = pthread_join(param->threads[size], NULL);
		if (status)
		{
			ft_putstr_fd("Error when joining\n", 2);
			return_status = status;
		}
		size--;
	}
	return (return_status);
}

int	join_all(t_philo_param *param)
{
	int	i;
	int	status;
	int	return_status;

	i = 0;
	status = 0;
	return_status = 0;
	while (i < param->number_of_philosophers)
	{
		status = pthread_join(param->threads[i], NULL);
		if (status)
		{
			ft_putstr_fd("Error when joining\n", 2);
			return_status = status;
		}
		i++;
	}
	return (return_status);
}
