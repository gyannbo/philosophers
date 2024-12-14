/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_thread.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbonis <gbonis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 12:01:36 by gbonis            #+#    #+#             */
/*   Updated: 2024/09/20 12:36:10 by gbonis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static t_thread	*pick_loser(t_thread *first_struct, double time)
{
	t_thread		*loser;
	pthread_mutex_t	*death_mutex_temp;

	death_mutex_temp = first_struct->death_mx;
	loser = NULL;
	loser_loop(first_struct, first_struct->args_array[NB_THRDS], &loser, time);
	return (loser);
}

int	is_it_done(t_values *values)
{
	int	i;

	i = 0;
	pthread_mutex_lock(values->death_mx);
	while (i < values->nb_th)
	{
		if (values->struc_arr[i].is_done == false)
		{
			pthread_mutex_unlock(values->death_mx);
			return (0);
		}
	i++;
	}
	pthread_mutex_unlock(values->death_mx);
	return (1);
}

int	checker_time_death(t_thread *thread_struct, double time)
{
	int			i;
	t_thread	*loser;

	i = 0;
	loser = pick_loser(thread_struct, time);
	if (!loser)
		return (0);
	pthread_mutex_lock(thread_struct->death_mx);
	try_to_die(loser, 0, time);
	pthread_mutex_unlock(thread_struct->death_mx);
	return (-1);
}

void	*checker_func(void *values)
{
	double		time;

	while (1)
	{
		time = get_time_ms(&((t_values *)values)->time_start);
		if (checker_time_death(((t_values *)values)->struc_arr, time) == -1)
			return (NULL);
		usleep(8000);
		if ((int)time % 20 == 0)
		{
			if (is_it_done((t_values *)values))
				return (NULL);
		}
	}
	return (NULL);
}
