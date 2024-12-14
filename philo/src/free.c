/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbonis <gbonis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 18:04:58 by gbonis            #+#    #+#             */
/*   Updated: 2024/09/09 13:53:33 by gbonis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	free_struct(t_values values)
{
	free(values.th_arr);
	free(values.mx_arr);
	free(values.struc_arr);
	free(values.death_mx);
}
