/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 15:02:34 by cdeville          #+#    #+#             */
/*   Updated: 2024/07/17 14:30:07 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers_bonus.h>

int	take_forks(t_philo *philo)
{
	t_philo_param	*param;

	param = philo->param;
	// if (!param)
	// 	printf("ERROOOOOOOOOOOOOOOOOR, PHILO NUMBER IS %ld\n", philo->philo_number);
	// else
	// 	printf("WORKING with param adress: %p\n", param);
	// // a retirer
	if (sem_wait(param->philo_eating))
		return (perror("sem_wait"), 1);
	// //
	// printf("philo_eating\n");
	// //
	if (sem_wait(param->forks_count))
		return (sem_post(param->philo_eating), perror("sem_wait"), 1);
	// //
	// printf("fork_count\n");
	// //
	if (sem_wait(param->forks_count))
		return (sem_post(param->philo_eating),
			sem_post(param->forks_count),
			perror("sem_wait"), 1);
	// //
	// printf("fork_count\n");
	// //
	if (do_print(FORK, philo) || do_print(FORK, philo))
		return (sem_post(param->philo_eating),
			sem_post(param->forks_count),
			sem_post(param->forks_count),
			perror("sem_wait"), 1);
	return (0);
}
