/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wilisson <wilisson@student.42heilbronn.de> +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/30 14:35:33 by wilisson          #+#    #+#             */
/*   Updated: 2026/01/17 21:03:23 by wilisson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int ac, char **av)
{
    t_table table;
    pthread_t *threads;
    int i;
    
    i = 0;
    if(ac != 5 && ac != 6)
        return(printf(WRONGINPUT), EXIT_FAILURE);
    if(parse_args(ac, av, &table) != EXIT_SUCCESS)
        return(printf(WRONGINPUT),EXIT_FAILURE);
    if(init_table(&table) != EXIT_SUCCESS)
        return(printf(WRONGINPUT), EXIT_FAILURE);
    table.start_time = current_time_ms();
    threads = malloc(sizeof(pthread_t) * table.num_philos);
    if(!threads)
        return(printf("Allocation failed"), EXIT_FAILURE);
    while(i < table.num_philos)
    {
        if(i % 2 == 0)
        {
            if(pthread_create(&threads[i], NULL, odd_philo_routine, &table.philos[i]) != 0)
                return(EXIT_FAILURE);
        }
        else
        {
            if(pthread_create(&threads[i], NULL, non_odd_philo_routine, &table.philos[i]) != 0)
                return(EXIT_FAILURE);
        }
        i++;
    }
    if(pthread_create(&table.monitor_thread, NULL, (void *)monitor_routine, &table) != 0)
        return(EXIT_FAILURE);
    i = 0;
    while(i < table.num_philos)
    {
        pthread_join(threads[i], NULL);
        i++;
    }
    pthread_join(table.monitor_thread, NULL);
    free(threads);
    destroy_forks(&table);
    destroy_philos(&table);
    cleanup_table(&table);
    return(EXIT_SUCCESS);
}
