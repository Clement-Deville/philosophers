/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:41:40 by cdeville          #+#    #+#             */
/*   Updated: 2024/04/19 18:10:49 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

long	time_passed(struct timeval start)
{
	struct timeval	end;
	long			miliseconds;
	long			micro;

	gettimeofday(&end, NULL);
	miliseconds = (end.tv_sec - start.tv_sec) * 1000;
	micro = end.tv_usec - start.tv_usec;
	if (micro)
		miliseconds += micro / 1000;
	return (miliseconds);
}

t_bool	is_dead(t_philo *philo)
{
	t_bool	status;

	status = FALSE;
	pthread_mutex_lock(&(((t_philo_param *)(philo->param))->mutex_is_dead));
	if (((t_philo_param *)(philo->param))->is_dead == TRUE)
		status = TRUE;
	// usleep(10);
	pthread_mutex_unlock(&(((t_philo_param *)(philo->param))->mutex_is_dead));
	return (status);
}

int	do_die(t_philo *philo)
{
	pthread_mutex_lock(&(((t_philo_param *)(philo->param))->mutex_is_dead));
	if (((t_philo_param *)(philo->param))->is_dead == TRUE)
	{
		pthread_mutex_unlock(&(((t_philo_param *)(philo->param))->mutex_is_dead));
		return (0);
	}
	((t_philo_param *)(philo->param))->is_dead = TRUE;
	usleep(50);
	do_print(DEAD, philo);
	pthread_mutex_unlock(&(((t_philo_param *)(philo->param))->mutex_is_dead));
	return (0);
}

int	take_left(t_philo *philo)
{
	if (pthread_mutex_lock(philo->l_fork))
		return (ft_putstr_fd("Mutex lock error\n", 2), 1);
	if (is_dead(philo) == FALSE)
		do_print(FORK, philo);
	return (0);
}

int	take_right(t_philo *philo)
{
	if (pthread_mutex_lock(philo->r_fork))
		return (ft_putstr_fd("Mutex lock error\n", 2), 1);
	if (is_dead(philo) == FALSE)
		do_print(FORK, philo);
	return (0);
}

int	do_eat(t_philo *philo)
{
	if (is_dead(philo) == FALSE)
	{
		do_print(EAT, philo);
		usleep(((t_philo_param *)(philo->param))->time_to_eat * 1000);
	}
	if (pthread_mutex_unlock(philo->l_fork))
		return (ft_putstr_fd("Mutex unlock error\n", 2), 1);
	if (pthread_mutex_unlock(philo->r_fork))
		return (ft_putstr_fd("Mutex unlock error\n", 2), 1);
	return (0);
}

int	do_sleep(t_philo *philo)
{
	if (is_dead(philo) == FALSE)
	{
		do_print(SLEEP, philo);
		usleep(((t_philo_param *)(philo->param))->time_to_sleep * 1000);
	}
	return (0);
}

int	do_think(t_philo *philo)
{
	if (is_dead(philo) == FALSE)
		do_print(THINK, philo);
	return (0);
}

void	*pthread_fct(void *argument)
{
	t_philo			*philo;
	int				count;

	count = 0;
	philo = (t_philo *)argument;
	while (is_dead(philo) == FALSE)
	{
		if (philo->philo_number % 2 == 0)
		{
			take_left(philo);
			take_right(philo);
		}
		else
		{
			take_right(philo);
			take_left(philo);
		}
		philo->last_eat = time_passed(((t_philo_param *)(philo->param))->clock);
		do_eat(philo);
		philo->last_eat = time_passed(((t_philo_param *)(philo->param))->clock);
		do_sleep(philo);
		do_think(philo);
		count++;
	}
	if (count == 5)
		printf("Every one ate the maximum");
	return (NULL);
}

// void	*pthread_fct(void *argument)
// {
// 	t_philo			*philo;
// 	int				count;
// 	struct timeval	start;
// 	long			timer;
// 	struct timeval	time;

// 	count = 0;
// 	philo = (t_philo *)argument;
// 	// printf("Number: %ld\n", time.tv_usec, philo->philo_number);
// 	gettimeofday(&start, NULL);
// 	while (count < 5)
// 	{
// 		if (philo->philo_number % 2 == 0)
// 		{
// 			pthread_mutex_lock(&(philo->l_fork));
// 			timer = time_passed(start);
// 			gettimeofday(&time, NULL);
// 			if (timer >= ((t_philo_param *)(philo->param))->time_to_die)
// 				return (pthread_mutex_unlock(&(philo->l_fork)),
// 					printf("%ld %ld is dead\n", time.tv_usec, philo->philo_number), NULL);
// 			printf("%ld %ld has taken a fork\n", time.tv_usec, philo->philo_number);
// 			pthread_mutex_lock(&(philo->r_fork));
// 			timer = time_passed(start);
// 			gettimeofday(&time, NULL);
// 			if (timer >= ((t_philo_param *)(philo->param))->time_to_die)
// 				return (pthread_mutex_unlock(&(philo->r_fork)),
// 					pthread_mutex_unlock(&(philo->l_fork)),
// 					printf("%ld %ld is dead\n", time.tv_usec, philo->philo_number), NULL);
// 			printf("%ld %ld has taken a fork\n", time.tv_usec, philo->philo_number);
// 		}
// 		else
// 		{
// 			pthread_mutex_lock(&(philo->r_fork));
// 			timer = time_passed(start);
// 			gettimeofday(&time, NULL);
// 			if (timer >= ((t_philo_param *)(philo->param))->time_to_die)
// 				return (pthread_mutex_unlock(&(philo->l_fork)),
// 					printf("%ld %ld is dead\n", time.tv_usec, philo->philo_number), NULL);
// 			printf("%ld %ld has taken a fork\n", time.tv_usec, philo->philo_number);
// 			pthread_mutex_lock(&(philo->l_fork));
// 			timer = time_passed(start);
// 			gettimeofday(&time, NULL);
// 			if (timer >= ((t_philo_param *)(philo->param))->time_to_die)
// 				return (pthread_mutex_unlock(&(philo->l_fork)),
// 					pthread_mutex_unlock(&(philo->r_fork)),
// 					printf("%ld %ld is dead\n", time.tv_usec, philo->philo_number), NULL);
// 			printf("%ld %ld has taken a fork\n", time.tv_usec, philo->philo_number);
// 		}
// 		printf("%ld %ld is eating\n", time.tv_usec, philo->philo_number);
// 		pthread_mutex_unlock(&(philo->l_fork));
// 		pthread_mutex_unlock(&(philo->r_fork));
// 		usleep(((t_philo_param *)(philo->param))->time_to_eat * 1000);
// 		gettimeofday(&start, NULL);
// 		timer = time_passed(start);
// 		gettimeofday(&time, NULL);
// 		if (timer >= ((t_philo_param *)(philo->param))->time_to_die)
// 			return (printf("%ld %ld is dead\n", time.tv_usec, philo->philo_number), NULL);
// 		printf("%ld %ld is sleeping\n", time.tv_usec, philo->philo_number);
// 		usleep(((t_philo_param *)(philo->param))->time_to_sleep * 1000);
// 		timer = time_passed(start);
// 		gettimeofday(&time, NULL);
// 		if (timer >= ((t_philo_param *)(philo->param))->time_to_die)
// 			return (printf("%ld %ld is dead\n", time.tv_usec, philo->philo_number), NULL);
// 		printf("%ld %ld is thinking\n", time.tv_usec, philo->philo_number);
// 		count++;
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
