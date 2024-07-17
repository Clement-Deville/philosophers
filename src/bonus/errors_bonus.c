/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 17:20:31 by cdeville          #+#    #+#             */
/*   Updated: 2024/07/17 11:23:17 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers_bonus.h>

// void	set_error(t_philo_param *param)
// {
// 	if (sem_wait(&(param->sem_error)))
// 	{
// 		usleep(500);
// 		do_print(CRITIC_ERROR, &(param->philo_tab[0]));
// 		return ;
// 	}
// 	param->error = TRUE;
// 	if (sem_post(&(param->sem_error)))
// 	{
// 		usleep(500);
// 		do_print(CRITIC_ERROR, &(param->philo_tab[0]));
// 		return ;
// 	}
// 	usleep(500);
// 	do_print(CRITIC_ERROR, &(param->philo_tab[0]));
// }

// t_bool	found_error(t_philo_param *param)
// {
// 	int	error;

// 	if (sem_wait(&(param->mutex_error)))
// 		return (set_error(param), (TRUE));
// 	error = param->error;
// 	if (sem_post(&(param->mutex_error)))
// 		return (set_error(param), TRUE);
// 	return (error);
// }

void	set_error(t_philo_param *param)
{
	(void)param;
	return ;
}
