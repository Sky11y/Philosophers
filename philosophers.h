/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiensal <jpiensal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 10:27:56 by jpiensal          #+#    #+#             */
/*   Updated: 2025/04/11 17:37:13 by jpiensal         ###   ########.fr       */
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
} t_errors;

typedef struct	s_master
{
	uint32_t		total_philos;
	uint32_t		philo_ids;
	uint32_t		time_to_die;
	uint32_t		time_to_eat;
	uint32_t		time_to_sleep;
	pthread_mutex_t eat_lock;
	pthread_mutex_t	sleep_lock;
	pthread_mutex_t	die_lock;
	pthread_mutex_t	*forks;
	bool			is_dead;
} t_master;

typedef struct s_philo
{
	uint32_t	id;
	int32_t		time_to_die;
	uint32_t	time_to_eat;
	uint32_t	time_to_sleep;
} t_philo;

int		philo_atoi(char *nbr);
int		philo_error(t_errors n);
void	*create_philo(void *arg);

/*
 * actions.c
 */
void	do_actions(t_master *master, t_philo *philo);
/*
 * prints.c
 */
void	print_eat(t_master *master, t_philo *philo);
void	print_sleep(t_master *master, t_philo *philo);
void	print_dead(t_master *master, t_philo *philo);


#endif
