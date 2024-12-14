/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbonis <gbonis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 19:22:10 by gbonis            #+#    #+#             */
/*   Updated: 2024/09/20 16:34:33 by gbonis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	init_everything(int argc, char **argv, t_values *values)
{
	if (gettimeofday(&values->time_start, NULL) == -1)
		return (-1);
	if (wrong_args(argc, argv, values))
		return (-1);
	if (init_arrays(&(*values)))
	{
		free_struct(*values);
		return (error_string(1));
	}
	values->death_flag = false;
	if (create_mutex(&(*values)))
	{
		free_struct(*values);
		return (error_string(2));
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_values	values;	

	if (init_everything(argc, argv, &values) == -1)
		return (0);
	init_thread(&values);
	if (values.death_flag == false)
		printf("nobody died\n");
	destroy_mutex(&values);
	free_struct(values);
	printf("total program time : %f ms\n", get_time_ms(&values.time_start));
	return (0);
}
