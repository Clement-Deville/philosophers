/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 15:23:01 by cdeville          #+#    #+#             */
/*   Updated: 2024/07/19 10:56:53 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers_bonus.h>

int	allocate(t_philo_param *param)
{
	param->pid_tab = (int *)malloc(sizeof(int)
			* (param->number_of_philosophers));
	if (param->pid_tab == NULL || init_sem(param) == 1)
		return (ft_putstr_fd("Erreur de malloc\n", 2), 1);
	param->philo_tab = (t_philo *)malloc(sizeof(t_philo)
			* (int)(param->number_of_philosophers));
	if (param->philo_tab == NULL)
		return (free(param->pid_tab),
			ft_putstr_fd("Erreur de malloc\n", 2), 1);
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

int	init(t_philo_param *param, int argc, char *argv[])
{
	if (get_parameters(param, argc, argv))
		return (1);
	if (allocate(param))
		return (1);
	param->stop = FALSE;
	gettimeofday(&(param->clock), NULL);
	if (create_philo(param))
		return (1);
	param->error = FALSE;
	param->everyone_ate = FALSE;
	return (0);
}
