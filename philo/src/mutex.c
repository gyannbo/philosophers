/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbonis <gbonis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 18:51:04 by gbonis            #+#    #+#             */
/*   Updated: 2024/09/12 13:28:25 by gbonis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	destroy_mutex(t_values *values)
{
	int	i;

	i = 0;
	while (i < values->nb_th)
	{
		if (pthread_mutex_destroy(&values->mx_arr[i]))
			return (-1);
		i++;
	}
	if (pthread_mutex_destroy(values->death_mx) == -1)
		return (-1);
	return (0);
}

int	create_mutex(t_values *values)
{
	int	i;
	int	nb_mx;

	i = 0;
	nb_mx = values->nb_th;
	while (nb_mx)
	{
		if (pthread_mutex_init(&values->mx_arr[i], NULL))
			return (-1);
		i++;
		nb_mx--;
	}
	if (pthread_mutex_init(values->death_mx, NULL))
		return (-1);
	return (0);
}
