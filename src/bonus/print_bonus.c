/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 15:43:01 by cdeville          #+#    #+#             */
/*   Updated: 2024/07/23 15:35:25 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers_bonus.h>

void	print_msg(int message_id, t_philo *philo)
{
	if (!do_continue(philo))
		return ;
	if (message_id == DEAD)
	{
		printf("%ld %ld died\n",
			time_passed(philo->param->clock), philo->philo_number);
		usleep(5000 + (100 * philo->param->number_of_philosophers));
	}
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
}

void	do_print(int message_id, t_philo *philo)
{
	sem_wait(philo->param->sem_print);
	print_msg(message_id, philo);
	sem_post(philo->param->sem_print);
}
