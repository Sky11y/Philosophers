/*                                                    +:+ +:+         +:+     */
/*   By: jpiensal <jpiensal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 10:27:43 by jpiensal          #+#    #+#             */
/*   Updated: 2025/04/11 17:37:27 by jpiensal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_eat(t_master *master, t_philo *philo)
{
	pthread_mutex_lock(master->eat_lock);
	printf("timestamp ms %d is eating\n", philo->id);
	pthread_mutex_unlock(master->eat_lock);
}

void	print_sleep(t_master *master, t_philo *philo)
{
	pthread_mutex_lock(master->sleep_lock);
	printf("timestamp ms %d is sleeping\n", philo->id);
	pthread_mutex_unlock(master->sleep_lock);

}

void	print_think(t_master *master, t_philo *philo)
{
	pthread_mutex_lock(master->think_lock);
	printf("timestamp ms %d is thinking\n", philo->id);
	pthread_mutex_unlock(master->think_lock);
}

void	print_dead(t_master *master, t_philo *philo)
{
	printf("timestamp ms %d\n died" philo->id);
}
