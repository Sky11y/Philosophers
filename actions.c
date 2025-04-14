/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiensal <jpiensal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:23:16 by jpiensal          #+#    #+#             */
/*   Updated: 2025/04/11 17:45:44 by jpiensal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	release_forks(t_master *master, t_philo *philo)
{
	if (philo->id % 2)
	{
		if (philo->id == master->total_philos)
			pthread_mutex_unlock(&master->forks[0]);
		else
			pthread_mutex_unlock(&master->forks[philo->id]);
	}
	else
		pthread_mutex_unlock(&master->forks[philo->id - 1]);
	if (philo->id % 2)
		pthread_mutex_unlock(&master->forks[philo->id - 1]);
	else
	{
		if (philo->id == master->total_philos)
			pthread_mutex_unlock(&master->forks[0]);
		else
			pthread_mutex_unlock(&master->forks[philo->id]);
	}
	philo->wait_forks = exchange_current_time();
	if (philo->wait_forks)
		philo_error(e_gettime);
}

void	die(t_master *master, t_philo *philo)
{
	static bool first_dead;

	if (first_dead)
		return ;
	first_dead = true;
	print(master, philo, e_die);
}

void	take_forks(t_master *master, t_philo *philo)
{
	if (philo->id % 2)
	{
		if (philo->id == master->total_philos)
			pthread_mutex_lock(&master->forks[0]);
		else
			pthread_mutex_lock(&master->forks[philo->id]);
	}
	else
		pthread_mutex_lock(&master->forks[philo->id - 1]);
	if (philo->id % 2)
		pthread_mutex_lock(&master->forks[philo->id - 1]);
	else
	{
		if (philo->id == master->total_philos)
			pthread_mutex_lock(&master->forks[0]);
		else
			pthread_mutex_lock(&master->forks[philo->id]);
	}
	philo->got_forks = exchange_current_time();
	if (philo->got_forks)
		philo_error(e_gettime);
}

