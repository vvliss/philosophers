/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wilisson <wilisson@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 16:07:57 by wilisson          #+#    #+#             */
/*   Updated: 2026/01/18 19:58:23 by wilisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"



void    eat(t_philo *philo)
{
    t_table *table;
    long long time_now;
    
    table = philo->table;
    pthread_mutex_lock(&philo->meal_mutex);
    philo->last_meal_time = current_time_ms();
    philo->eat_count++;
    pthread_mutex_unlock(&philo->meal_mutex);
    
    pthread_mutex_lock(&table->print_mutex);
    time_now = current_time_ms() - table->start_time;
    pthread_mutex_lock(&table->sim_mutex);
    if(table->simulation_running)
        printf("%lld %d is eating\n", time_now, philo->id);
    pthread_mutex_unlock(&table->sim_mutex);
    pthread_mutex_unlock(&table->print_mutex);
    sleep_check(table->time_to_eat, table);
}

void    sleep_and_think(t_philo *philo)
{
    t_table *table;
    long long time_now;

    table = philo->table;
    pthread_mutex_lock(&table->print_mutex);
    time_now = current_time_ms() - table->start_time;
     pthread_mutex_lock(&table->sim_mutex);
    if(table->simulation_running)
        printf("%lld %d is sleeping\n", time_now, philo->id);
    pthread_mutex_unlock(&table->sim_mutex);
    pthread_mutex_unlock(&table->print_mutex);
    sleep_check(table->time_to_sleep, table);
    pthread_mutex_lock(&table->print_mutex);
    time_now = current_time_ms() - table->start_time;
    pthread_mutex_lock(&table->sim_mutex);
    if(table->simulation_running)
        printf("%lld %d is thinking\n", time_now, philo->id);
    pthread_mutex_unlock(&table->sim_mutex);
    pthread_mutex_unlock(&table->print_mutex);
    pthread_mutex_lock(&table->sim_mutex);
    if (table->num_philos % 2)
    {
        pthread_mutex_unlock(&table->sim_mutex);
        usleep(10000);
    }
    else
        pthread_mutex_unlock(&table->sim_mutex);
}

void    *odd_philo_routine(void *arg)
{
    t_table *table;
    t_philo *philo;
    int simulation;
    
    philo = (t_philo *)arg;
    table = philo->table;
    pthread_mutex_lock(&philo->meal_mutex);
    philo->last_meal_time = current_time_ms();
    pthread_mutex_unlock(&philo->meal_mutex);
    if(table->num_philos == 1)
    {
        pthread_mutex_lock(philo->left_fork);
        printf("%lld %d has taken left fork\n", current_time_ms() - table->start_time, philo->id);
        pthread_mutex_unlock(philo->left_fork);
        return NULL;
    }
    while(1)
    {
        pthread_mutex_lock(&table->sim_mutex);
        simulation = table->simulation_running;
        pthread_mutex_unlock(&table->sim_mutex);
        if(!simulation)
            break;
        pthread_mutex_lock(philo->left_fork);
        printf("%lld %d has taken left fork\n", current_time_ms() - table->start_time, philo->id);
        pthread_mutex_lock(philo->right_fork);
        printf("%lld %d has taken right fork\n", current_time_ms() - table->start_time, philo->id);
        eat(philo);
        pthread_mutex_unlock(philo->left_fork);
        pthread_mutex_unlock(philo->right_fork);
        sleep_and_think(philo);
    }
    return NULL;
}

void    *non_odd_philo_routine(void *arg)
{
    t_table *table;
    t_philo *philo;
    int simulation;

    philo = (t_philo *)arg;
    table = philo->table;
    usleep(1000);
    pthread_mutex_lock(&philo->meal_mutex);
    philo->last_meal_time = current_time_ms();
    pthread_mutex_unlock(&philo->meal_mutex);
    while(1)
    {
        pthread_mutex_lock(&table->sim_mutex);
        simulation = table->simulation_running;
        pthread_mutex_unlock(&table->sim_mutex);
        if (!simulation)
            break;
        pthread_mutex_lock(philo->right_fork);
        printf("%lld %d has taken right fork\n", current_time_ms() - table->start_time, philo->id);
        pthread_mutex_lock(philo->left_fork);
        printf("%lld %d has taken left fork\n", current_time_ms() - table->start_time, philo->id);
        eat(philo);
        pthread_mutex_unlock(philo->right_fork);
        pthread_mutex_unlock(philo->left_fork);
        sleep_and_think(philo);
    }
    return NULL;
}
