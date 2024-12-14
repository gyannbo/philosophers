/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_threads_structs.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbonis <gbonis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 15:43:21 by gbonis            #+#    #+#             */
/*   Updated: 2024/09/13 15:50:48 by gbonis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_threads_structs(t_values *values)
{
	int	i;

	i = 0;
	while (i < values->args_array[NB_THRDS])
	{
		values->struc_arr[i].th_max_numb = values->nb_th;
		values->struc_arr[i].th_own_numb = i;
		values->struc_arr[i].time_start.tv_sec = values->time_start.tv_sec;
		values->struc_arr[i].time_start.tv_usec = values->time_start.tv_usec;
		values->struc_arr[i].flag_first_pass = 1;
		args_array_init(values, &values->struc_arr[i]);
		if (i == values->nb_th - 1)
			values->struc_arr[i].right_mutex = &values->mx_arr[i];
		else
			values->struc_arr[i].left_mutex = &values->mx_arr[i];
		if (i == values->nb_th - 1)
			values->struc_arr[i].left_mutex = &values->mx_arr[0];
		else
			values->struc_arr[i].right_mutex = &values->mx_arr[i + 1];
		values->struc_arr[i].death_mx = values->death_mx;
		values->struc_arr[i].death_flag = &values->death_flag;
		values->struc_arr[i].is_done = false;
		i++;
	}
	return (0);
}
