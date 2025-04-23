/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiensal <jpiensal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 13:12:10 by jpiensal          #+#    #+#             */
/*   Updated: 2025/04/23 12:29:34 by jpiensal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_eat(t_master *master, t_philo *philo)
{
	unsigned int	timestamp;

	timestamp = get_current_time() - master->begin_program;
	printf("%u %d is eating\n", timestamp, philo->id);
}

void	print_sleep(t_master *master, t_philo *philo)
{
	unsigned int	timestamp;

	timestamp = get_current_time() - master->begin_program;
	printf("%u %d is sleeping\n", timestamp, philo->id);
}

void	print_think(t_master *master, t_philo *philo)
{
	unsigned int	timestamp;

	timestamp = get_current_time() - master->begin_program;
	printf("%u %d is thinking\n", timestamp, philo->id);
}

void	print_dead(t_master *master, t_philo *philo)
{
	unsigned int	timestamp;

	timestamp = get_current_time() - master->begin_program;
	printf("%u %d died\n", timestamp, philo->id);
}

void	print_got_fork(t_master *master, t_philo *philo)
{
	unsigned int	timestamp;

	timestamp = get_current_time() - master->begin_program;
	printf("%u %d has taken a fork\n", timestamp, philo->id);
}
