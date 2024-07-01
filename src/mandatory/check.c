/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 16:38:49 by cdeville          #+#    #+#             */
/*   Updated: 2024/07/01 15:46:08 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

t_bool	someone_is_dead(t_philo_param *param)
{
	t_bool	status;

	if (pthread_mutex_lock(&(param->mutex_is_dead)))
		return (set_error(param), FALSE);
	status = param->is_dead;
	if (pthread_mutex_unlock(&(param->mutex_is_dead)))
		return (set_error(param), FALSE);
	return (status);
}

t_bool	everyone_ate(t_philo *philo)
{
	int	status;

	if (pthread_mutex_lock(&(philo->param->mutex_everyone_ate)))
		return (set_error(philo->param), FALSE);
	status = philo->param->everyone_ate;
	if (pthread_mutex_unlock(&(philo->param->mutex_everyone_ate)))
		return (set_error(philo->param), FALSE);
	return (status);
}

t_bool	do_continue(t_philo *philo)
{
	if (found_error(philo->param) || someone_is_dead(philo->param) == TRUE
		|| everyone_ate(philo) == TRUE)
		return (FALSE);
	else
		return (TRUE);
}
