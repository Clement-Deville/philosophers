/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_monitoring_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 16:14:25 by cdeville          #+#    #+#             */
/*   Updated: 2024/07/24 15:19:31 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers_bonus.h>

int	join_monitoring(t_philo_param *param)
{
	sem_post(param->sem_is_dead);
	sem_wait(&(param->sem_stop));
	param->stop = TRUE;
	sem_post(&(param->sem_stop));
	sem_post(param->sem_everyone_ate);
	sem_post((param->sem_error));
	pthread_join(param->dead_monitor, NULL);
	pthread_join(param->eat_monitor, NULL);
	pthread_join(param->error_monitor, NULL);
	return (0);
}

int	term_childs(t_philo_param *param)
{
	int	i;

	i = 0;
	while (i < 2 * param->number_of_philosophers)
	{
		sem_post(param->sem_global_terminate);
		i++;
	}
	return (0);
}

void	join_valids(t_philo_param *param, int i)
{
	sem_post(param->sem_is_dead);
	sem_wait(&(param->sem_stop));
	param->stop = TRUE;
	sem_post(&(param->sem_stop));
	sem_post(param->sem_everyone_ate);
	sem_post((param->sem_error));
	pthread_join(param->dead_monitor, NULL);
	if (i == 2)
		pthread_join(param->eat_monitor, NULL);
	if (i == 3)
		pthread_join(param->error_monitor, NULL);
}

int	init_global_monitoring(t_philo_param *param)
{
	if (pthread_create(&(param->eat_monitor),
			NULL, pthread_eat, param))
		return (perror("pthread"), join_valids(param, 1), 1);
	if (pthread_create(&(param->dead_monitor),
			NULL, pthread_dead, param))
		return (perror("pthread"), join_valids(param, 2), 1);
	if (pthread_create(&(param->error_monitor),
			NULL, pthread_error, param))
		return (perror("pthread"), join_valids(param, 3), 1);
	return (0);
}
