/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiensal <jpiensal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 11:23:07 by jpiensal          #+#    #+#             */
/*   Updated: 2025/05/26 12:57:56 by jpiensal         ###   ########.fr       */
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

int	philo_error(t_master *master, t_errors n)
{
	if (n == e_input || n == e_create_master)
		write(2, INPUT, 14);
	else if (n == e_create_philo)
		write(2, CREATE_PHILO, 30);
	else if (n == e_create_observer)
		write(2, CREATE_OBS, 26);
	else if (n == e_memory)
		write(2, MEMORY, 18);
	else if (n == e_join)
		write(2, JOIN, 23);
	else if (n == e_lock)
		write(2, LOCK, 32);
	else if (n == e_unlock)
		write(2, UNLOCK, 29);
	else if (n == e_gettime)
		write(2, TIME, 29);
	else
		write(2, UB, 20);
	master->error = true;
	return (n);
}

unsigned int	get_current_time(t_master *master)
{
	struct timeval	temp;

	if (gettimeofday(&temp, NULL) == -1)
	{
		philo_error(master, e_gettime);
		return (0);
	}
	return ((unsigned int)(temp.tv_sec * 1000 + temp.tv_usec / 1000));
}

int	ft_usleep(t_master *master, unsigned int ms)
{
	unsigned int	start;

	start = get_current_time(master);
	while ((get_current_time(master) - start) < ms && !master->is_dead)
		usleep(500);
	return (0);
}
