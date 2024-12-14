/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wrong_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbonis <gbonis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 17:32:11 by gbonis            #+#    #+#             */
/*   Updated: 2024/09/06 16:00:20 by gbonis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static	int	print_usage(int argc)
{
	if (argc != 5 && argc != 6)
	{
		printf("usage: ./philo <number_of_philosophers> <time_to_die_ms>");
		printf(" <time_to_eat_ms> <time_to_sleep_ms> ");
		printf("<(opt)number_of_time_must_eat>\n");
		return (-1);
	}
	return (0);
}

static	int	is_digit(char *s)
{
	int	error;

	error = 0;
	while (*s)
	{
		if (*s == '-')
		{
			printf("args can't be negative numbers\n");
			print_usage(0);
			return (-1);
		}
		if (!(*s >= 48 && *s <= 57))
			error = -1;
		s++;
	}
	if (error)
		printf("args not digits\n");
	return (error);
}

static	int	parse_digit_n_overflow(int argc, char **argv)
{
	int	i;
	int	overflow;
	int	is_zero;

	i = 1;
	overflow = 0;
	while (i < argc)
	{
		if (is_digit(argv[i]))
			return (-1);
		is_zero = ft_atoi_overflow(argv[i], &overflow);
		if (overflow)
		{
			printf("overflow on args\n");
			return (-1);
		}
		if (!is_zero)
		{
			printf("args value can't be zero\n");
			print_usage(0);
			return (-1);
		}
		i++;
	}
	return (0);
}

void	fill_args_array(int argc, char **argv, int args_array[5])
{
	int	i_args;
	int	i_array;
	int	overflow;

	i_args = 1;
	i_array = 0;
	overflow = 0;
	if (argc == 5)
		args_array[NB_MUST_EAT] = 0;
	while (i_args < argc)
	{
		args_array[i_array] = ft_atoi_overflow(argv[i_args], &overflow);
		i_args++;
		i_array++;
	}
}

int	wrong_args(int argc, char **argv, t_values *values)
{
	if (argc != 5 && argc != 6)
	{
		printf("wrong args numbers\n");
		print_usage(argc);
		return (-1);
	}
	if (parse_digit_n_overflow(argc, argv))
		return (-1);
	fill_args_array(argc, argv, values->args_array);
	if (values->args_array[NB_THRDS] > THREAD_MAX)
	{
		printf("too much threads, max = %d\n", THREAD_MAX);
		return (-1);
	}
	if (values->args_array[NB_THRDS] == 1)
		printf("only 1 fork, this poor man's gonna die\n");
	values->nb_th = values->args_array[NB_THRDS];
	return (0);
}
