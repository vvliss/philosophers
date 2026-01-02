/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wilisson <wilisson@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 14:35:42 by wilisson          #+#    #+#             */
/*   Updated: 2026/01/02 17:07:11 by wilisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int init_forks(t_table *table)
{
    int i;

    i = 0;
    table->forks = malloc(sizeof(pthread_mutex_t) * table->num_philos);
    if(!table->forks)
        return(EXIT_FAILURE);
    while(i < table->num_philos)
    {
        if(pthread_mutex_init(&table->forks[i], NULL) != 0) 
            return(EXIT_FAILURE);
        i++;
    }
    return(EXIT_SUCCESS);
}

int init_philo(t_table *table)
{
    t_philo *philo;
    int i;

    i = 0;
    table->philos = malloc(sizeof(t_philo) * table->num_philos);
    if(!table->philos)
        return(EXIT_FAILURE);
    while(i < table->num_philos)
    {
        philo = &table->philos[i];
        philo->id = i + 1;
        philo->eat_count = 0;
        philo->left_fork = &table->forks[i];
        philo->right_fork = &table->forks[(i + 1) % table->num_philos];
        
        i++;
    }
    return(EXIT_SUCCESS);
}

void init_table(t_table *table)
{
    
}
