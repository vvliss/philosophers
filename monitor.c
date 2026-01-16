/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wilisson <wilisson@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 19:35:58 by wilisson          #+#    #+#             */
/*   Updated: 2026/01/16 19:24:42 by wilisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *monitor_routine(void *arg)
{
    pthread_t monitor;
    t_philo *philo;
    t_table *table;
    int simulation;
    long long time_now;
    
    table = philo->table;
    philo = (t_philo *)arg;
    simulation = table->simulation_running;
    monitor = philo->monitor_thread;
    while(simulation)
    {
        time_now = 
        if(check_death != 0)
        {
            pthread_mutex_lock(&table->sim_mutex);
            
            printf("%lld %d died\n", )
        }
    }
}

int check_death(t_philo *philo)
{
    long long last_meal;
    t_table *table;

    philo = philo->table;
    last_meal = philo->last_meal_time;
    if(current_time_ms() - last_meal >= table->time_to_die)
        return(1);
    if(philo->eat_count == -1)
        return(1);        
    else
        return(0);
}
