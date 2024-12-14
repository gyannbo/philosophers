/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unlock_mutexes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbonis <gbonis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 14:51:12 by gbonis            #+#    #+#             */
/*   Updated: 2024/09/27 14:51:40 by gbonis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	unlock_mx(t_thread *thread)
{
	pthread_mutex_unlock(thread->right_mutex);
}

void	unlock_both_mx(t_thread *thread)
{
	pthread_mutex_unlock(thread->right_mutex);
	pthread_mutex_unlock(thread->left_mutex);
}
