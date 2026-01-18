/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutexes.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wilisson <wilisson@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/18 23:42:23 by wilisson          #+#    #+#             */
/*   Updated: 2026/01/18 23:45:06 by wilisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	grab_mutexes(pthread_mutex_t *m_one, pthread_mutex_t *m_two)
{
	pthread_mutex_lock(m_one);
	pthread_mutex_lock(m_two);
}

void	unlock_mutexes(pthread_mutex_t *m_one, pthread_mutex_t *m_two)
{
	pthread_mutex_unlock(m_one);
	pthread_mutex_unlock(m_two);
}

void	grab_left_first(t_philo *philo, t_table *table)
{
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(&table->sim_mutex);
	if (table->simulation_running)
		printf("%lld %d has taken left fork\n", current_time_ms()
			- table->start_time, philo->id);
	pthread_mutex_unlock(&table->sim_mutex);
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(&table->sim_mutex);
	if (table->simulation_running)
		printf("%lld %d has taken right fork\n", current_time_ms()
			- table->start_time, philo->id);
	pthread_mutex_unlock(&table->sim_mutex);
	eat(philo);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	grab_right_first(t_philo *philo, t_table *table)
{
	pthread_mutex_lock(philo->right_fork);
	pthread_mutex_lock(&table->sim_mutex);
	if (table->simulation_running)
		printf("%lld %d has taken right fork\n", current_time_ms()
			- table->start_time, philo->id);
	pthread_mutex_unlock(&table->sim_mutex);
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(&table->sim_mutex);
	if (table->simulation_running)
		printf("%lld %d has taken left fork\n", current_time_ms()
			- table->start_time, philo->id);
	pthread_mutex_unlock(&table->sim_mutex);
	eat(philo);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}
