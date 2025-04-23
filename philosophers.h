/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiensal <jpiensal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 10:27:56 by jpiensal          #+#    #+#             */
/*   Updated: 2025/04/23 16:04:29 by jpiensal         ###   ########.fr       */
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
	int				philo_ids;
	int				times_to_eat;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	time_to_think;
	unsigned int	begin_program;
	struct s_philo	**philo_arr;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	*forks;
	bool			is_dead;
	bool			error;
}	t_master;

typedef struct s_philo
{
	int				id;
	int				eat_count;
	unsigned int	eaten;
	bool			is_eating;
}	t_philo;

unsigned int	philo_atoi(char *nbr);
int				philo_error(t_master *master, t_errors n);
int				philosophers(t_master *master, int count);
unsigned int	get_current_time(void);
bool			check_death(t_master *master);
void			do_action(t_master *master, t_action action);

/*
 * actions.c
 */
void			release_forks(t_master *master, t_philo *philo,
				bool is_left_fork);
void			die(t_master *master, t_philo *philo);
int				take_right_fork(t_master *master, t_philo *philo);
int				take_left_fork(t_master *master, t_philo *philo);
void			print(t_master *master, t_philo *philo, t_action action);
/*
 * prints.c
 */
void			print_got_fork(t_master *master, t_philo *philo);
void			print_dead(t_master *master, t_philo *philo);
void			print_think(t_master *master, t_philo *philo);
void			print_sleep(t_master *master, t_philo *philo);
void			print_eat(t_master *master, t_philo *philo);

#endif
