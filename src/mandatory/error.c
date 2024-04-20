/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 16:17:14 by cdeville          #+#    #+#             */
/*   Updated: 2024/04/20 17:06:16 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

int	set_error(t_philo_param *param)
{
	if (pthread_mutex_lock(&(param->mutex_error)))
		return (1);
	param->error = TRUE;
	if (pthread_mutex_unlock(&(param->mutex_error)))
		return (1);
}
