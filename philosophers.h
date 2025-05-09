/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiensal <jpiensal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 10:27:56 by jpiensal          #+#    #+#             */
/*   Updated: 2025/05/09 16:47:37 by jpiensal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <string.h>
# include <stdint.h>
# include <stdbool.h>

typedef enum e_errors
{
	e_none,
	e_input,
	e_create_master,
	e_create_philo,
	e_memory,
	e_join,
	e_lock,
	e_unlock,
	e_gettime,
	e_undefined_behaviour,
}	t_errors;

typedef enum e_action
{
	e_die,
	e_gotfork,
	e_eat,
	e_sleep,
	e_think,
}	t_action;

typedef struct s_master
{
	int				total_philos;
	int				times_to_eat;
	_Atomic int		is_eaten;
	_Atomic int		philos_started;
	int				philos_initialised;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	time_to_think;
	unsigned int	begin_program;
	struct s_philo	**philo_arr;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	init_lock;
	pthread_mutex_t	time_lock;
	pthread_mutex_t	*forks;
	bool			is_dead;
	bool			error;
	bool			is_finished;
}	t_master;

typedef struct s_philo
{
	int				id;
	int				eat_count;
	unsigned int	eaten;
}	t_philo;

/*
 * philosopher_utils.c
 */
unsigned int	philo_atoi(char *nbr);
int				philo_error(t_master *master, t_errors n);
unsigned int	get_current_time(t_master *master);
/*
 * philosophers.c
 */
void			*start_thread(void *arg);
/*
 * observer.c
 */
void			*observer(void *arg);
/*
 * mutex.c
 */
int				init_locks(t_master *master);
int				destroy_locks(t_master *master);
/*
 * actions.c
 */
void			print(t_master *master, int id, t_action action);
void			release_forks(t_master *master, t_philo *philo,
					bool is_left_fork);
void			die(t_master *master, t_philo *philo);
int				take_first_fork(t_master *master, t_philo *philo);
int				take_second_fork(t_master *master, t_philo *philo);
/*
 * prints.c
 */
void			print_eat(t_master *master, int id);
void			print_sleep(t_master *master, int id);
void			print_think(t_master *master, int id);
void			print_dead(t_master *master, int id);
void			print_got_fork(t_master *master, int id);
/*
 * threads.c
 */
int				create_threads(t_master *master, pthread_t *philo);
int				join_threads(t_master *master, pthread_t *philo);

#endif
