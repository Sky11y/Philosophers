/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiensal <jpiensal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:04:04 by jpiensal          #+#    #+#             */
/*   Updated: 2025/05/13 15:01:42 by jpiensal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	create_threads(t_master *master)
{
	int			count;
	/*pthread_t	observe_thread;

	if (pthread_create(&observe_thread, NULL, observer, (void *)master))
		return (philo_error(master, e_create_philo));
	*/
	count = 0;
	while (count < master->total_philos)
	{
		if (pthread_create(&master->philo_arr[count].thread, NULL,
					start_thread, (void *)&master->philo_arr[count]))
			return (philo_error(master, e_create_philo));
		count++;
	}
	master->begin_program = get_current_time(master);
	while (count--)
	{
		if (pthread_join(master->philo_arr[count].thread, NULL))
			return (philo_error(master, e_join));
	}
	//if (pthread_join(observe_thread, NULL))
	//	return (philo_error(master, e_join));
	return (0);
}
