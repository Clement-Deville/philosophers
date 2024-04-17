/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:41:40 by cdeville          #+#    #+#             */
/*   Updated: 2024/04/17 14:43:48 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

// void	*pthread_fct(void *argument)
// {
// 	t_philo_param	*p;
// 	long			r_fork;
// 	long			l_fork;

// 	p = (t_philo_param *)argument;
// 	if (*(p->philo_id) == 0)
// 	{
// 		r_fork = p->number_of_philosophers + 1;
// 		l_fork = *(p->philo_id) + 1;
// 	}
// 	else
// 	{
// 		r_fork = *(p->philo_id);
// 		l_fork = *(p->philo_id) + 1;
// 	}
// 	printf("Philo %ld has fork %ld and %ld\n", *(p->philo_id) + 1, r_fork, l_fork);
// 	return (NULL);
// }

void	*pthread_fct(void *argument)
{
	t_philo	*philo;

	philo = (t_philo *)argument;
	printf("Number: %ld\n", philo->philo_number);
	return (NULL);
}

// void	*pthread_fct(void *argument)
// {
// 	t_philo	*p;
// 	int		i;

// 	p = (t_philo *)argument;
// 	i = 0;
// 	while (i < 10)
// 	{
// 		if (p->number % 2 == 0)
// 		{
// 			pthread_mutex_lock(&(p->l_fork));
// 			pthread_mutex_lock(&(p->r_fork));
// 		}
// 		else
// 		{
// 			pthread_mutex_lock(&(p->r_fork));
// 			pthread_mutex_lock(&(p->l_fork));
// 		}
// 		pthread_mutex_unlock(&(p->l_fork));
// 		pthread_mutex_unlock(&(p->r_fork));
// 		printf("Philo %ld has eaten\n", p->number + 1);
// 		sleep(2);
// 		i++;
// 	}
// 	return (NULL);
// }

int	join_all(t_philo_param param)
{
	int	i;
	int	status;
	int	return_status;

	i = 0;
	status = 0;
	return_status = 0;
	while (i < param.number_of_philosophers)
	{
		status = pthread_join(param.threads[i], NULL);
		if (status)
		{
			ft_putstr_fd("Error when joining\n", 2);
			return_status = status;
		}
		i++;
	}
	return (return_status);
}
