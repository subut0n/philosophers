/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main-processes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: addzikow <addzikow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 10:11:25 by addzikow          #+#    #+#             */
/*   Updated: 2021/11/02 10:26:04 by addzikow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int main(int ac, char *av[])
{
	int pid = fork();
	int x = 2;

	if (pid == -1)
		return (1);
	if (pid == 0)
	{
		x++;
	}
	sleep(2);
	printf("Value of x: %d\n", x);
	if (pid != 0)
	{
		wait(NULL);
	}
	return(0);
}