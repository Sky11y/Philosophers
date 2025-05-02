/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiensal <jpiensal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:23:16 by jpiensal          #+#    #+#             */
/*   Updated: 2025/05/02 18:12:54 by jpiensal         ###   ########.fr       */
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

static void	*observer(void *arg)
{
	int				i;
	unsigned int	timestamp;
	t_master		*master;

	master = (t_master *)arg;
	i = 0;
	while (master->philos_started < master->total_philos - 1)
		continue ;
	while (!master->is_dead && !master->error && master->is_eaten)
	{
		if (master->philo_arr[i]->eat_count == 0)
		{
			if (++i == master->total_philos)
				i = 0;
			continue ;
		}
		timestamp = get_current_time();
		if (!timestamp)
		{
			philo_error(master, e_gettime);
			break ;
		}
		if (timestamp - master->philo_arr[i]->eaten >= master->time_to_die)
		{
			print(master, i + 1, e_die);
			break ;
		}
		if (++i == master->total_philos)
			i = 0;
	}
	master->is_finished = true;
	return (NULL);
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

static void	*start_thread(void *arg)
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
	if (master->total_philos == 1)
	{
		print(master, philo.id, e_gotfork);
		usleep(master->time_to_die * 1000);
		print(master, philo.id, e_die);
		return (NULL);
	}
	if (philo.id % 2 == 0 || philo.id == master->total_philos)
	{
		print(master, philo.id, e_think);
		usleep(master->time_to_think * 1000);
	}
	master_loop(master, &philo);
	while (master->is_finished == false)
		continue ;
	return (NULL);
}

int	philosophers(t_master *master, int count)
{
	pthread_t	*philo;

	philo = malloc(sizeof(pthread_t) * (master->total_philos + 1));
	if (!philo)
		return (philo_error(master, e_memory));
	while (count < master->total_philos)
	{
		if (pthread_create(&philo[count++], NULL, start_thread, (void *)master))
		{
			free(philo);
			return (philo_error(master, e_create_philo));
		}
	}
	pthread_create(&philo[count++], NULL, observer, (void *)master);
	while (master->philos_initialised < master->total_philos)
		continue ;
	master->begin_program = get_current_time();
	if (!master->begin_program)
		return (philo_error(master, e_gettime));
	while (count--)
	{
		if (pthread_join(philo[count], NULL))
		{
			free(philo);
			return (philo_error(master, e_join));
		}
	}
	free(philo);
	return (0);
}
