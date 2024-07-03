/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 10:51:23 by cdeville          #+#    #+#             */
/*   Updated: 2024/07/03 10:52:26 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

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
		ft_putstr_fd("Error at mutex destory\n", 2);
	free(param->philo_tab);
	free(param->forks);
	free(param->threads);
}

int	destroy_mutex(t_philo_param *param)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (i < param->number_of_philosophers)
	{
		ret = (ret
				|| pthread_mutex_destroy(&((param->philo_tab[i])
						.mutex_ate_enought))
				|| pthread_mutex_destroy(&(param->forks[i]))
				|| pthread_mutex_destroy(&((param->philo_tab[i])
						.mutex_last_eat)));
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

int	clean_exit(t_philo_param *param)
{
	int	status;

	status = found_error(param);
	status = (destroy_mutex(param) || status);
	free(param->philo_tab);
	free(param->forks);
	free(param->threads);
	return (status);
}
