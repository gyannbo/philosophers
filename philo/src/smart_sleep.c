/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smart_sleep.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbonis <gbonis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 19:11:49 by gbonis            #+#    #+#             */
/*   Updated: 2024/09/23 19:11:50 by gbonis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	smart_sleep(t_thread *thread, double amount)
{
	double	t;

	t = get_time_ms(&thread->time_start);
	while (1)
	{
		if (get_time_ms(&thread->time_start) - t >= amount)
		{
			break ;
		}
		usleep(50);
	}
}
