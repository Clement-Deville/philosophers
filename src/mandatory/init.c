/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:43:18 by cdeville          #+#    #+#             */
/*   Updated: 2024/07/02 17:27:58 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

void	set_philo_param(t_philo_param *param)
{
	int	i;

	i = 1;
	if (param->number_of_philosophers >= 1)
	{
		(param->philo_tab[0]).philo_number = 1;
		(param->philo_tab[0]).l_fork = &(param->forks[0]);
		(param->philo_tab[0]).r_fork
			= &(param->forks[param->number_of_philosophers - 1]);
		(param->philo_tab[0]).last_eat = 0;
		(param->philo_tab[0]).param = param;
	}
	while (i < param->number_of_philosophers)
	{
		(param->philo_tab[i]).philo_number = i + 1;
		(param->philo_tab[i]).l_fork = &(param->forks[i]);
		(param->philo_tab[i]).r_fork = &(param->forks[i - 1]);
		(param->philo_tab[i]).last_eat = 0;
		(param->philo_tab[i]).param = param;
		i++;
	}
}

int	set_philo_mutex(t_philo_param *param)
{
	int	i;

	i = 0;
	while (i < param->number_of_philosophers)
	{
		if (pthread_mutex_init(&((param->philo_tab[i]).mutex_ate_enought), NULL)
			|| pthread_mutex_init(&((param->philo_tab[i])
					.mutex_last_eat), NULL))
		{
			ft_putstr_fd("Error at mutex init\n", 2);
			while (i >= 0)
			{
				pthread_mutex_destroy(&((param->philo_tab[i])
						.mutex_ate_enought));
				pthread_mutex_destroy(&((param->philo_tab[i]).mutex_last_eat));
				i--;
			}
			return (1);
		}
		(param->philo_tab[i]).ate_enought = FALSE;
		i++;
	}
	return (0);
}

int	create_philo(t_philo_param *param)
{
	set_philo_param(param);
	return (set_philo_mutex(param));
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
			return (1);
		}
		i++;
	}
	if (pthread_mutex_init(&(param->mutex_is_dead), NULL)
		|| pthread_mutex_init(&(param->print), NULL)
		|| pthread_mutex_init(&(param->mutex_everyone_ate), NULL)
		|| pthread_mutex_init(&(param->mutex_error), NULL))
	{
		ft_putstr_fd("Error at mutex init\n", 2);
		return (1);
	}
	return (0);
}

int	allocate(t_philo_param *param)
{
	param->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* (param->number_of_philosophers));
	if (param->forks == NULL)
		return (ft_putstr_fd("Erreur de malloc\n", 2), 1);
	param->threads = (pthread_t *)malloc(sizeof(pthread_t)
			* (param->number_of_philosophers));
	if (param->threads == NULL || init_mutex(param) == 1)
		return (free(param->forks), ft_putstr_fd("Erreur de malloc\n", 2), 1);
	param->philo_tab = (t_philo *)malloc(sizeof(t_philo)
			* (param->number_of_philosophers));
	if (param->philo_tab == NULL)
		return (free(param->threads),
			free(param->forks), ft_putstr_fd("Erreur de malloc\n", 2), 1);
	return (0);
}

int	get_parameters(t_philo_param *param, int argc, char *argv[])
{
	if (argc < 5 || argc > 6)
		return (ft_putstr_fd("Wrong number of arguments\n", 2), 1);
	if (is_valid_parameters(argc, argv) == FALSE)
		return (1);
	param->number_of_philosophers = ft_atoi(argv[1]);
	if (param->number_of_philosophers < 1)
		return (ft_putstr_fd("Error: Need a least one philo to run\n", 2), 1);
	param->time_to_die = ft_atoi(argv[2]);
	param->time_to_eat = ft_atoi(argv[3]);
	param->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		param->max_eat = ft_atoi(argv[5]);
	else
		param->max_eat = -1;
	if (param->max_eat == 0)
		return (ft_putstr_fd("Error: Need a least one meal to run\n", 2), 1);
	return (0);
}

int	destroy_mutex_init_error(t_philo_param *param)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (i < param->number_of_philosophers)
	{
		ret = (ret || pthread_mutex_destroy(&(param->forks[i])));
		i++;
	}
	ret = (pthread_mutex_destroy(&(param->mutex_is_dead)) || ret);
	ret = (pthread_mutex_destroy(&(param->print)) || ret);
	ret = (pthread_mutex_destroy(&(param->mutex_everyone_ate)) || ret);
	ret = (pthread_mutex_destroy(&(param->mutex_error)) || ret);
	if (ret)
	{
		ft_putstr_fd("Error at mutex destory\n", 2);
		return (1);
	}
	return (0);
}

void	clean_init_error(t_philo_param *param)
{
	destroy_mutex_init_error(param);
	free(param->philo_tab);
	free(param->forks);
	free(param->threads);
}

int	init(t_philo_param *param, int argc, char *argv[])
{
	if (get_parameters(param, argc, argv))
		return (1);
	if (allocate(param))
		return (1);
	param->is_dead = FALSE;
	gettimeofday(&(param->clock), NULL);
	if (create_philo(param))
		return (clean_init_error(param), 1);
	param->error = FALSE;
	param->everyone_ate = FALSE;
	return (0);
}
