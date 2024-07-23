/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthreads_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 10:51:05 by cdeville          #+#    #+#             */
/*   Updated: 2024/07/23 14:57:15 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers_bonus.h>

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

void	*pthread_actions(void *argument)
{
	int		count;
	t_philo	*philo;

	philo = (t_philo *)argument;
	count = 0;
	while (do_continue(philo) == TRUE)
	{
		take_forks(philo);
		do_eat(philo);
		do_sleep(philo);
		do_think(philo);
		count++;
		if (count == philo->param->max_eat)
			set_one_ate_enought(philo);
	}
	return (NULL);
}

void	*pthread_actions_for_one(void *argument)
{
	int		count;
	t_philo	*philo;

	philo = (t_philo *)argument;
	count = 0;
	do_print(FORK, philo);
	while (do_continue(philo) == TRUE)
	{
		usleep(500);
	}
	return (NULL);
}

void	*pthread_term(void *argument)
{
	t_philo	*philo;

	philo = (t_philo *)argument;
	sem_wait(philo->param->sem_global_terminate);
	sem_wait(&(philo->sem_terminate));
	philo->terminate = TRUE;
	sem_post(&(philo->sem_terminate));
	return (NULL);
}
