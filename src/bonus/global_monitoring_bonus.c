/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_monitoring_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 16:14:25 by cdeville          #+#    #+#             */
/*   Updated: 2024/07/11 16:36:36 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers_bonus.h>

void	*pthread_global(void *argument)
{

}

int	init_global_monitoring(t_philo_param *param)
{
	if (pthread_create(&(param->global_monitor),
			NULL, pthread_global, param))
		return (perror("pthread"), 1);
}
