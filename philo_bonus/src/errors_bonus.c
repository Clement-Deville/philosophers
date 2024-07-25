/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 17:20:31 by cdeville          #+#    #+#             */
/*   Updated: 2024/07/19 10:50:26 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers_bonus.h>

void	set_error(t_philo_param *param)
{
	sem_post((param->sem_error));
	usleep(5000 + (30 * param->number_of_philosophers));
	return ;
}
