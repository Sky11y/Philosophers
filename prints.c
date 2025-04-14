/*                                                    +:+ +:+         +:+     */
/*   By: jpiensal <jpiensal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 10:27:43 by jpiensal          #+#    #+#             */
/*   Updated: 2025/04/11 17:37:27 by jpiensal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	print_eat(t_master *master, t_philo *philo)
{
	unsigned int 	timestamp;

	timestamp = exchange_current_time() - master->begin_program;
	printf("%u ms %d is eating\n", timestamp / 1000, philo->id);
}

static void	print_sleep(t_master *master, t_philo *philo)
{
	unsigned int 	timestamp;

	timestamp = exchange_current_time() - master->begin_program;
	printf("%u ms %d is sleeping\n", timestamp / 1000, philo->id);
}

static void	print_think(t_master *master, t_philo *philo)
{
	unsigned int 	timestamp;

	timestamp = exchange_current_time() - master->begin_program;
	printf("%u ms %d is thinking\n", timestamp / 1000, philo->id);
}

static void	print_dead(t_master *master, t_philo *philo)
{
	unsigned int 	timestamp;

	timestamp = exchange_current_time() - master->begin_program;
	printf("%u ms %d died\n", timestamp / 1000, philo->id);
}

void	print(t_master *master, t_philo *philo, t_action action)
{
	pthread_mutex_lock(&master->print_lock);
	if (master->is_dead || master->error)
		return ;
	if (action == e_die)
	{
		master->is_dead = true;
		print_dead(master, philo);
	}
	else if (action == e_eat)
		print_eat(master, philo);
	else if (action == e_sleep)
		print_sleep(master, philo);
	else if (action == e_think)
		print_think(master, philo);
	else
		philo_error(e_undefined_action);
	pthread_mutex_unlock(&master->print_lock);
}
