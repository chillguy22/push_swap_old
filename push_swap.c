/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaktimur <eaktimur@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 20:19:07 by eaktimur          #+#    #+#             */
/*   Updated: 2024/05/28 18:28:34 by eaktimur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

void	swap(int *array, int length, char c)
{
	int	temp;

	if (length > 1)
	{
		temp = array[0];
		array[0] = array[1];
		array[1] = temp;
	}
	if (c == 'a')
		write(1, "sa\n", 3);
	else if (c == 'b')
		write(1, "sb\n", 3);
}

void	push(int *a, int *len_a, int *b, int *len_b)
{
	int	i;

	if (*len_b == 0)
		return ;
	i = *len_b;
	while (i >= 0)
	{
		b[i + 1] = b[i];
		i--;
	}
	b[0] = a[0];
	(*len_b)++;
	(*len_a)--;
	i = 0;
	while (i < *len_a)
	{
		a[i] = a[i + 1];
		i++;
	}
	return ;
}

void	rotate(int *arr, int length, char x)
{
	int	i;
	int	first_element;

	i = 0;
	if (length <= 1)
		return ;
	first_element = arr[0];
	while (i < length - 1)
	{
		arr[i] = arr[i + 1];
		i++;
	}
	arr[length - 1] = first_element;
	if (x == 'a')
		write(1, "ra\n", 3);
	else if (x == 'b')
		write(1, "rb\n", 3);
}

void	reverse_rotate(int *arr, int length, char c)
{
	int	i;
	int	last_element;

	if (length <= 1)
		return ;
	i = length - 1;
	last_element = arr[length - 1];
	while (i > 0)
	{
		arr[i] = arr[i - 1];
		i--;
	}
	arr[0] = last_element;
	if (c == 'a')
		write(1, "rra\n", 4);
	else if (c == 'b')
		write(1, "rrb\n", 4);
}

void	exiterror(void)
{
	printf("Error\n");
	exit(0);
}

void	exiterror1(int *a, int *b)
{
	printf("Error\n");
	free(a);
	free(b);
	exit(0);
}

void	exitsuccess(int *tab)
{
	// free(tab);
	return ;
	exit(0);
}

int	check_if_sorted(int *tab, int len)
{
	int	i;

	if (len <= 1)
		return (1);
	i = 0;
	while (i < len - 1)
	{
		if (tab[i] > tab[i + 1])
			return (0);
		i++;
	}
	return (1);
}

void	sort2(int *a)
{
	int	temp;

	if (a[0] > a[1])
	{
		write(1, "ra\n", 3);
		exitsuccess(a);
	}
	else
		exitsuccess(a);
	return ;
}

void	sort3(int *a)
{
	int	max_index;

	max_index = 0;
	if (a[1] > a[max_index])
		max_index = 1;
	if (a[2] > a[max_index])
		max_index = 2;
	if (max_index == 0)
	{
		rotate(a, 3, 'a');
		if (a[0] > a[1])
			swap(a, 3, 'a');
	}
	else if (max_index == 1)
	{
		reverse_rotate(a, 3, 'a');
		if (a[0] > a[1])
			swap(a, 3, 'a');
	}
	else if (max_index == 2)
	{
		if (a[0] > a[1])
			swap(a, 3, 'a');
	}
	exitsuccess(a);
}

int	find_target(int num, int *b)
{
	// loop checking b to find target of num
	// return index of b
}

void	index_assign(int *big, int *b)
{
	if (b[0] > b[1])
		big = 0;
	else
		big = 1;
}

int	**create2DArray(int *array1, int length1, int *array2, int length2)
{
	int	**array2D;
	int	i;

	array2D = (int **)malloc(2 * sizeof(int *));
	array2D[0] = (int *)malloc(length1 * sizeof(int));
	array2D[1] = (int *)malloc(length2 * sizeof(int));
	array2D[2] = (int *)malloc(1 * sizeof(int));
	array2D[3] = (int *)malloc(1 * sizeof(int));
	i = 0;
	while (i < length1)
	{
		array2D[0][i] = array1[i];
		i++;
	}
	i = 0;
	while (i < length2)
	{
		array2D[1][i] = array2[i];
		i++;
	}
	array2D[2][0] = length1;
	array2D[3][0] = length2;
	return (array2D); // remember to free
}

int	find_big_index(int *arr, int len)
{
	int	i;
	int	maxIndex;

	if (len <= 0)
		return (-1);
	i = 1;
	maxIndex = 0;
	while (i < len)
	{
		if (arr[i] > arr[maxIndex])
			maxIndex = i;
		i++;
	}
	return (maxIndex);
}

void	assign_targets(int *targets, int **lol, int biggest_index)
{
	int	i;
	int	j;
	int	temp;
	int	diff;
	int	difftemp;

	i = 0;
	while (i < lol[2][0])
	{
		j = 0;
		diff = INT_MAX;
		while (j < lol[3][0])
		{
			if ((lol[0][i] > lol[1][j]))
			{
				difftemp = lol[0][i] - lol[1][j];
				if (difftemp < diff)
				{
					diff = difftemp;
					temp = j;
				}
			}
			j++;
		}
		if (diff == INT_MAX)
			j = find_big_index(lol[1], lol[3][0]);
		targets[i] = j;
		i++;
	}
}

void	sort(int *a, int *len_a, int *b, int *len_b)
{
	int	biggest_index;
	int	*targets;
	int	**lol;

	if (len_a == 4)
	{
		push(*a, *len_a, *b, *len_b);
		write(1, "pb\n", 3);
	}
	if (len_a >= 5)
	{
		push(*a, *len_a, *b, *len_b);
		write(1, "pb\n", 3);
		push(*a, *len_a, *b, *len_b);
		write(1, "pb\n", 3);
	}
	index_assign(biggest_index, *b);
	targets = (int *)malloc(sizeof(int) * (*len_a));
	if (!targets)
		exiterror1(a, b);
	lol = create2DArray(a, len_a, b, len_b);
	assign_targets(targets, lol, biggest_index);
}

int	*push_swap(int *a, int len_a)
{
	int	*b;
	int	len_b;

	b = (int *)malloc(sizeof(int) * len_a);
	if (!b)
		exiterror();
	len_b = 0;
	if (check_if_sorted(a, len_a))
		return (a);
	if (len_a == 2)
		sort2(a);
	if (len_a == 3)
		sort3(a);
	sort(*a, len_a, *b, len_b);
	// free(a, b)
	return (a);
}
// Main function to test the push_swap function
int	main(void)
{
	int	case1[] = {1, 2, 3};
	int	case2[] = {2, 1};
	int	case3[] = {3, 2, 1};
	int	case4[] = {1, 3, 2};
	int	case5[] = {2, 3, 1};
	int	case6[] = {2, 1, 3};
	int	case7[] = {3, 1, 2};
	int	*arr1;
	int	*arr2;
	int	*arr3;
	int	*arr4;
	int	*arr5;
	int	*arr6;
	int	*arr7;

	// Test case 1: Already sorted
	printf("Test case 1 (1, 2, 3):\n");
	arr1 = malloc(3 * sizeof(int));
	if (!arr1)
		exiterror();
	for (int i = 0; i < 3; i++)
		arr1[i] = case1[i];
	push_swap(arr1, 3);
	free(arr1);
	// Test case 2: Two elements unsorted
	printf("Test case 2 (2, 1):\n");
	arr2 = malloc(2 * sizeof(int));
	if (!arr2)
		exiterror();
	for (int i = 0; i < 2; i++)
		arr2[i] = case2[i];
	push_swap(arr2, 2);
	free(arr2);
	// Test case 3: Three elements reverse sorted
	printf("Test case 3 (3, 2, 1):\n");
	arr3 = malloc(3 * sizeof(int));
	if (!arr3)
		exiterror();
	for (int i = 0; i < 3; i++)
		arr3[i] = case3[i];
	push_swap(arr3, 3);
	free(arr3);
	// Test case 4: Three elements middle unsorted
	printf("Test case 4 (1, 3, 2):\n");
	arr4 = malloc(3 * sizeof(int));
	if (!arr4)
		exiterror();
	for (int i = 0; i < 3; i++)
		arr4[i] = case4[i];
	push_swap(arr4, 3);
	free(arr4);
	// Test case 5: Three elements last unsorted
	printf("Test case 5 (2, 3, 1):\n");
	arr5 = malloc(3 * sizeof(int));
	if (!arr5)
		exiterror();
	for (int i = 0; i < 3; i++)
		arr5[i] = case5[i];
	push_swap(arr5, 3);
	free(arr5);
	printf("Test case 6 (2, 1, 3):\n");
	arr6 = malloc(3 * sizeof(int));
	if (!arr6)
		exiterror();
	for (int i = 0; i < 3; i++)
		arr6[i] = case6[i];
	push_swap(arr6, 3);
	free(arr6);
	printf("Test case 7 (3, 1, 2):\n");
	arr7 = malloc(3 * sizeof(int));
	if (!arr7)
		exiterror();
	for (int i = 0; i < 3; i++)
		arr7[i] = case7[i];
	push_swap(arr7, 3);
	free(arr7);
	return (0);
}
