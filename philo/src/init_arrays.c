/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_arrays.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbonis <gbonis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 15:03:29 by gbonis            #+#    #+#             */
/*   Updated: 2024/09/18 14:32:35 by gbonis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	error_string(int code)
{
	if (code == 1)
		write(1, "malloc problem \n", 16);
	if (code == 2)
		write(1, "mutex init problem\n", 19);
	return (-1);
}

int	init_arrays(t_values *values)
{
	values->th_arr = malloc(sizeof (pthread_t) * values->nb_th);
	if (values->th_arr == NULL)
		return (-1);
	values->mx_arr = malloc(sizeof (pthread_mutex_t) * values->nb_th);
	if (values->mx_arr == NULL)
	{
		free(values->th_arr);
		return (-1);
	}
	values->struc_arr = malloc(sizeof (t_thread) * values->nb_th);
	if (values->struc_arr == NULL)
	{
		free(values->th_arr);
		free(values->mx_arr);
		return (-1);
	}
	values->death_mx = malloc(sizeof (pthread_mutex_t));
	if (values->death_mx == NULL)
	{
		free(values->th_arr);
		free(values->mx_arr);
		free(values->struc_arr);
		return (-1);
	}
	return (0);
}
