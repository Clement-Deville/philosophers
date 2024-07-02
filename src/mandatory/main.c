/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 10:28:30 by cdeville          #+#    #+#             */
/*   Updated: 2024/07/02 15:14:14 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

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

int	execute_one(t_philo_param *param)
{
	if (pthread_create(&(param->threads[0]),
			NULL, pthread_fct_for_one, (void *)&(param->philo_tab[0])))
	{
		set_error(param);
		return (clean_exit(param));
	}
	return (0);
}

int	execute_multi(t_philo_param *param)
{
	long	i;

	i = 0;
	while (i < param->number_of_philosophers)
	{
		if (pthread_create(&(param->threads[i]),
				NULL, pthread_fct, (void *)&(param->philo_tab[i])))
		{
			set_error(param);
			if (join_valids(param, i))
				return (clean_exit(param), 1);
			return (clean_exit(param));
		}
		i++;
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_philo_param	param;
	t_bool			error;

	if (init(&param, argc, argv))
		return (1);
	if (param.number_of_philosophers == 1)
	{
		if (execute_one(&param))
			return (1);
	}
	else
	{
		if (execute_multi(&param))
			return (1);
	}
	error = check_stop_conditions(&param);
	usleep(100);
	if (join_all(&param) != 0)
		return (clean_exit(&param), 1);
	return (clean_exit(&param) || error);
}
