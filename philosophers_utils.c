/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiensal <jpiensal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 11:23:07 by jpiensal          #+#    #+#             */
/*   Updated: 2025/04/14 16:49:12 by jpiensal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

unsigned int	philo_atoi(char *nbr)
{
	unsigned int		res;
	size_t	len;

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
	return (res);
}

int	philo_error(t_errors n)
{
	if (n == e_input)
	{
		printf("Invalid input. Give 4 arguments using only positive numbers.\n");
		printf("Use 'no_of_philos' 'time_to_die' 'time_to_eat' 'time_to_eat'\n");
	}
	else if (n == e_join)
		printf("Failed to join");
	else if (n == e_create_master)
		printf("Failed to create master");
	else if (n == e_create_philo)
		printf("Failed to create philosopher");
	else if (n == e_memory)
		printf("not enough memory");
	return (n);
}

unsigned int	exchange_current_time(void)
{
	unsigned int	us;
	struct timeval	temp;

	if (gettimeofday(&temp, NULL) == -1)
		return (0);
	us = (unsigned int)(temp.tv_sec * 1000000);
	us += (unsigned int)(temp.tv_usec );
	return (us);
}
