/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_monitoring_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 16:14:25 by cdeville          #+#    #+#             */
/*   Updated: 2024/07/18 17:59:01 by cdeville         ###   ########.fr       */
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

void	*pthread_dead(void *argument)
{
	t_philo_param	*param;

	param = (t_philo_param *)argument;
	sem_wait(param->sem_is_dead);
	term_childs(param);
	return (NULL);
}

void	*pthread_error(void *argument)
{
	t_philo_param	*param;

	param = (t_philo_param *)argument;
	sem_wait((param->sem_error));
	term_childs(param);
	return (NULL);
	// je dois faire exit  mon program avec la bonne valeur
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
		sem_wait(&(param->sem_stop));
		if (param->stop)
			return (sem_post(&(param->sem_stop)), NULL);
		sem_post(&(param->sem_stop));
	}
	term_childs(param);
	sem_wait(param->sem_print);
	usleep(100);
	printf("Programm stopped cause everyone ate\n");
	sem_post(param->sem_print);
	return (NULL);
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
