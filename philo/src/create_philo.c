/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 10:48:45 by cdeville          #+#    #+#             */
/*   Updated: 2024/07/03 10:49:08 by cdeville         ###   ########.fr       */
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
