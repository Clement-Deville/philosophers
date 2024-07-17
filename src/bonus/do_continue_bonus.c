/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_continue_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 10:40:27 by cdeville          #+#    #+#             */
/*   Updated: 2024/07/17 17:22:15 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers_bonus.h>

int	do_continue(t_philo *philo)
{
	if (do_terminate(philo))
		return (FALSE);
	return (TRUE);
}
