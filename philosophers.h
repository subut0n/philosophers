/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: addzikow <addzikow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 16:15:05 by addzikow          #+#    #+#             */
/*   Updated: 2021/11/03 14:45:13 by addzikow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include "libft/libft.h"

typedef struct s_arg
{
    int				nb_philo;
    int				die;
    int				eat;
    int				sleep;
    int				nb_eat;
}           t_arg;

typedef struct  s_philo
{
    int				id;
    pthread_t		thread_id;
    pthread_mutex_t	*fork_right;
    pthread_mutex_t	fork_left;
	long int		ms_eat;
	unsigned int	nb_eat;
}               t_philo;

typedef struct	s_party
{
	t_philo *philo;
	t_arg 	arg;
}				t_party;

