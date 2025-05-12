/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiensal <jpiensal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 11:23:07 by jpiensal          #+#    #+#             */
/*   Updated: 2025/05/09 18:08:56 by jpiensal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

unsigned int	philo_atoi(char *nbr)
{
	unsigned int	res;
	size_t			len;

	res = 0;
	len = 0;
	while (nbr[len])
		len++;
	if (len > 10)
		return (0);
	while (*nbr)
	{
		res = res * 10 + (unsigned int)(*nbr - '0');
		nbr++;
	}
	if (res > 3600000)
		return (0);
	return (res);
}

static void	print_input_error(void)
{
	printf("Invalid input. ");
	printf("Give 4[+1 optional] arguments using only positive numbers ");
	printf("between 1 and 3,600,000 (1 ms to 1 h).\n");
	printf("Use 'no_of_philos' 'time_to_die' 'time_to_eat' 'time_to_eat' ");
	printf("'[number_of_times_each_philosopher_must_eat]'\n");
}

int	philo_error(t_master *master, t_errors n)
{
	if (n == e_input || n == e_create_master)
		print_input_error();
	else if (n == e_create_philo)
		printf("Failed to create philosopher\n");
	else if (n == e_memory)
		printf("not enough memory\n");
	else if (n == e_join)
		printf("Failed to join\n");
	else if (n == e_lock)
		printf("Failed to initialize a mutex_lock\n");
	else if (n == e_unlock)
		printf("Failed to destroy a mutex lock\n");
	else if (n == e_gettime)
		printf("Failed to fetch current time\n");
	else
		printf("Undefined behaviour\n");
	master->error = true;
	return (n);
}

unsigned int	get_current_time(t_master *master)
{
	struct timeval	temp;

	if (gettimeofday(&temp, NULL) == -1)
	{
		master->error = true;
		return (0);
	}
	return ((unsigned int)(temp.tv_sec * 1000 + temp.tv_usec / 1000));
}

int	ft_usleep(t_master *master, unsigned int ms)
{
	unsigned int	start;

	start = get_current_time(master);
	while ((get_current_time(master) - start) < ms)
		usleep(500);
	return (0);
}
