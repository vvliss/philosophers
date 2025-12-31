/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wilisson <wilisson@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 14:35:42 by wilisson          #+#    #+#             */
/*   Updated: 2025/12/31 15:15:46 by wilisson         ###   ########.fr       */
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
    return(0);
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
        philo->id = i 
    }
}

void init_table(t_table *table)
{
    
}
