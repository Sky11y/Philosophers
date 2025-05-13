/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiensal <jpiensal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:23:16 by jpiensal          #+#    #+#             */
/*   Updated: 2025/05/13 15:12:48 by jpiensal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"


static void	master_loop(t_master *master, t_philo *philo)
{
	while (!master->is_dead && !master->error && !master->is_finished)
	{
		if (take_first_fork(master, philo) || take_second_fork(master, philo))
			return ;
		if (eat(master, philo) == 0)
		{
		//	master->is_eaten -= 1;
			return ;
		}
		if (master->is_dead || master->error)
			return ;
		print(master, philo->id, e_sleep);
		if (philo->time_to_sleep <= philo->time_to_die)
			ft_usleep(master, philo->time_to_sleep);
		else
		{
			ft_usleep(master, philo->time_to_die);
			return ;
		}
		print(master, philo->id, e_think);
	}
}

static void	start_routine(t_master *master, t_philo *philo)
{
	pthread_t	self_observe;

	philo->eaten = master->begin_program;
	if (master->total_philos == 1)
	{
		print(master, philo->id, e_gotfork);
		ft_usleep(master, philo->time_to_die);
		print(master, philo->id, e_die);
		return ;
	}
	pthread_create(&self_observe, NULL, observe, (void *)philo);
	//master->philos_started++;
	if (philo->id % 2 == 0 || philo->id == master->total_philos)
		print(master, philo->id, e_think);
	master_loop(master, philo);
	//philo->is_eating = true;
	pthread_join(self_observe, NULL);
	while (master->is_finished == false)
		continue ;
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
