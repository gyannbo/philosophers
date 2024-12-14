/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_loop.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbonis <gbonis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 16:21:29 by gbonis            #+#    #+#             */
/*   Updated: 2024/09/18 14:32:37 by gbonis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	code_func(t_thread *thread_struct, int code, double t)
{
	if (code == EAT)
	{
		thread_struct->flag_first_pass = 0;
		thread_struct->start_eat_ms = t;
		printf("%f %d is eating\n", t, thread_struct->th_own_numb + 1);
		return (0);
	}
	if (code == SLEEP)
	{
		printf("%f %d is sleeping\n", t, thread_struct->th_own_numb + 1);
		return (0);
	}
	if (code == THINK)
	{
		printf("%f %d is thinking\n", t, thread_struct->th_own_numb + 1);
		return (0);
	}
	if (code == FORK)
	{
		printf("%f %d has taken a fork\n", t, thread_struct->th_own_numb + 1);
		return (0);
	}
	return (0);
}

int	print_string(int code, t_thread *thread_struct)
{
	double	t;

	pthread_mutex_lock(thread_struct->death_mx);
	if (*thread_struct->death_flag == true)
	{
		pthread_mutex_unlock(thread_struct->death_mx);
		return (-1);
	}
	t = get_time_ms(&thread_struct->time_start);
	if (should_i_die(thread_struct, t))
	{
		try_to_die(thread_struct, 0, t);
		pthread_mutex_unlock(thread_struct->death_mx);
		return (-1);
	}
	code_func(thread_struct, code, t);
	pthread_mutex_unlock(thread_struct->death_mx);
	usleep(1);
	return (0);
}

int	when_one_thread(t_thread *t)
{
	while (1)
	{
		if (get_diff_from_time_start(t) == -1)
		{
			pthread_mutex_lock(t->death_mx);
			try_to_die(t, 0, get_time_ms(&t->time_start));
			pthread_mutex_unlock(t->death_mx);
			pthread_mutex_unlock(t->right_mutex);
			return (-1);
		}
	}
}

int	has_nb_eat(t_thread *thread)
{
	if (print_string(THINK, thread) == -1)
		return (-1);
	if (thread_eat(thread) == -1)
		return (-1);
	thread->args_array[NB_MUST_EAT]--;
	if (print_string(SLEEP, thread) == -1)
	{
		unlock_both_mx(thread);
		return (-1);
	}
	unlock_both_mx(thread);
	smart_sleep(thread, thread->args_array[SLEEP]);
	return (0);
}

int	no_nb_eat(t_thread *thread)
{
	if (print_string(THINK, thread))
		return (-1);
	if (thread_eat(thread) == -1)
		return (-1);
	if (print_string(SLEEP, thread) == -1)
	{
		unlock_both_mx(thread);
		return (-1);
	}
	unlock_both_mx(thread);
	smart_sleep(thread, thread->args_array[SLEEP]);
	return (0);
}
