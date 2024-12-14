/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbonis <gbonis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 15:01:31 by gbonis            #+#    #+#             */
/*   Updated: 2024/09/18 15:01:48 by gbonis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

double	get_time_ms(struct timeval *time_start)
{
	double			ms;
	struct timeval	time_cal;

	if (gettimeofday(&time_cal, NULL) == -1)
		return (-1);
	if (time_cal.tv_sec == time_start->tv_sec)
	{
		ms = (double)(time_cal.tv_usec - time_start->tv_usec) / 1000;
		return (ms);
	}
	else
	{
		ms = ((double)((1000000 + time_cal.tv_usec) - time_start->tv_usec)
				/ 1000) + ((time_cal.tv_sec - time_start->tv_sec - 1) * 1000);
		return (ms);
	}
}

int	get_diff_from_time_start(t_thread *thread_struct)
{
	double	now;

	now = get_time_ms(&thread_struct->time_start);
	if (now >= (double)thread_struct->args_array[TIME_DIE])
		return (-1);
	else
		return (0);
}

int	get_diff_eat(t_thread *thread_struct)
{
	double	ms;
	double	now;

	now = get_time_ms(&thread_struct->time_start);
	if (now == -1)
		return (-1);
	ms = now - thread_struct->start_eat_ms;
	if (ms < (double)thread_struct->args_array[TIME_DIE])
		return (0);
	else
		return (-1);
}
