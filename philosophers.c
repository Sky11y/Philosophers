/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiensal <jpiensal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:23:16 by jpiensal          #+#    #+#             */
/*   Updated: 2025/04/11 17:45:44 by jpiensal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	init_philo(t_philo *philo, t_master *master)
{
	philo->id = master->philo_ids++;
	philo->time_to_die = master->time_to_die;
	philo->time_to_eat = master->time_to_eat;
	philo->time_to_sleep = master->time_to_sleep;
	philo->is_dead = false;
	return (0);
}

void	*create_philo(void *arg)
{
	t_master	*master;
	t_philo		philo;

	master = (t_master *)arg;
	if (init_philo(&philo, master))
	{
		philo_error(e_create_philo);
		return (NULL);
	}
	while (master->is_dead)
		do_actions(master, &philo);
	printf("philo successfully created\n");
	printf("philo values: %d %d %d %d\n", philo.id, philo.time_to_die, philo.time_to_eat, philo.time_to_sleep);
	return (NULL);
}
