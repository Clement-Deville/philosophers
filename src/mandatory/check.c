/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 16:38:49 by cdeville          #+#    #+#             */
/*   Updated: 2024/04/19 18:04:22 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

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
		usleep(100);
	}
	return (0);
}
