/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sem_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 10:56:32 by cdeville          #+#    #+#             */
/*   Updated: 2024/07/24 17:21:30 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers_bonus.h>

int	unlink_sem(void)
{
	sem_unlink(S_ERR);
	sem_unlink(S_FORKS);
	sem_unlink(S_IS_DEAD);
	sem_unlink(S_EVERY);
	sem_unlink(S_PRINT);
	sem_unlink(S_EATING);
	sem_unlink(S_TAB);
	sem_unlink(S_GLOBAL);
	return (0);
}

void	close_sem(t_philo_param *param)
{
	sem_destroy(&(param->sem_stop));
	sem_close(param->sem_error);
	sem_close(param->forks_count);
	sem_close(param->sem_is_dead);
	sem_close(param->sem_everyone_ate);
	sem_close(param->sem_print);
	sem_close(param->philo_eating);
	sem_close(param->sem_pid_tab);
	sem_close(param->sem_global_terminate);
}

int	open_sem_others(t_philo_param *param)
{
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
	if (param->sem_global_terminate == SEM_FAILED)
		return (perror("sem_open"), close_sem(param), 1);
	return (0);
}

int	init_sem(t_philo_param *param)
{
	unlink_sem();
	if (sem_init(&(param->sem_stop), 1, 1))
		return (perror("sem_init"), 1);
	param->sem_error = sem_open(S_ERR, O_CREAT, 0644, 0);
	if (param->sem_error == SEM_FAILED)
		return (perror("sem_open"), close_sem(param), 1);
	param->forks_count = sem_open(S_FORKS, O_CREAT, 0644,
			param->number_of_philosophers);
	if (param->forks_count == SEM_FAILED)
		return (perror("sem_open"), close_sem(param), 1);
	param->sem_is_dead = sem_open(S_IS_DEAD, O_CREAT, 0644, 0);
	if (param->sem_is_dead == SEM_FAILED)
		return (perror("sem_open"), close_sem(param), 1);
	return (open_sem_others(param));
}

// int	open_sem_others_child(t_philo_param *param)
// {
// 	param->sem_everyone_ate = sem_open(S_EVERY, 0);
// 	if (param->sem_everyone_ate == SEM_FAILED)
// 		return (perror("sem_open"), close_sem(param), 1);
// 	param->sem_print = sem_open(S_PRINT, 0);
// 	if (param->sem_print == SEM_FAILED)
// 		return (perror("sem_open"), close_sem(param), 1);
// 	param->philo_eating = sem_open(S_EATING, 0);
// 	if (param->philo_eating == SEM_FAILED)
// 		return (perror("sem_open"), close_sem(param), 1);
// 	param->sem_pid_tab = sem_open(S_TAB, 0);
// 	if (param->sem_pid_tab == SEM_FAILED)
// 		return (perror("sem_open"), close_sem(param), 1);
// 	param->sem_global_terminate = sem_open(S_GLOBAL, 0);
// 	if (param->sem_global_terminate == SEM_FAILED)
// 		return (perror("sem_open"), close_sem(param), 1);
// 	return (0);
// }

// int	init_sem_child(t_philo_param *param)
// {
// 	param->sem_error = sem_open(S_ERR, 0);
// 	if (param->sem_error == SEM_FAILED)
// 		return (perror("sem_open"), close_sem(param), 1);
// 	param->forks_count = sem_open(S_FORKS, 0);
// 	if (param->forks_count == SEM_FAILED)
// 		return (perror("sem_open"), close_sem(param), 1);
// 	param->sem_is_dead = sem_open(S_IS_DEAD, 0);
// 	if (param->sem_is_dead == SEM_FAILED)
// 		return (perror("sem_open"), close_sem(param), 1);
// 	return (open_sem_others_child(param));
// }

// int	open_sem_others_child(t_philo_param *param)
// {
// 	param->sem_everyone_ate = sem_open(S_EVERY, 0, 0);
// 	if (param->sem_everyone_ate == SEM_FAILED)
// 		return (perror("sem_open"), close_sem(param), 1);
// 	param->sem_print = sem_open(S_PRINT, 0, 1);
// 	if (param->sem_print == SEM_FAILED)
// 		return (perror("sem_open"), close_sem(param), 1);
// 	param->philo_eating = sem_open(S_EATING, 0,
// 			param->number_of_philosophers / 2);
// 	if (param->philo_eating == SEM_FAILED)
// 		return (perror("sem_open"), close_sem(param), 1);
// 	param->sem_pid_tab = sem_open(S_TAB, 0, 1);
// 	if (param->sem_pid_tab == SEM_FAILED)
// 		return (perror("sem_open"), close_sem(param), 1);
// 	param->sem_global_terminate = sem_open(S_GLOBAL, 0, 0);
// 	if (param->sem_global_terminate == SEM_FAILED)
// 		return (perror("sem_open"), close_sem(param), 1);
// 	return (0);
// }

// int	init_sem_child(t_philo_param *param)
// {
// 	unlink_sem();
// 	if (sem_init(&(param->sem_stop), 1, 1))
// 		return (perror("sem_init"), 1);
// 	param->sem_error = sem_open(S_ERR, 0, 0);
// 	if (param->sem_error == SEM_FAILED)
// 		return (perror("sem_open"), close_sem(param), 1);
// 	param->forks_count = sem_open(S_FORKS, 0,
// 			param->number_of_philosophers);
// 	if (param->forks_count == SEM_FAILED)
// 		return (perror("sem_open"), close_sem(param), 1);
// 	param->sem_is_dead = sem_open(S_IS_DEAD, 0, 0);
// 	if (param->sem_is_dead == SEM_FAILED)
// 		return (perror("sem_open"), close_sem(param), 1);
// 	return (open_sem_others(param));
// }
