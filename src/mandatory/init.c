/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:43:18 by cdeville          #+#    #+#             */
/*   Updated: 2024/04/19 10:11:09 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

int	create_philo(t_philo_param *param)
{
	int	i;

	i = 1;
	if (param->number_of_philosophers >= 1)
	{
		(param->philo_tab[0]).philo_number = 1;
		(param->philo_tab[0]).l_fork = param->forks[0];
		(param->philo_tab[0]).r_fork
			= param->forks[param->number_of_philosophers - 1];
		(param->philo_tab[0]).param = param;
	}
	while (i < param->number_of_philosophers)
	{
		(param->philo_tab[i]).philo_number = i + 1;
		(param->philo_tab[i]).l_fork = param->forks[i];
		(param->philo_tab[i]).r_fork = param->forks[i - 1];
		(param->philo_tab[i]).param = param;
		i++;
	}
	return (0);
}

t_bool	is_valid_parameters(int argc, char *argv[])
{
	if (argc < 1)
		return (FALSE);
	(void)argv;
	return (TRUE);
}

int	init_mutex(t_philo_param *param)
{
	int	i;

	i = 0;
	while (i < param->number_of_philosophers)
	{
		if (pthread_mutex_init(&(param->forks[i]), NULL))
		{
			ft_putstr_fd("Error at mutex init\n", 2);
			return (-1);
		}
		i++;
	}
	if (pthread_mutex_init(&(param->mutex_is_dead), NULL))
	{
		ft_putstr_fd("Error at mutex init\n", 2);
		return (-1);
	}
	return (0);
}

int	init(t_philo_param *param, int argc, char *argv[])
{

	if (argc < 5 || argc > 6)
		return (ft_putstr_fd("Wrong number of arguments\n", 2), 1);
	if (is_valid_parameters(argc, argv) == FALSE)
		return (1);
	param->number_of_philosophers = ft_atoi(argv[1]);
	param->time_to_die = ft_atoi(argv[2]);
	param->time_to_eat = ft_atoi(argv[3]);
	param->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		param->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	else
		param->number_of_times_each_philosopher_must_eat = -1;
	param->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* (param->number_of_philosophers));
	if (param->forks == NULL)
		return (ft_putstr_fd("Erreur de malloc\n", 2), 1);
	param->threads = (pthread_t *)malloc(sizeof(pthread_t)
			* (param->number_of_philosophers));
	if (param->threads == NULL || init_mutex(param) == -1)
		return (free(param->forks), ft_putstr_fd("Erreur de malloc\n", 2), 1);
	param->philo_tab = (t_philo *)malloc(sizeof(t_philo)
			* (param->number_of_philosophers));
	if (param->philo_tab == NULL)
		return (free(param->threads),
			free(param->forks), ft_putstr_fd("Erreur de malloc\n", 2), 1);
	param->is_dead = FALSE;
	gettimeofday(&(param->clock), NULL);
	create_philo(param);
	int	i;

	i = 0;
	while(i < param->number_of_philosophers)
	{
		printf("Philo %d: \nL: %p\nR: %p\n", i + 1, &(param->philo_tab[i].l_fork), &(param->philo_tab[i].l_fork));
		// printf("Fork %d: %p\n", i + 1, &(param->forks[i]));
		i++;
	}
	return (0);
}
