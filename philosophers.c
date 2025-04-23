/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiensal <jpiensal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:23:16 by jpiensal          #+#    #+#             */
/*   Updated: 2025/04/23 16:19:23 by jpiensal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	init_philo(t_philo *philo, t_master *master)
{
	philo->id = master->philo_ids++;
	philo->eat_count = master->times_to_eat;
	philo->is_eating = false;
	philo->eaten = get_current_time();
	if (!philo->eaten)
		return (philo_error(master, e_gettime));
	master->philo_arr[philo->id - 1] = philo;
	return (0);
}

static void	master_loop(t_master *master, t_philo *philo)
{
	while (!master->is_dead && !master->error)
	{
		if (take_right_fork(master, philo) || take_left_fork(master, philo))
			break ;
		print(master, philo, e_eat);
		do_action(master, e_eat);
		//usleep(master->time_to_eat * 1000);
		release_forks(master, philo, true);
		if (check_death(master) || !philo->eat_count)
			return ;
		print(master, philo, e_sleep);
		do_action(master, e_sleep);
		/*if (master->time_to_sleep <= master->time_to_die)
			usleep(master->time_to_sleep * 1000);
		else
		{
			usleep(master->time_to_die * 1000);
			break ;
		}*/
		if (check_death(master))
			break ;
		print(master, philo, e_think);
		do_action(master, e_think);
		//usleep(master->time_to_think * 1000);
	}
	//die(master, philo);
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
	while (master->philo_ids < master->total_philos)
		continue ;
	master->begin_program = get_current_time();
	if (!master->begin_program)
		return (NULL);
	if (master->total_philos == 1)
	{
		print(master, &philo, e_gotfork);
		usleep(master->time_to_die * 1000);
		die(master, &philo);
		return (NULL);
	}
	if (philo.id % 2 == 0 || philo.id == master->total_philos)
	{
		print(master, &philo, e_think);
		usleep(master->time_to_think * 1000);
	}
	master_loop(master, &philo);
	return (NULL);
}

int	philosophers(t_master *master, int count)
{
	pthread_t	*philo;

	philo = malloc(sizeof(pthread_t) * master->total_philos);
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

void	do_action(t_master *master, t_action action)
{
	unsigned int action_time;
	unsigned int temp;

	action_time = 0;
	if (action == e_sleep)
		action_time = master->time_to_sleep;
	else if (action == e_think)
		action_time = master->time_to_think;
	else if (action == e_eat)
	{
		if (master->time_to_die < master->time_to_eat)
			action_time = master->time_to_die;
		else
		{
			action_time = master->time_to_die - master->time_to_eat;
			temp = 0;
			while (temp + action_time < master->time_to_eat)
			{
				usleep(action_time * 1000);
				temp += action_time;
				if (check_death(master))
					return ;
			}
			action_time = master->time_to_eat - temp;
		}
	}
	usleep(action_time * 1000);
}
