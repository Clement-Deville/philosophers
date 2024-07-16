/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_monitoring_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 16:14:25 by cdeville          #+#    #+#             */
/*   Updated: 2024/07/16 18:25:31 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers_bonus.h>

int	join_monitoring(t_philo_param *param)
{
	sem_post(param->sem_is_dead);
	// UNLOCKING THE SEM_WAIT
	pthread_join(param->dead_monitor, NULL);
	pthread_join(param->eat_monitor, NULL);
}

void	*pthread_dead(void *argument)
{
	t_philo_param	*param;

	param = (t_philo_param *)argument;
	sem_wait(param->sem_is_dead);
	kill_all_childs(param);
	return (NULL);
}

void	*pthread_eat(void *argument)
{
	int				count;
	t_philo_param	*param;

	param = (t_philo_param *)argument;
	count = 0;
	while (count != param->number_of_philosophers)
	{
		sem_wait(param->sem_everyone_ate);
		count++;
	}
	sem_wait(param->sem_print);
	kill_all_childs(param);
	printf("Programm stopped cause everyone ate\n");
	sem_post(param->sem_print);
	return (NULL);
}

int	init_global_monitoring(t_philo_param *param)
{
	if (pthread_create(&(param->eat_monitor),
			NULL, pthread_eat, param)
		|| pthread_create(&(param->dead_monitor),
			NULL, pthread_dead, param))
		return (perror("pthread"), 1);
}
