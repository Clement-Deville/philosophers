/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdeville <cdeville@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/17 11:17:49 by cdeville          #+#    #+#             */
/*   Updated: 2024/07/17 11:17:58 by cdeville         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers_bonus.h>

long	get_time(void)
{
	struct timeval	time;
	long			ms;

	gettimeofday(&time, NULL);
	ms = time.tv_sec * 1000;
	if (time.tv_usec)
		ms += time.tv_usec / 1000;
	return (ms);
}

long	time_passed(const struct timeval start)
{
	struct timeval	end;
	long			miliseconds;
	long			micro;

	gettimeofday(&end, NULL);
	miliseconds = (end.tv_sec - start.tv_sec) * 1000;
	micro = end.tv_usec - start.tv_usec;
	if (micro)
		miliseconds += micro / 1000;
	return (miliseconds);
}
