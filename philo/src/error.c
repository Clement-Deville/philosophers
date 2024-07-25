/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 16:17:14 by cdeville          #+#    #+#             */
/*   Updated: 2024/06/28 13:55:47 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

void	set_error(t_philo_param *param)
{
	if (pthread_mutex_lock(&(param->mutex_error)))
	{
		usleep(500);
		do_print(CRITIC_ERROR, &(param->philo_tab[0]));
		return ;
	}
	param->error = TRUE;
	if (pthread_mutex_unlock(&(param->mutex_error)))
	{
		usleep(500);
		do_print(CRITIC_ERROR, &(param->philo_tab[0]));
		return ;
	}
	usleep(500);
	do_print(CRITIC_ERROR, &(param->philo_tab[0]));
}

t_bool	found_error(t_philo_param *param)
{
	int	error;

	if (pthread_mutex_lock(&(param->mutex_error)))
		return (set_error(param), (TRUE));
	error = param->error;
	if (pthread_mutex_unlock(&(param->mutex_error)))
		return (set_error(param), TRUE);
	return (error);
}
