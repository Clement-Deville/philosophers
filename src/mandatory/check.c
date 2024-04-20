/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 16:38:49 by cdeville          #+#    #+#             */
/*   Updated: 2024/04/20 17:47:46 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

t_bool	is_someone_is_dead(t_philo_param *param)
{
	t_bool	status;

	if (pthread_mutex_lock(&(param->mutex_is_dead)))
		return (set_error(param), FALSE);
	status = param->is_dead;
	if (pthread_mutex_unlock(&(param->mutex_is_dead)))
		return (set_error(param), FALSE);
	return (status);
}

int	check_if_someone_died(t_philo_param *param)
{
	int		i;
	t_bool	alive;
	long	timer;

	alive = TRUE;
	while (alive)
	{
		i = 0;
		while (i < param->number_of_philosophers)
		{
			timer = time_passed(param->clock) - param->philo_tab[i].last_eat;
			if (timer >= param->time_to_die)
			{
				do_die(&(param->philo_tab[i]));
				return (0);
			}
			i++;
		}
		usleep(50);
	}
	return (0);
}

int	check_if_everyone_ate_enought(t_philo_param *param)
{

}

t_bool	check_stop_conditions(t_philo_param *param)
{
	if (found_error(param))
		return (TRUE);
	if (check_if_someone_died(param))
		return (TRUE);
	if (check_if_everyone_ate_enought(param))
		return (TRUE);
	return (FALSE);
}

t_bool	everyone_ate(t_philo *philo)
{
	int	status;

	if (pthread_mutex_lock(&(philo->param->mutex_everyone_ate)))
		return (set_error(philo->param), FALSE);
	status = philo->param->everyone_ate;
	if (pthread_mutex_unlock(&(philo->param->mutex_everyone_ate)))
		return (set_error(philo->param), FALSE);
	if (status == TRUE)
		if (do_print(EVERYONE_ATE, philo))
			return (set_error(philo->param), FALSE);
	return (status);
}

t_bool	found_error(t_philo_param *param)
{
	int	error;

	if (pthread_mutex_lock(&(param->mutex_error)))
		return (TRUE);
	error = param->error;
	if (pthread_mutex_unlock(&(param->mutex_error)))
		return (TRUE);
	return (error);
}

t_bool	do_continue(t_philo *philo)
{
	if (is_someone_is_dead(philo) == TRUE || everyone_ate(philo) == TRUE
		|| found_error(philo))
		return (FALSE);
	else
		return (TRUE);
}
