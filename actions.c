/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiensal <jpiensal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:23:16 by jpiensal          #+#    #+#             */
/*   Updated: 2025/04/11 17:45:44 by jpiensal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	eat(t_master *master, t_philo *philo)
{
	static bool	first_dead;

	if (philo->time_to_die <= 0 || master->is_dead)
	{
		master->is_dead = true;
		if (!first_dead)
		{
			first_dead = true;
			print_dead(master, philo);
		}
		return ;
	}
	print_eat(master, philo);
	while (philo->time_to_eat)
		philo->time_to_eat--;
	philo->time_to_die = master->time_to_die;
}

static void	take_forks_and_eat(t_master *master, t_philo *philo)
{
	if (philo->id % 2)
	{
		if (philo->id == master->total_philos)
			pthread_mutex_lock(master->forks[0]);
		else
			pthread_mutex_lock(master->forks[philo->id]);
	}
	else
		pthread_mutex_lock(master->forks[philo->id - 1]);
	if (philo->id % 2)
		pthread_mutex_lock(master->forks[philo->id - 1]);
	else
	{
		if (philo->id == master->total_philos)
			pthread_mutex_lock(master->forks[0]);
		else
			pthread_mutex_lock(master->forks[philo->id]);
	}
	eat(master, philo);
}

static void	sleep(t_master *master, t_philo *philo)
{
	print_sleep(philo);
	while (philo->time_to_sleep)
		philo->time_to_sleep--;
	philo->time_to_sleep = master->time_to_sleep;
}

void	do_actions(t_master *master, t_philo *philo)
{
	take_forks_and_eat(master, &philo);
	sleep(master, &philo);
	print_think(master, &philo);
}

