/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 13:49:53 by cdeville          #+#    #+#             */
/*   Updated: 2024/07/02 12:50:53 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

t_bool	check_if_someone_died(t_philo_param *param)
{
	int		i;
	long	timer;

	i = 0;
	while (i < param->number_of_philosophers)
	{
		if (pthread_mutex_lock(&(param->philo_tab[i].mutex_last_eat)))
			return (set_error(param), FALSE);
		timer = time_passed(param->clock) - param->philo_tab[i].last_eat;
		if (pthread_mutex_unlock(&(param->philo_tab[i].mutex_last_eat)))
			return (set_error(param), FALSE);
		if (timer >= param->time_to_die)
		{
			do_die(&(param->philo_tab[i]));
			return (TRUE);
		}
		i++;
	}
	return (FALSE);
}

int	set_everyone_ate(t_philo_param *param)
{
	if (pthread_mutex_lock(&(param->mutex_everyone_ate)))
		return (set_error(param), 1);
	param->everyone_ate = TRUE;
	if (pthread_mutex_unlock(&(param->mutex_everyone_ate)))
		return (set_error(param), 1);
	return (0);
}

t_bool	check_if_everyone_ate_enought(t_philo_param *param)
{
	int		i;
	t_bool	did_everyone_ate;

	i = 0;
	while (i < param->number_of_philosophers)
	{
		// if (pthread_mutex_lock(&(param->mutex_everyone_ate)))
		// 	return (set_error(param), FALSE);
		if (pthread_mutex_lock(&(param->philo_tab[i].mutex_ate_enought)))
			return (pthread_mutex_unlock(&(param->mutex_everyone_ate)),
				set_error(param), FALSE);
		did_everyone_ate = param->philo_tab[i].ate_enought;
		// if (pthread_mutex_unlock(&(param->mutex_everyone_ate))
		// 	||
		if (pthread_mutex_unlock(&(param->philo_tab[i].mutex_ate_enought)))
			return (set_error(param), FALSE);
		if (did_everyone_ate == FALSE)
			return (FALSE);
		i++;
	}
	set_everyone_ate(param);
	usleep (200);
	do_print(EVERYONE_ATE, &(param->philo_tab[0]));
	return (TRUE);
}

int	check_stop_conditions(t_philo_param *param)
{
	while (1)
	{
		if (found_error(param))
			return (1);
		if (check_if_someone_died(param))
			return (0);
		if (found_error(param))
			return (1);
		if (check_if_everyone_ate_enought(param))
			return (0);
		usleep(50);
	}
}
