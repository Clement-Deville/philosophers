/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:41:40 by cdeville          #+#    #+#             */
/*   Updated: 2024/04/17 18:03:34 by cdeville         ###   ########.fr       */
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
// 	printf("%ld %ld has fork %ld and %ld\n", *(p->philo_id) + 1, r_fork, l_fork);
// 	return (NULL);
// }

long	time_passed(struct timeval start)
{
	struct timeval	end;
	long			microseconds;

	gettimeofday(&end, NULL);
	microseconds = (end.tv_sec - start.tv_sec) * 1000000
		+ (end.tv_usec - start.tv_usec);
	return (microseconds);
}

void	*pthread_fct(void *argument)
{
	t_philo			*philo;
	int				count;
	struct timeval	start;
	long			timer;

	count = 0;
	philo = (t_philo *)argument;
	// printf("Number: %ld\n", timer, philo->philo_number);
	gettimeofday(&start, NULL);
	while (count < 5)
	{
		if (philo->philo_number % 2 == 0)
		{
			pthread_mutex_lock(&(philo->l_fork));
			timer = time_passed(start);
			if (timer >= ((t_philo_param *)(philo->param))->time_to_die)
				return (pthread_mutex_unlock(&(philo->l_fork)),
					printf("%ld %ld is dead\n", timer, philo->philo_number), NULL);
			printf("%ld %ld has taken a fork\n", timer, philo->philo_number);
			pthread_mutex_lock(&(philo->r_fork));
			if (timer >= ((t_philo_param *)(philo->param))->time_to_die)
				return (pthread_mutex_unlock(&(philo->r_fork)),
					pthread_mutex_unlock(&(philo->l_fork)),
					printf("%ld %ld is dead\n", timer, philo->philo_number), NULL);
			printf("%ld %ld has taken a fork\n", timer, philo->philo_number);
		}
		else
		{
			pthread_mutex_lock(&(philo->r_fork));
			if (timer >= ((t_philo_param *)(philo->param))->time_to_die)
				return (pthread_mutex_unlock(&(philo->l_fork)),
					printf("%ld %ld is dead\n", timer, philo->philo_number), NULL);
			printf("%ld %ld has taken a fork\n", timer, philo->philo_number);
			pthread_mutex_lock(&(philo->l_fork));
			if (timer >= ((t_philo_param *)(philo->param))->time_to_die)
				return (pthread_mutex_unlock(&(philo->l_fork)),
					pthread_mutex_unlock(&(philo->r_fork)),
					printf("%ld %ld is dead\n", timer, philo->philo_number), NULL);
			printf("%ld %ld has taken a fork\n", timer, philo->philo_number);
		}
		printf("%ld %ld is eating\n", timer, philo->philo_number);
		pthread_mutex_unlock(&(philo->l_fork));
		pthread_mutex_unlock(&(philo->r_fork));
		usleep(((t_philo_param *)(philo->param))->time_to_eat * 1000);
		gettimeofday(&start, NULL);
		if (timer >= ((t_philo_param *)(philo->param))->time_to_die)
			return (printf("%ld %ld is dead\n", timer, philo->philo_number), NULL);
		printf("%ld %ld is sleeping\n", timer, philo->philo_number);
		usleep(((t_philo_param *)(philo->param))->time_to_sleep * 1000);
		if (timer >= ((t_philo_param *)(philo->param))->time_to_die)
			return (printf("%ld %ld is dead\n", timer, philo->philo_number), NULL);
		printf("%ld %ld is thinking\n", timer, philo->philo_number);
		count++;
	}
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
// 		printf("%ld %ld has eaten\n", p->number + 1);
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
