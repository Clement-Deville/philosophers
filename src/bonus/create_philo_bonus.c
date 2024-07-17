/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_philo_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 10:48:45 by cdeville          #+#    #+#             */
/*   Updated: 2024/07/17 14:29:30 by cdeville         ###   ########.fr       */
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
		printf("param adress is %p in set\n", param);
	}
	while (i < param->number_of_philosophers)
	{
		(param->philo_tab[i]).philo_number = i + 1;
		(param->philo_tab[i]).last_eat = 0;
		(param->philo_tab[i]).param = param;
		printf("param adress is %p in set\n", param);
		i++;
	}
}

void	destroy_philo_sem(t_philo_param *param)
{
	int	i;

	i = 0;
	while (i < param->number_of_philosophers)
	{
		sem_destroy(&(param->philo_tab[i].sem_ate_enought));
		sem_destroy(&(param->philo_tab[i].sem_last_eat));
		i++;
	}
}

int	set_philo_sem(t_philo_param *param)
{
	int	i;

	i = 0;
	while (i < param->number_of_philosophers)
	{
		if (sem_init(&(param->philo_tab[i].sem_ate_enought), 1, 1))
		{
			ft_putstr_fd("Error at mutex init\n", 2);
			i--;
			while (i)
			{
				sem_destroy(&(param->philo_tab[i].sem_ate_enought));
				sem_destroy(&(param->philo_tab[i].sem_last_eat));
				i--;
			}
			return (1);
		}
		if (sem_init(&(param->philo_tab[i].sem_last_eat), 1, 1))
		{
			ft_putstr_fd("Error at mutex init\n", 2);
			sem_destroy(&(param->philo_tab[i].sem_ate_enought));
			i--;
			while (i)
			{
				sem_destroy(&(param->philo_tab[i].sem_ate_enought));
				sem_destroy(&(param->philo_tab[i].sem_last_eat));
				i--;
			}
		}
		(param->philo_tab[i]).ate_enought = FALSE;
		i++;
	}
	return (0);
}

int	create_philo(t_philo_param *param)
{
	set_philo_param(param);
	// int	i;
	// i = 0;
	// while (i < param->number_of_philosophers)
	// {
	// 	printf("Philo number %ld, Philo param %p\n", param->philo_tab[i].philo_number, (param->philo_tab[i]).param);
	// 	// a retirer
	// 	i++;
	// }
	return (set_philo_sem(param));
}
