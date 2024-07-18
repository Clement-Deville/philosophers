/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 15:23:01 by cdeville          #+#    #+#             */
/*   Updated: 2024/07/18 14:56:36 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers_bonus.h>

// int	init_sem(t_philo_param *param)
// {
// 	if (sem_init(&(param->forks_count), 1, param->number_of_philosophers))
// 		return (perror("sem_init"), 1);
// 	if (sem_init(&(param->sem_is_dead), 1, 1))
// 		return (sem_destroy(&(param->forks_count)), perror("sem_init"), 1);
// 	if (sem_init(&(param->sem_everyone_ate), 1, 1))
// 		return (sem_destroy(&(param->forks_count)),
// 			sem_destroy(&(param->sem_is_dead)), perror("sem_init"), 1);
// 	if (sem_init(&(param->sem_error), 1, 1))
// 		return (sem_destroy(&(param->forks_count)),
// 			sem_destroy(&(param->sem_everyone_ate)),
// 			sem_destroy(&(param->sem_is_dead)), perror("sem_init"), 1);
// 	if (sem_init(&(param->sem_print), 1, 1))
// 		return (sem_destroy(&(param->forks_count)),
// 			sem_destroy(&(param->sem_everyone_ate)),
// 			sem_destroy(&(param->sem_is_dead)),
// 			sem_destroy(&(param->sem_error)), perror("sem_init"), 1);
// 	if (sem_init(&(param->philo_eating), 1, param->number_of_philosophers / 2))
// 		return (sem_destroy(&(param->forks_count)),
// 			sem_destroy(&(param->sem_everyone_ate)),
// 			sem_destroy(&(param->sem_is_dead)),
// 			sem_destroy(&(param->sem_error)),
// 			sem_destroy(&(param->sem_print)), perror("sem_init"), 1);
// 	return (0);
// }

int	unlink_sem(void)
{
	sem_unlink(S_FORKS);
	sem_unlink(S_IS_DEAD);
	sem_unlink(S_EVERY);
	sem_unlink(S_PRINT);
	sem_unlink(S_EATING);
	sem_unlink(S_TAB);
	sem_unlink(S_GLOBAL);
	return (0);
}

int	close_sem(t_philo_param *param)
{
	if (param->forks_count == SEM_FAILED)
		return (1);
	if (sem_close(param->forks_count) == -1)
		return (perror("sem_close"), 1);
	// sem_unlink(S_FORKS);
	if (param->sem_is_dead == SEM_FAILED)
		return (1);
	if (sem_close(param->sem_is_dead) == -1)
		return (perror("sem_close"), 1);
	// sem_unlink(S_IS_DEAD);
	if (param->sem_everyone_ate == SEM_FAILED)
		return (1);
	if (sem_close(param->sem_everyone_ate) == -1)
		return (perror("sem_close"), 1);
	// sem_unlink(S_EVERY);
	if (param->sem_print == SEM_FAILED)
		return (1);
	if (sem_close(param->sem_print) == -1)
		return (perror("sem_close"), 1);
	// sem_unlink(S_PRINT);
	if (param->philo_eating == SEM_FAILED)
		return (1);
	if (sem_close(param->philo_eating) == -1)
		return (perror("sem_close"), 1);
	// sem_unlink(S_EATING);
	if (param->sem_pid_tab == SEM_FAILED)
		return (1);
	if (sem_close(param->sem_pid_tab) == -1)
		return (perror("sem_close"), 1);
	// sem_unlink(S_TAB);
	if (param->sem_global_terminate == SEM_FAILED)
		return (1);
	if (sem_close(param->sem_global_terminate) == -1)
		return (perror("sem_close"), 1);
	// sem_unlink(S_GLOBAL);
	return (0);
}

int	open_sem(t_philo_param *param)
{
	if (sem_init(&(param->sem_stop), 1, 1))
		return (perror("sem_init"), 1);
	// param->sem_can_die = sem_open(S_CAN_DIE, O_CREAT, 0644, 1);
	// if (param->sem_can_die == SEM_FAILED)
	// 	return (perror("sem_open"), close_sem(param), 1);
	// need to change to sem init and protect
	param->forks_count = sem_open(S_FORKS, O_CREAT, 0644,
			param->number_of_philosophers);
	if (param->forks_count == SEM_FAILED)
		return (perror("sem_open"), close_sem(param), 1);
	param->sem_is_dead = sem_open(S_IS_DEAD, O_CREAT, 0644, 0);
	if (param->sem_is_dead == SEM_FAILED)
		return (perror("sem_open"), close_sem(param), 1);
	param->sem_everyone_ate = sem_open(S_EVERY, O_CREAT, 0644, 0);
	if (param->sem_everyone_ate == SEM_FAILED)
		return (perror("sem_open"), close_sem(param), 1);
	param->sem_print = sem_open(S_PRINT, O_CREAT, 0644, 1);
	if (param->sem_print == SEM_FAILED)
		return (perror("sem_open"), close_sem(param), 1);
	param->philo_eating = sem_open(S_EATING, O_CREAT, 0644,
			param->number_of_philosophers / 2);
	if (param->philo_eating == SEM_FAILED)
		return (perror("sem_open"), close_sem(param), 1);
	param->sem_pid_tab = sem_open(S_TAB, O_CREAT, 0644, 1);
	if (param->sem_pid_tab == SEM_FAILED)
		return (perror("sem_open"), close_sem(param), 1);
	param->sem_global_terminate = sem_open(S_GLOBAL, O_CREAT, 0644, 0);
	if (param->sem_pid_tab == SEM_FAILED)
		return (perror("sem_open"), close_sem(param), 1);
	return (0);
}

int	init_sem(t_philo_param *param)
{
	unlink_sem();
	return (open_sem(param));
}

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
