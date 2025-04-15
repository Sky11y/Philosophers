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
	unsigned int 	timestamp;

	timestamp = get_current_time() - master->begin_program;
	printf("%u ms %d is eating\n", timestamp / 1000, philo->id);
}

void	print_sleep(t_master *master, t_philo *philo)
{
	unsigned int 	timestamp;

	timestamp = get_current_time() - master->begin_program;
	printf("%u ms %d is sleeping\n", timestamp / 1000, philo->id);
}

void	print_think(t_master *master, t_philo *philo)
{
	unsigned int 	timestamp;

	timestamp = get_current_time() - master->begin_program;
	printf("%u ms %d is thinking\n", timestamp / 1000, philo->id);
}

void	print_dead(t_master *master, t_philo *philo)
{
	unsigned int 	timestamp;

	timestamp = get_current_time() - master->begin_program;
	printf("%u ms %d died\n", timestamp / 1000, philo->id);
}

void	print_got_fork(t_master *master, t_philo *philo)
{
	unsigned int 	timestamp;

	timestamp = get_current_time() - master->begin_program;
	printf("%u ms %d has taken a fork\n", timestamp / 1000, philo->id);
}
