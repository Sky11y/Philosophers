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

typedef enum
{
	e_none,
	e_input,
	e_create_master,
	e_create_philo,
	e_join,
	e_memory,
} t_errors;

typedef struct	s_master
{
	uint32_t	philos;
	uint32_t	forks;
	uint32_t	time_to_die;
	uint32_t	time_to_eat;
	uint32_t	time_to_sleep;
} t_master;

typedef struct s_philo
{
	int			philo_id;
	uint32_t	time_to_die;
	uint32_t	time_to_eat;
	uint32_t	time_to_sleep;
} t_philo;

int		philo_atoi(char *nbr);
int		philo_error(t_errors n);
void	*create_philo(void *arg);

#endif
