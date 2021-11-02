/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   coucou.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: addzikow <addzikow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 11:33:49 by addzikow          #+#    #+#             */
/*   Updated: 2021/11/02 12:58:54 by addzikow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void *roll_dice()
{
	int value;
	int *result;

	value = (rand() % 6) + 1;
	result = malloc(sizeof(int));
	if (!result)
		perror("Malloc problem.");
	*result = value;
	printf("thread result : %p\n", result);
	printf("value : %d\n", value);
	return ((void*)result);
}

int main(int ac, char *av[])
{
	pthread_t th;
	int *result;

	if (pthread_create(&th, NULL, &roll_dice, NULL) != 0)
	{
		perror("Thread failed to create.\n");
		return (-1);
	}
	if (pthread_join(th, (void **)&result) != 0)
		return (-1);
	printf("Main res : %p\n", result);
	printf("Result : %d \n", *result);
	free(result);
	return (0);
}