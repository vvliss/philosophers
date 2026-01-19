/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wilisson <wilisson@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 16:07:57 by wilisson          #+#    #+#             */
/*   Updated: 2026/01/19 13:39:33 by wilisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philo *philo)
{
	t_table		*table;
	long long	time_now;

	table = philo->table;
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal_time = current_time_ms();
	philo->eat_count++;
	pthread_mutex_unlock(&philo->meal_mutex);
	pthread_mutex_lock(&table->print_mutex);
	time_now = current_time_ms() - table->start_time;
	pthread_mutex_lock(&table->sim_mutex);
	if (table->simulation_running)
		printf("%lld %d is eating\n", time_now, philo->id);
	pthread_mutex_unlock(&table->sim_mutex);
	pthread_mutex_unlock(&table->print_mutex);
	sleep_check(table->time_to_eat, table);
}

void	sleep_and_think(t_philo *philo)
{
	long long	time_now;

	grab_mutexes(&philo->table->print_mutex, &philo->table->sim_mutex);
	time_now = current_time_ms() - philo->table->start_time;
	if (philo->table->simulation_running)
		printf("%lld %d is sleeping\n", time_now, philo->id);
	unlock_mutexes(&philo->table->sim_mutex, &philo->table->print_mutex);
	sleep_check(philo->table->time_to_sleep, philo->table);
	grab_mutexes(&philo->table->print_mutex, &philo->table->sim_mutex);
	time_now = current_time_ms() - philo->table->start_time;
	if (philo->table->simulation_running)
		printf("%lld %d is thinking\n", time_now, philo->id);
	unlock_mutexes(&philo->table->sim_mutex, &philo->table->print_mutex);
	pthread_mutex_lock(&philo->table->sim_mutex);
	if (philo->table->num_philos % 2)
	{
		pthread_mutex_unlock(&philo->table->sim_mutex);
		usleep(10000);
	}
	else
		pthread_mutex_unlock(&philo->table->sim_mutex);
}

static int	handle_single_philo(t_philo *philo, t_table *table)
{
	if (table->num_philos != 1)
		return (0);
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(&table->print_mutex);
	printf("%lld %d has taken left fork\n",
		current_time_ms() - table->start_time, philo->id);
	pthread_mutex_unlock(&table->print_mutex);
	pthread_mutex_unlock(philo->left_fork);
	return (1);
}

void	*odd_philo_routine(void *arg)
{
	t_table	*table;
	t_philo	*philo;
	int		simulation;

	philo = (t_philo *)arg;
	table = philo->table;
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal_time = current_time_ms();
	pthread_mutex_unlock(&philo->meal_mutex);
	if (handle_single_philo(philo, table))
		return (NULL);
	while (1)
	{
		pthread_mutex_lock(&table->sim_mutex);
		simulation = table->simulation_running;
		pthread_mutex_unlock(&table->sim_mutex);
		if (!simulation)
			break ;
		grab_left_first(philo, table);
		sleep_and_think(philo);
	}
	return (NULL);
}

void	*non_odd_philo_routine(void *arg)
{
	t_table	*table;
	t_philo	*philo;
	int		simulation;

	philo = (t_philo *)arg;
	table = philo->table;
	usleep(1000);
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal_time = current_time_ms();
	pthread_mutex_unlock(&philo->meal_mutex);
	while (1)
	{
		pthread_mutex_lock(&table->sim_mutex);
		simulation = table->simulation_running;
		pthread_mutex_unlock(&table->sim_mutex);
		if (!simulation)
			break ;
		grab_right_first(philo, table);
		sleep_and_think(philo);
	}
	return (NULL);
}
