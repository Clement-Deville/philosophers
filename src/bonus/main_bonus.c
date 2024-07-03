/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 17:31:34 by cdeville          #+#    #+#             */
/*   Updated: 2024/07/03 16:39:26 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers_bonus.h>

void	destroy_error(t_philo_param *param)
{
	if (param->forks == SEM_FAILED)
		return ;
	sem_close(param->forks);
	sem_unlink("forks");
	if (param->sem_is_dead == SEM_FAILED)
		return ;
	sem_close(param->sem_is_dead);
	sem_unlink("sem_is_dead");
	if (param->sem_everyone_ate == SEM_FAILED)
		return ;
	sem_close(param->sem_everyone_ate);
	sem_unlink("sem_everyone_ate");
	if (param->sem_error == SEM_FAILED)
		return ;
	sem_close(param->sem_error);
	sem_unlink("sem_error");
	if (param->sem_print == SEM_FAILED)
		return ;
	sem_close(param->sem_print);
	sem_unlink("sem_print");
}

int	init_sem(t_philo_param *param)
{
	if (sem_init(param->forks, 1, param->number_of_philosophers))
		return (destroy_error(param), perror("sem_init"), 1);
	if (sem_init(param->sem_is_dead, 1, 1))
		return (destroy_error(param), perror("sem_init"), 1);
	if (sem_init(param->sem_everyone_ate, 1, 1))
		return (destroy_error(param), perror("sem_init"), 1);
	if (sem_init(param->sem_error, 1, 1))
		return (destroy_error(param), perror("sem_init"), 1);
	if (sem_init(param->sem_print, 1, 1))
		return (destroy_error(param), perror("sem_init"), 1);
	return (0);
}

int	open_and_init_sem(t_philo_param *param)
{
	param->forks = sem_open("forks", O_CREAT);
	if (param->forks == SEM_FAILED)
		return (perror("int_sem"), 1);
	param->sem_is_dead = sem_open("sem_is_dead", O_CREAT);
	if (param->forks == SEM_FAILED)
		return (destroy_error(param), perror("int_sem"), 1);
	param->sem_everyone_ate = sem_open("sem_everyone_ate", O_CREAT);
	if (param->forks == SEM_FAILED)
		return (destroy_error(param), perror("int_sem"), 1);
	param->sem_error = sem_open("sem_error", O_CREAT);
	if (param->forks == SEM_FAILED)
		return (destroy_error(param), perror("int_sem"), 1);
	param->sem_print = sem_open("sem_print", O_CREAT);
	if (param->forks == SEM_FAILED)
		return (destroy_error(param), perror("int_sem"), 1);
	return (init_sem(param));
}

int	allocate(t_philo_param *param)
{
	param->pid_tab = (int *)malloc(sizeof(int)
			* (param->number_of_philosophers));
	if (param->pid_tab == NULL || open_and_init_sem(param) == 1)
		return (ft_putstr_fd("Erreur de malloc\n", 2), 1);
	param->philo_tab = (t_philo *)malloc(sizeof(t_philo)
			* (param->number_of_philosophers));
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
	param->is_dead = FALSE;
	gettimeofday(&(param->clock), NULL);
	if (create_philo(param))
		return (destroy_error(param), 1);
	param->error = FALSE;
	param->everyone_ate = FALSE;
	return (0);
}

int	main(int argc, char *argv[])
{
	t_philo_param	param;

	if (init(&param, argc, argv))
		return (1);
}


// Mon idee d'algo, alterner entre pair et impair:
// On commence par les pairs puis par les impairs, cela se traduit par un booleen
// qui decide du comportement, apres avoir manger, le philo prend et relache la premiere
// puis la fois d'apres il prend la premiere et essaie d'avoir la deuxieme
// PS : Faut il un temps d'attente particulier entre les deux phases?
