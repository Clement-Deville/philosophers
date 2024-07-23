/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 17:31:34 by cdeville          #+#    #+#             */
/*   Updated: 2024/07/19 11:05:40 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers_bonus.h>

int	execute_one(t_philo_param *param)
{
	long	i;

	i = 0;
	if (init_global_monitoring(param))
		return (1);
	while (i < param->number_of_philosophers)
	{
		param->pid_tab[i] = fork();
		if (param->pid_tab[i] == -1)
		{
			perror("Fork");
			set_error(param);
			wait_for_all(param, i);
			join_monitoring(param);
			return (clean_exit(param));
		}
		if (param->pid_tab[i] == 0)
			exit (process_one(&(param->philo_tab[i])));
		i++;
	}
	sem_post(param->sem_pid_tab);
	if (wait_for_all(param, param->number_of_philosophers)
		|| join_monitoring(param))
		return (clean_exit(param), 1);
	return (clean_exit(param), 0);
}

int	execute_multi(t_philo_param *param)
{
	long	i;

	i = 0;
	if (init_global_monitoring(param))
		return (1);
	while (i < param->number_of_philosophers)
	{
		param->pid_tab[i] = fork();
		if (param->pid_tab[i] == -1)
		{
			perror("Fork");
			set_error(param);
			wait_for_all(param, i);
			join_monitoring(param);
			return (clean_exit(param));
		}
		if (param->pid_tab[i] == 0)
			exit (process_multi(&(param->philo_tab[i])));
		i++;
	}
	sem_post(param->sem_pid_tab);
	if (wait_for_all(param, param->number_of_philosophers)
		|| join_monitoring(param))
		return (clean_exit(param), 1);
	return (clean_exit(param), 0);
}

int	main(int argc, char *argv[])
{
	t_philo_param	param;

	if (init(&param, argc, argv))
		return (1);
	if (param.number_of_philosophers == 1)
		return (execute_one(&param));
	else
		return (execute_multi(&param));
}
