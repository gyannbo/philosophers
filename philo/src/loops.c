/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loops.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbonis <gbonis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 12:25:16 by gbonis            #+#    #+#             */
/*   Updated: 2024/09/29 12:25:18 by gbonis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	nb_eat_loop(t_thread *thread_struct)
{
	while (thread_struct->args_array[NB_MUST_EAT])
	{
		if (thread_struct->th_own_numb % 3 == 0)
			usleep(1500);
		if (has_nb_eat(thread_struct) == -1)
			return (-1);
		usleep(1);
	}
	return (0);
}

int	no_nb_eat_loop(t_thread *thread_struct)
{
	while (1)
	{
		if (thread_struct->th_own_numb % 3 == 0)
			usleep(1500);
		if (no_nb_eat(thread_struct) == -1)
			return (-1);
		usleep(1);
	}
}
