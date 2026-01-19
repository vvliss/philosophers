/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wilisson <wilisson@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 19:35:58 by wilisson          #+#    #+#             */
/*   Updated: 2026/01/19 13:40:51 by wilisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_philo *philo)
{
	long long	last_meal;
	int			dead;

	pthread_mutex_lock(&philo->meal_mutex);
	dead = 0;
	last_meal = philo->last_meal_time;
	if (current_time_ms() - last_meal >= philo->table->time_to_die)
		dead = 1;
	pthread_mutex_unlock(&philo->meal_mutex);
	return (dead);
}

static int	all_philos_full(t_table *table)
{
	int	i;

	if (table->must_eat_count <= 0)
		return (0);
	i = 0;
	while (i < table->num_philos)
	{
		pthread_mutex_lock(&table->philos[i].meal_mutex);
		if (table->philos[i].eat_count < table->must_eat_count)
		{
			pthread_mutex_unlock(&table->philos[i].meal_mutex);
			return (0);
		}
		pthread_mutex_unlock(&table->philos[i].meal_mutex);
		i++;
	}
	return (1);
}

static int	check_philos(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philos)
	{
		if (check_death(&table->philos[i]))
		{
			pthread_mutex_lock(&table->sim_mutex);
			table->simulation_running = false;
			pthread_mutex_unlock(&table->sim_mutex);
			pthread_mutex_lock(&table->print_mutex);
			printf("%lld %d died\n", current_time_ms()
				- table->start_time, table->philos[i].id);
			pthread_mutex_unlock(&table->print_mutex);
			return (1);
		}
		pthread_mutex_lock(&table->sim_mutex);
		if (!table->simulation_running)
			return (pthread_mutex_unlock(&table->sim_mutex), 1);
		pthread_mutex_unlock(&table->sim_mutex);
		i++;
	}
	return (0);
}

static int	check_all_full(t_table *table)
{
	if (!all_philos_full(table))
		return (0);
	pthread_mutex_lock(&table->sim_mutex);
	table->simulation_running = false;
	pthread_mutex_unlock(&table->sim_mutex);
	return (1);
}

void	*monitor_routine(void *arg)
{
	t_table	*table;

	table = (t_table *)arg;
	if(table->num_philos > 1)
		usleep(10000);
	while (1)
	{
		if (check_philos(table))
			return (NULL);
		if (check_all_full(table))
			return (NULL);
		usleep(1000);
	}
	return (NULL);
}
