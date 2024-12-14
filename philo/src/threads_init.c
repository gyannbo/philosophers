/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbonis <gbonis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 20:45:56 by gbonis            #+#    #+#             */
/*   Updated: 2024/09/18 14:53:35 by gbonis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	args_array_init(t_values *values, t_thread *thread_struct)
{
	thread_struct->args_array[0] = values->args_array[0];
	thread_struct->args_array[1] = values->args_array[1];
	thread_struct->args_array[2] = values->args_array[2];
	thread_struct->args_array[3] = values->args_array[3];
	thread_struct->args_array[4] = values->args_array[4];
	return (0);
}

void	*th_f(void *given_struct)
{
	t_thread	*thread_struct;

	thread_struct = ((t_thread *)given_struct);
	if (thread_struct->args_array[NB_MUST_EAT] != 0)
	{
		if (nb_eat_loop(thread_struct) == -1)
			return (NULL);
	}
	else
	{
		if (no_nb_eat_loop(thread_struct) == -1)
			return (NULL);
	}
	pthread_mutex_lock(thread_struct->death_mx);
	thread_struct->is_done = true;
	pthread_mutex_unlock(thread_struct->death_mx);
	return (NULL);
}

int	func_to_join(t_values *values, int nb_th_created)
{
	int	nb_th;
	int	y;

	nb_th = values->nb_th;
	y = 0;
	while (y < nb_th && y < nb_th_created)
	{
		if (pthread_join(values->th_arr[y], NULL) == -1)
			return (-1);
		y++;
	}
	if (pthread_join(values->checker_id, NULL) == -1)
		return (-1);
	return (0);
}

int	init_thread(t_values *values)
{
	int	y;
	int	nb_th;

	y = 0;
	nb_th = values->nb_th;
	init_threads_structs(values);
	if (pthread_create(&values->checker_id, NULL, checker_func, values))
		return (-1);
	while (nb_th)
	{
		if (pthread_create(&values->th_arr[y],
				NULL, th_f, &values->struc_arr[y]))
		{
			return (func_to_join(values, y));
		}
		y++;
		nb_th--;
	}
	if (func_to_join(values, y))
	{
		return (-1);
	}
	return (0);
}
