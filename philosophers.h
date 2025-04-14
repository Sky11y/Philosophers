/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiensal <jpiensal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 10:27:56 by jpiensal          #+#    #+#             */
/*   Updated: 2025/04/14 16:49:35 by jpiensal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
 #define PHILOSOPHERS_H

# include <stdlib.h> //malloc, free
# include <stdio.h> //printf
# include <unistd.h> //write, usleep
# include <sys/time.h> //gettimeofday
# include <pthread.h> //all the thread functions
					  //pthread_create(
					  //pthread_detach(
					  //pthread_join(
					  //pthread_mutex_init(
					  //phtread_mutext_destroy(
					  //phtread_mutex_lock(
					  //pthread_mutex_unlock(
# include <string.h> //memset
# include <stdint.h>
# include <stdbool.h>

typedef enum
{
	e_none,
	e_input,
	e_create_master,
	e_create_philo,
	e_join,
	e_lock,
	e_memory,
	e_gettime,
	e_undefined_action,
} t_errors;

typedef enum
{
	e_die,
	e_eat,
	e_sleep,
	e_think,
} t_action;

typedef struct	s_master
{
	int				total_philos;
	int				philo_ids;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	time_to_think;
	unsigned int	begin_program;
	pthread_mutex_t print_lock;
	pthread_mutex_t	*forks;
	bool			is_dead;
	bool			error;
} t_master;

typedef struct s_philo
{
	int				id;
	unsigned int	wait_forks;
	unsigned int	got_forks;
} t_philo;

unsigned int	philo_atoi(char *nbr);
int				philo_error(t_errors n);
int				philosophers(t_master *master);
unsigned int	exchange_current_time(void);

/*
 * actions.c
 */
void	release_forks(t_master *master, t_philo *philo);
void	die(t_master *master, t_philo *philo);
void	take_forks(t_master *master, t_philo *philo);
/*
 * prints.c
 */
void	print(t_master *master, t_philo *philo, t_action action);



#endif
