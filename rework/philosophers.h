/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: addzikow <addzikow@42student.lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 11:04:18 by addzikow          #+#    #+#             */
/*   Updated: 2021/11/05 11:34:55 by addzikow         ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */


# include	<stdio.h>
# include	<stdlib.h>
# include	<unistd.h>
# include	<stdbool.h>
# include	<string.h>
# include	<limits.h>
# include	<pthread.h>
# include	<sys/time.h>
# include	<signal.h>

# include   "../libft/libft.h"


# define EVEN 0
# define ODD 1

typedef struct s_arg
{
	int	nb_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	meals_per_philo;
}	t_arg;

typedef enum e_state
{
	NOT_INIT	=	0,
	FORK		=	1,
	EAT			=	2,
	SLEEP		=	3,
	THINK		=	4,
	DIE			=	5,
}	t_state;

typedef struct s_ph
{
	int			i;
	pthread_t	philosoph;
	bool		fork_in_use;
	bool		alive;
	int			state;
}	t_ph;

typedef struct s_data
{
	t_arg				arg;
	t_ph				*philo;
	t_state				state;
}	t_data;
