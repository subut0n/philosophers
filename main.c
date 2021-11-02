/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: addzikow <addzikow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 17:00:44 by addzikow          #+#    #+#             */
/*   Updated: 2021/11/02 09:50:35 by addzikow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philosophers.h>

void parse_args(int ac, char **av, t_party *party)
{
	party->arg.nb_philo = ft_atoi(av[1]);
	party->arg.die = ft_atoi(av[2]);
	party->arg.eat = ft_atoi(av[3]);
	party->arg.sleep = ft_atoi(av[4]);
	if (ac == 6)
		party->arg.nb_eat = ft_atoi(av[5]);
}

int main(int argc, char **argv)
{
	t_party party;

	parse_args(argc, argv, &party);
}