/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiensal <jpiensal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:23:16 by jpiensal          #+#    #+#             */
/*   Updated: 2025/05/14 11:25:15 by jpiensal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	master_loop(t_master *master, t_philo *philo)
{
	while (!master->is_dead && !master->error)
	{
		if (take_first_fork(master, philo) || take_second_fork(master, philo))
			return ;
		if (eat(master, philo) == 0)
		{
			master->is_eaten -= 1;
			return ;
		}
		if (master->is_dead || master->error)
			return ;
		print(master, philo->id, e_sleep);
		if (master->time_to_sleep <= master->time_to_die)
			ft_usleep(master, master->time_to_sleep);
		else
		{
			ft_usleep(master, master->time_to_die);
			return ;
		}
		print(master, philo->id, e_think);
		ft_usleep(master, master->time_to_think);
	}
}

static void	start_routine(t_master *master, t_philo *philo)
{
	philo->eaten = master->begin_program;
	if (master->total_philos == 1)
	{
		print(master, philo->id, e_gotfork);
		ft_usleep(master, master->time_to_die);
		print(master, philo->id, e_die);
		return ;
	}
	master->philos_started++;
	if (philo->id % 2 == 0 || philo->id == master->total_philos)
	{
		print(master, philo->id, e_think);
		ft_usleep(master, master->time_to_think);
	}
	master_loop(master, philo);
	philo->is_eating = true;
}

void	*start_thread(void *arg)
{
	t_philo				*philo;

	philo = (t_philo *)arg;
	while (philo->data->begin_program == 0)
		continue ;
	start_routine(philo->data, philo);
	return (NULL);
}
