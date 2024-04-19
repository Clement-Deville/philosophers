/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 12:09:20 by cdeville          #+#    #+#             */
/*   Updated: 2024/04/19 18:10:22 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

int	do_print(int message_id, t_philo *philo)
{
	pthread_mutex_lock(&(((t_philo_param *)(philo->param))->print));
	if (message_id == DEAD)
		printf("%ld %ld is dead\n", time_passed(((t_philo_param *)(philo->param))->clock), philo->philo_number);
	else if (message_id == FORK)
		printf("%ld %ld has taken a fork\n", time_passed(((t_philo_param *)(philo->param))->clock), philo->philo_number);
	else if (message_id == EAT)
		printf("%ld %ld is eating\n", time_passed(((t_philo_param *)(philo->param))->clock), philo->philo_number);
	else if (message_id == SLEEP)
		printf("%ld %ld is sleeping\n", time_passed(((t_philo_param *)(philo->param))->clock), philo->philo_number);
	else if (message_id == THINK)
		printf("%ld %ld is thinking\n", time_passed(((t_philo_param *)(philo->param))->clock), philo->philo_number);
	pthread_mutex_unlock(&(((t_philo_param *)(philo->param))->print));
	return (0);
}
