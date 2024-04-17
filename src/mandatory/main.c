/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 10:28:30 by cdeville          #+#    #+#             */
/*   Updated: 2024/04/17 14:43:10 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

int	destroy_mutex(t_philo_param *param)
{
	int	i;

	i = 0;
	while (i < param->number_of_philosophers)
	{
		if (pthread_mutex_destroy(&(param->forks[i])))
		{
			ft_putstr_fd("Error at mutex destory\n", 2);
			return (-1);
		}
		i++;
	}
	return (0);
}

int	clean_exit(t_philo_param param)
{
	int	status;

	status = 0;
	status = destroy_mutex(&param);
	free(param.philo_tab);
	free(param.forks);
	free(param.threads);
	return (status);
}

int	main(int argc, char *argv[])
{
	t_philo_param	param;
	long			i;

	i = 0;
	if (init(&param, argc, argv))
		return (1);
	while (i < param.number_of_philosophers)
	{
		pthread_create(&(param.threads[i]), NULL, pthread_fct, (void *)&(param.philo_tab[i]));
		i++;
	}
	sleep(1);
	if (join_all(param) != 0)
		return (clean_exit(param), 1);
	return (clean_exit(param) || 0);
}
