/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:43:01 by cdeville          #+#    #+#             */
/*   Updated: 2024/07/17 18:03:02 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers_bonus.h>

int	do_print(int message_id, t_philo *philo)
{
	// if (philo->param->sem_print == NULL)
	// 	printf("In do_print: philo->param->sem_print is null\n");
	// if (philo->param == NULL)
	// 	printf("In do_print: philo->param is null\n");
	// a retirer
	if (sem_wait(philo->param->sem_print))
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
	if (sem_post(philo->param->sem_print))
		return (set_error(philo->param), 1);
	return (0);
}
