/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 12:09:20 by cdeville          #+#    #+#             */
/*   Updated: 2024/04/22 18:44:09 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

int	do_print(int message_id, t_philo *philo)
{
	if (pthread_mutex_lock(&(philo->param->print)))
		return (set_error(philo->param), 1);
	if (message_id == DEAD)
		printf("%ld %ld is dead\n",
			time_passed(philo->param->clock), philo->philo_number);
	else if (message_id == FORK)
		printf("%ld %ld has taken a fork\n",
			time_passed(philo->param->clock), philo->philo_number);
	else if (message_id == EAT)
		printf("%ld %ld is eating\n",
			time_passed(philo->param->clock), philo->philo_number);
	else if (message_id == SLEEP)
		printf("%ld %ld is sleeping\n",
			time_passed(philo->param->clock), philo->philo_number);
	else if (message_id == THINK)
		printf("%ld %ld is thinking\n",
			time_passed(philo->param->clock), philo->philo_number);
	else if (message_id == EVERYONE_ATE)
		printf("Programm stopped cause everyone ate\n");
	else if (message_id == CRITIC_ERROR)
		ft_putstr_fd("\n\nCRITICAL ERROR OCCURED!\n\n", 2);
	if (pthread_mutex_unlock(&(philo->param->print)))
		return (set_error(philo->param), 1);
	return (0);
}
