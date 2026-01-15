/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wilisson <wilisson@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 16:07:57 by wilisson          #+#    #+#             */
/*   Updated: 2026/01/15 20:13:43 by wilisson         ###   ########.fr       */
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
    printf("%lld %d is eating\n", time_now, philo->id);
    pthread_mutex_unlock(&table->print_mutex);
    smart_sleep(table->time_to_eat, table);
}

void    sleep_and_think(t_philo *philo)
{
    
}

void    philo_routine(void *arg)
{
    t_table *table;
    t_philo *philo;
    
    philo = (t_philo *)arg;
    table = philo->table;

    while(table->simulation_running)
    {
        if(philo->id % 2 == 0) //right-left
        {
            pthread_mutex_lock(philo->right_fork);
            pthread_mutex_lock(philo->left_fork);
            //eat time
            //relese forks
            //sleep time
            //think no time
        }
        else if(philo->id % 2 != 0) //left-right
        {
            if()
            {
                pthread_mutex_lock(philo->left_fork);
                pthread_mutex_lock(philo->right_fork);
                
            }
        }
    }    
}
