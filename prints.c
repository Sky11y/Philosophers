/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prints.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiensal <jpiensal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 13:12:10 by jpiensal          #+#    #+#             */
/*   Updated: 2025/05/02 17:05:44 by jpiensal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print_eat(t_master *master, int id)
{
	unsigned int	timestamp;

	timestamp = get_current_time() - master->begin_program;
	printf("%u %d is eating\n", timestamp, id);
}

void	print_sleep(t_master *master, int id)
{
	unsigned int	timestamp;

	timestamp = get_current_time() - master->begin_program;
	printf("%u %d is sleeping\n", timestamp, id);
}

void	print_think(t_master *master, int id)
{
	unsigned int	timestamp;

	timestamp = get_current_time() - master->begin_program;
	printf("%u %d is thinking\n", timestamp, id);
}

void	print_dead(t_master *master, int id)
{
	unsigned int	timestamp;

	timestamp = get_current_time() - master->begin_program;
	printf("%u %d died\n", timestamp, id);
}

void	print_got_fork(t_master *master, int id)
{
	unsigned int	timestamp;

	timestamp = get_current_time() - master->begin_program;
	printf("%u %d has taken a fork\n", timestamp, id);
}
