/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiensal <jpiensal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:23:16 by jpiensal          #+#    #+#             */
/*   Updated: 2025/05/05 15:31:37 by jpiensal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	init_philo(t_philo *philo, t_master *master)
{
	static int	i = 1;

	pthread_mutex_lock(&master->init_lock);
	philo->id = i++;
	philo->eat_count = master->times_to_eat;
	philo->eaten = 0;
	master->philo_arr[philo->id - 1] = philo;
	pthread_mutex_unlock(&master->init_lock);
	return (0);
}

static void	master_loop(t_master *master, t_philo *philo)
{
	master->philos_started++;
	while (!master->is_dead && !master->error && !master->is_finished)
	{
		if (take_first_fork(master, philo) || take_second_fork(master, philo))
			break ;
		print(master, philo->id, e_eat);
		usleep(master->time_to_eat * 1000);
		release_forks(master, philo, true);
		if (!philo->eat_count || master->is_dead)
		{
			if (!philo->eat_count)
				master->is_eaten -= 1;
			return ;
		}
		print(master, philo->id, e_sleep);
		if (master->time_to_sleep <= master->time_to_die)
			usleep(master->time_to_sleep * 1000);
		else
		{
			usleep(master->time_to_die * 1000);
			break ;
		}
		print(master, philo->id, e_think);
		usleep(master->time_to_think * 1000);
	}
}

static void	start_routine(t_master *master, t_philo *philo)
{
	if (master->total_philos == 1)
	{
		print(master, philo->id, e_gotfork);
		usleep(master->time_to_die * 1000);
		print(master, philo->id, e_die);
		return ;
	}
	if (philo->id % 2 == 0 || philo->id == master->total_philos)
	{
		print(master, philo->id, e_think);
		usleep(master->time_to_think * 1000);
	}
	master_loop(master, philo);
}

void	*start_thread(void *arg)
{
	t_master	*master;
	t_philo		philo;

	master = (t_master *)arg;
	if (init_philo(&philo, master))
	{
		philo_error(master, e_create_philo);
		return (NULL);
	}
	master->philos_initialised++;
	while (master->begin_program == 0)
		continue ;
	philo.eaten = master->begin_program;
	start_routine(master, &philo);
	while (master->is_finished == false)
		continue ;
	return (NULL);
}
