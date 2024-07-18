/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 17:31:34 by cdeville          #+#    #+#             */
/*   Updated: 2024/07/18 18:23:10 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers_bonus.h>

int	execute_one(t_philo_param *param)
{
	(void)param;
	clean_exit(param);
	return (0);
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


// Mon idee d'algo, alterner entre pair et impair:
// On commence par les pairs puis par les impairs, cela se traduit par un booleen
// qui decide du comportement, apres avoir manger, le philo prend et relache la premiere
// puis la fois d'apres il prend la premiere et essaie d'avoir la deuxieme
// PS : Faut il un temps d'attente particulier entre les deux phases?
