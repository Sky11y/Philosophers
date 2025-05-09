/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiensal <jpiensal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:04:04 by jpiensal          #+#    #+#             */
/*   Updated: 2025/05/05 14:57:23 by jpiensal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	create_threads(t_master *master, pthread_t *philo)
{
	int	count;

	count = 0;
	while (count < master->total_philos)
	{
		if (pthread_create(&philo[count++], NULL, start_thread, (void *)master))
		{
			free(philo);
			return (philo_error(master, e_create_philo));
		}
	}
	if (pthread_create(&philo[count], NULL, observer, (void *)master))
	{
		free(philo);
		return (philo_error(master, e_create_philo));
	}
	return (0);
}

int	join_threads(t_master *master, pthread_t *philo)
{
	int	count;

	count = 0;
	while (count < master->total_philos + 1)
	{
		if (pthread_join(philo[count++], NULL))
		{
			free(philo);
			return (philo_error(master, e_join));
		}
	}
	return (0);
}
