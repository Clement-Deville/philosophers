/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthread_for_one_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 16:00:15 by cdeville          #+#    #+#             */
/*   Updated: 2024/07/25 16:00:37 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers_bonus.h>

void	*pthread_actions_for_one(void *argument)
{
	int		count;
	t_philo	*philo;

	philo = (t_philo *)argument;
	count = 0;
	do_print(FORK, philo);
	while (do_continue(philo) == TRUE)
	{
		usleep(500);
	}
	return (NULL);
}
