/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gbonis <gbonis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 15:29:24 by gbonis            #+#    #+#             */
/*   Updated: 2024/09/20 15:43:37 by gbonis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <limits.h>
# include <stddef.h>
# include <stdbool.h>

# define THREAD_MAX 61786

# define NB_THRDS 0
# define TIME_DIE 1
# define TIME_EAT 2
# define TIME_SLEEP 3
# define NB_MUST_EAT 4

# define THINK 0
# define FORK 1
# define EAT 2
# define SLEEP 3
# define DEATH 4
# define ERROR 100

typedef struct s_thread_struct
{
	struct timeval	time_start;
	double			start_eat_ms;
	int				th_max_numb;
	int				th_own_numb;
	int				flag_first_pass;
	int				args_array[5];
	pthread_mutex_t	*left_mutex;
	pthread_mutex_t	*right_mutex;
	pthread_mutex_t	*death_mx;
	bool			*death_flag;
	bool			is_done;
}	t_thread;

typedef struct s_values
{
	struct timeval	time_start;
	int				nb_th;
	int				args_array[5];
	bool			death_flag;
	pthread_t		*th_arr;
	pthread_t		checker_id;
	pthread_mutex_t	*mx_arr;
	pthread_mutex_t	*death_mx;
	t_thread		*struc_arr;	
}	t_values;

int			wrong_args(int argc, char **argv, t_values *values);
int			ft_atoi_overflow(const char *nptr, int *overflow);

int			init_arrays(t_values *values);
int			init_threads_structs(t_values *values);
int			init_thread(t_values *values);

int			args_array_init(t_values *values, t_thread *thread_struct);
int			create_mutex(t_values *values);
int			destroy_mutex(t_values *values);

int			print_string(int code, t_thread *thread_struct);

int			has_nb_eat(t_thread *thread_struct);
int			no_nb_eat(t_thread *thread_struct);

double		get_time_ms(struct timeval *time_start);
int			get_diff_eat(t_thread *thread_struct);
int			get_diff_from_time_start(t_thread *thread_struct);

int			try_to_die(t_thread *tread_struct, int code, double time);
int			check_death_flag(t_thread *thread_struct);

void		*checker_func(void *values);
void		loser_loop(t_thread *f_struct, int n, t_thread **loser, double t);

int			error_string(int code);
void		free_struct(t_values values);

void		smart_sleep(t_thread *thread, double deadline);
int			checker_diff_from_start(t_thread *thread_struct, double now);
int			checker_get_diff_eat(t_thread *thread_struct, double now);
int			should_i_die(t_thread *t, double time);
void		unlock_mx(t_thread *thread);
void		unlock_both_mx(t_thread *thread);
int			nb_eat_loop(t_thread *thread_struct);
int			no_nb_eat_loop(t_thread *thread_struct);
int			thread_eat(t_thread *t);
int			when_one_thread(t_thread *t);
#endif
