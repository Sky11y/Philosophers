/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpiensal <jpiensal@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/18 13:08:11 by jpiensal          #+#    #+#             */
/*   Updated: 2025/04/23 15:41:34 by jpiensal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	print(t_master *master, t_philo *philo, t_action action)
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
		print_dead(master, philo);
	}
	else if (action == e_gotfork)
		print_got_fork(master, philo);
	else if (action == e_eat)
		print_eat(master, philo);
	else if (action == e_sleep)
		print_sleep(master, philo);
	else if (action == e_think)
		print_think(master, philo);
	else
		philo_error(master, e_undefined_behaviour);
	pthread_mutex_unlock(&master->print_lock);
}

void	release_forks(t_master *master, t_philo *philo, bool has_left_fork)
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
	if (philo->id % 2 && has_left_fork)
		pthread_mutex_unlock(&master->forks[philo->id - 1]);
	else if (has_left_fork)
	{
		if (philo->id == master->total_philos)
			pthread_mutex_unlock(&master->forks[0]);
		else
			pthread_mutex_unlock(&master->forks[philo->id]);
	}
	philo->is_eating = false;
	philo->eaten = get_current_time();
	if (!philo->eaten)
		philo_error(master, e_gettime);
	if (philo->eat_count != -1)
		philo->eat_count--;
}

void	die(t_master *master, t_philo *philo)
{
	static bool	first_dead;

	if (first_dead)
		return ;
	first_dead = true;
	print(master, philo, e_die);
}

int	take_right_fork(t_master *master, t_philo *philo)
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
	print(master, philo, e_gotfork);
	if (check_death(master))
	{
		release_forks(master, philo, false);
		return (1);
	}
	return (0);
}

int	take_left_fork(t_master *master, t_philo *philo)
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
	print(master, philo, e_gotfork);
	if (check_death(master))
	{
		release_forks(master, philo, true);
		return (1);
	}
	philo->is_eating = true;
	return (0);
}
