/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiensal <jpiensal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 11:23:07 by jpiensal          #+#    #+#             */
/*   Updated: 2025/04/11 17:23:54 by jpiensal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	philo_atoi(char *nbr)
{
	int		res;
	size_t	len;

	res = 0;
	len = 0;
	while (nbr[len])
		len++;
	if (len > 10)
		return (0);
	while (*nbr)
	{
		res = res * 10 + (int)(*nbr - '0');
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
