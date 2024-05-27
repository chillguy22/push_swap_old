/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaktimur <eaktimur@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 20:19:07 by eaktimur          #+#    #+#             */
/*   Updated: 2024/05/20 15:13:04 by eaktimur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

void	exiterror(void)
{
	printf("Error\n");
	exit(0);
}

int	ft_atoi(const char *str)
{
	int				i;
	long long int	num;
	long long int	sign;

	sign = 1;
	i = 0;
	num = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + (str[i] - 48);
		i++;
	}
	if (((!(str[i] >= '0' && str[i] <= '9')) && (str[i] != '\0')) || (((num
					* sign) > 2147483648) || ((num * sign) < -2147483647)))
		exiterror();
	return (num * sign);
}

int	check_duplicates(int *tab, int n, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		if (tab[i] == n)
			return (1);
		i++;
	}
	return (0);
}

int	check_inputs(char **argv, int argc)
{
	int	i;
	int	*tab;

	tab = (int *)malloc(sizeof(int) * (argc - 1));
	if (!tab)
		exiterror();
	i = 1;
	while (i < argc)
	{
		tab[i - 1] = ft_atoi(argv[i]);
		if (check_duplicates(tab, tab[i - 1], i-1))
			exiterror();
		i++;
	}
	for (int k = i - 2; k >= 0; k--)
		printf("Element %i: %i\n", k, tab[k]);
	return (0);
}

int	main(int argc, char **argv)
{
	if (argc < 2 || check_inputs(argv, argc))
		exiterror();
	return (0);
}
