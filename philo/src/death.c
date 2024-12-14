/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbonis <gbonis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 19:08:40 by gbonis            #+#    #+#             */
/*   Updated: 2024/09/18 15:06:53 by gbonis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	should_i_die(t_thread *t, double time)
{
	if (t->flag_first_pass)
	{
		if (checker_diff_from_start(t, time) == -1)
		{
			return (1);
		}
	}
	else if (checker_get_diff_eat(t, time) == -1)
	{
		return (1);
	}
	return (0);
}

int	try_to_die(t_thread *t, int code, double time)
{
	if (*t->death_flag == false)
	{
		*t->death_flag = true;
		if (code == ERROR)
		{
			printf("something went wrong, probably with a syscall");
			printf(". pls try again\n");
			return (0);
		}
		printf("%f %d died\n", time, t->th_own_numb + 1);
	}
	else
	{
		return (-1);
	}
	return (0);
}
