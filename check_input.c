/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaktimur <eaktimur@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 20:19:07 by eaktimur          #+#    #+#             */
/*   Updated: 2024/05/21 17:45:21 by eaktimur         ###   ########.fr       */
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

void	exiterror1(int *tab)
{
	free(tab);
	printf("Error\n");
	exit(0);
}

static int	is_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\v' || c == '\f'
		|| c == '\r')
		return (1);
	else
		return (0);
}

static int	words_count(const char *str)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	if (str == 0)
		return (count);
	while (str[i] != '\0')
	{
		if ((is_space(str[i + 1]) || str[i + 1] == '\0') && (!(is_space(str[i])
					|| str[i] == '\0')))
			count++;
		i++;
	}
	return (count);
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
	if (((!(str[i] >= '0' && str[i] <= '9')) && (str[i] != '\0')
			&& (!(is_space(str[i])))) || (((num * sign) > 2147483648) || ((num
					* sign) < -2147483647)))
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

int	check_duplicates1(int *array, int length)
{
	int	i;
	int	j;

	i = 0;
	while (i < length - 1)
	{
		j = i + 1;
		while (j < length)
		{
			if (array[i] == array[j])
				return (1);
			j++;
		}
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
		if (check_duplicates(tab, tab[i - 1], i - 1))
			exiterror1(tab);
		i++;
	}
	free(tab);
	return (0);
}

int	*ft_split(char *str)
{
	int	*tab;
	int	i;
	int	count;

	i = 0;
	count = words_count(str);
	tab = (int *)malloc(count * sizeof(int));
	if (!tab)
		return (NULL);
	while (*str)
	{
		while (is_space(*str))
			str++;
		if (*str == '-' || *str == '+' || (*str >= '0' && *str <= '9'))
		{
			tab[i] = ft_atoi(str);
			i++;
			while (*str && !is_space(*str))
				str++;
		}
		else
			exiterror1(tab);
	}
	return (tab);
}

int	*extract(int argc, char **argv)
{
	int	*tab;
	int	i;

	tab = (int *)malloc((argc - 1) * sizeof(int));
	if (!tab)
		exiterror();
	i = 1;
	while (i < argc)
	{
		tab[i - 1] = ft_atoi(argv[i]);
		i++;
	}
	return (tab);
}

int	main(int argc, char **argv)
{
	int	count;
	int	*tab;

	if (argc < 2 || (argc > 2 && check_inputs(argv, argc)))
		exiterror();
	if (argc == 2)
	{
		count = words_count(argv[1]);
		if (count >= 1 && (((argv[1][0] >= '0') && (argv[1][0] <= '9'))
				|| argv[1][0] == '-' || argv[1][0] <= '+'))
		{
			tab = ft_split(argv[1]);
			if (check_duplicates1(tab, count))
				exiterror1(tab);
			for (int k = 0; k < count; k++)
				printf("Element %i: %i\n", k, tab[k]);
			// push_swap(tab);
		}
		else
			exiterror();
		return (0);
	}
	tab = extract((argc), argv);
	for (int k = 0; k < argc - 1; k++)
		printf("Element %i: %i\n", k, tab[k]);
	// push_swap(tab);
	free(tab);
	return (0);
}
