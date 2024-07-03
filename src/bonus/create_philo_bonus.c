/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 10:48:45 by cdeville          #+#    #+#             */
/*   Updated: 2024/07/03 16:32:02 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers_bonus.h>

void	set_philo_param(t_philo_param *param)
{
	int	i;

	i = 1;
	if (param->number_of_philosophers >= 1)
	{
		(param->philo_tab[0]).philo_number = 1;
		(param->philo_tab[0]).last_eat = 0;
		(param->philo_tab[0]).param = param;
	}
	while (i < param->number_of_philosophers)
	{
		(param->philo_tab[i]).philo_number = i + 1;
		(param->philo_tab[i]).last_eat = 0;
		(param->philo_tab[i]).param = param;
		i++;
	}
}

void	destroy_philo_sem(t_philo_param *param)
{
	int	i;

	i = 0;
	while (i < param->number_of_philosophers)
	{
		if (param->philo_tab[i].sem_ate_enought == SEM_FAILED)
			return ;
		sem_close(param->philo_tab[i].sem_ate_enought);
		if (param->philo_tab[i].sem_last_eat == SEM_FAILED)
			return ;
		sem_close(param->philo_tab[i].sem_last_eat);
		i++;
	}
}

int	set_philo_sem(t_philo_param *param)
{
	int	i;

	i = 0;
	while (i < param->number_of_philosophers)
	{
		param->philo_tab[i].sem_ate_enought = sem_open(NULL, O_CREAT);
		param->philo_tab[i].sem_last_eat = sem_open(NULL, O_CREAT);
		if (param->philo_tab[i].sem_ate_enought == SEM_FAILED
			|| param->philo_tab[i].sem_last_eat == SEM_FAILED)
		{
			ft_putstr_fd("Error at mutex init\n", 2);
			return (destroy_philo_sem(param), 1);
		}
		if (sem_init(param->philo_tab[i].sem_ate_enought, 0, 1)
			|| sem_init(param->philo_tab[i].sem_last_eat, 0, 1))
		{
			ft_putstr_fd("Error at mutex init\n", 2);
			return (destroy_philo_sem(param), 1);
		}
		(param->philo_tab[i]).ate_enought = FALSE;
		i++;
	}
	return (0);
}

int	create_philo(t_philo_param *param)
{
	set_philo_param(param);
	return (set_philo_sem(param));
}
