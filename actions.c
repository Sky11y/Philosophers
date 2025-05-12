/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiensal <jpiensal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 13:08:11 by jpiensal          #+#    #+#             */
/*   Updated: 2025/05/12 11:13:56 by jpiensal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print(t_master *master, int id, t_action action)
{
	pthread_mutex_lock(&master->print_lock);
	if (master->is_dead || master->error)
	{
		pthread_mutex_unlock(&master->print_lock);
		return ;
	}
	if (action == e_die)
	{
		master->is_dead = true;
		print_dead(master, id);
	}
	else if (action == e_gotfork)
		print_got_fork(master, id);
	else if (action == e_eat)
		print_eat(master, id);
	else if (action == e_sleep)
		print_sleep(master, id);
	else if (action == e_think)
		print_think(master, id);
	else
		philo_error(master, e_undefined_behaviour);
	pthread_mutex_unlock(&master->print_lock);
}

void	release_forks(t_master *master, t_philo *philo, bool has_both_forks)
{
	if (philo->id % 2)
	{
		if (philo->id == master->total_philos)
			pthread_mutex_unlock(&master->forks[0]);
		else
			pthread_mutex_unlock(&master->forks[philo->id]);
	}
	else
		pthread_mutex_unlock(&master->forks[philo->id - 1]);
	if (philo->id % 2 && has_both_forks)
		pthread_mutex_unlock(&master->forks[philo->id - 1]);
	else if (has_both_forks)
	{
		if (philo->id == master->total_philos)
			pthread_mutex_unlock(&master->forks[0]);
		else
			pthread_mutex_unlock(&master->forks[philo->id]);
	}
	philo->eaten = get_current_time(master);
	philo->is_eating = false;
	if (philo->eat_count != -1)
		philo->eat_count--;
}

int	take_first_fork(t_master *master, t_philo *philo)
{
	if (philo->id % 2)
	{
		if (philo->id == master->total_philos)
			pthread_mutex_lock(&master->forks[0]);
		else
			pthread_mutex_lock(&master->forks[philo->id]);
	}
	else
		pthread_mutex_lock(&master->forks[philo->id - 1]);
	print(master, philo->id, e_gotfork);
	if (master->is_dead)
	{
		release_forks(master, philo, false);
		return (1);
	}
	return (0);
}

int	take_second_fork(t_master *master, t_philo *philo)
{
	if (philo->id % 2)
		pthread_mutex_lock(&master->forks[philo->id - 1]);
	else
	{
		if (philo->id == master->total_philos)
			pthread_mutex_lock(&master->forks[0]);
		else
			pthread_mutex_lock(&master->forks[philo->id]);
	}
	print(master, philo->id, e_gotfork);
	philo->eaten = get_current_time(master);
	philo->is_eating = true;
	if (master->is_dead)
	{
		release_forks(master, philo, true);
		return (1);
	}
	return (0);
}
