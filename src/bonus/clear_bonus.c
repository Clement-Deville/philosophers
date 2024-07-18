/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 10:51:23 by cdeville          #+#    #+#             */
/*   Updated: 2024/07/18 17:43:28 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers_bonus.h>

void	destroy_philo_sem(t_philo_param *param)
{
	int	i;

	i = 0;
	while (i < param->number_of_philosophers)
	{
		sem_destroy(&(param->philo_tab[i].sem_ate_enought));
		sem_destroy(&(param->philo_tab[i].sem_last_eat));
		sem_destroy(&(param->philo_tab[i].sem_terminate));
		i++;
	}
}

int	clean_exit(t_philo_param *param)
{
	destroy_philo_sem(param);
	close_sem(param);
	unlink_sem();
	free(param->pid_tab);
	free(param->philo_tab);
	return (0);
}

int	clean_exit_child(t_philo_param *param)
{
	close_sem(param);
	free(param->pid_tab);
	free(param->philo_tab);
	return (0);
}
