/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_eat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbonis <gbonis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 13:43:00 by gbonis            #+#    #+#             */
/*   Updated: 2024/09/29 13:43:03 by gbonis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"philosophers.h"

int	thread_eat(t_thread *thread)
{
	pthread_mutex_lock(thread->right_mutex);
	if (print_string(FORK, thread) == -1)
	{
		unlock_mx(thread);
		return (-1);
	}
	if (thread->args_array[NB_THRDS] == 1)
	{
		when_one_thread(thread);
		return (-1);
	}
	pthread_mutex_lock(thread->left_mutex);
	if (print_string(FORK, thread) == -1)
	{
		unlock_both_mx(thread);
		return (-1);
	}
	if (print_string(EAT, thread) == -1)
	{
		unlock_both_mx(thread);
		return (-1);
	}
	smart_sleep(thread, thread->args_array[TIME_EAT]);
	return (0);
}
