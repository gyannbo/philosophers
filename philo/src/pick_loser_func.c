/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pick_loser_func.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbonis <gbonis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 10:11:33 by gbonis            #+#    #+#             */
/*   Updated: 2024/09/20 12:51:13 by gbonis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"philosophers.h"

int	checker_diff_from_start(t_thread *thread_struct, double now)
{
	if (now > thread_struct->args_array[TIME_DIE])
	{
		return (-1);
	}
	else
		return (0);
}

int	checker_get_diff_eat(t_thread *thread_struct, double now)
{
	int	ms;

	ms = now - thread_struct->start_eat_ms;
	if (ms <= thread_struct->args_array[TIME_DIE])
		return (0);
	else
		return (-1);
}

int	if_not_done(t_thread *first_struct, t_thread **loser, double t)
{
	if (first_struct->flag_first_pass)
	{
		if (checker_diff_from_start(first_struct, t) == -1)
		{
			*loser = first_struct;
			return (1);
		}
	}
	else if (checker_get_diff_eat(first_struct, t) == -1)
	{
		if (*loser == NULL)
			*loser = first_struct;
		else
		{
			if ((*loser)->start_eat_ms > first_struct->start_eat_ms)
				*loser = first_struct;
		}
	}
	return (0);
}

void	loser_loop(t_thread *first_struct, int n, t_thread **loser, double t)
{
	int				i;
	pthread_mutex_t	*death_mx;

	i = 0;
	death_mx = first_struct->death_mx;
	while (i < n)
	{
		pthread_mutex_lock(death_mx);
		if (first_struct->is_done == true)
		{
			i++;
			first_struct++;
			pthread_mutex_unlock(death_mx);
			continue ;
		}
		if (if_not_done(first_struct, loser, t))
		{
			pthread_mutex_unlock(death_mx);
			return ;
		}
		pthread_mutex_unlock(death_mx);
		i++;
		first_struct++;
		usleep(1);
	}
}
