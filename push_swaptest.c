/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swaptest.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaktimur <eaktimur@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 20:19:07 by eaktimur          #+#    #+#             */
/*   Updated: 2024/06/06 18:40:15 by eaktimur         ###   ########.fr       */
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

	if (*len_a == 0)
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

void	rotateboth(int **lol)
{
	int	i;
	int	first_element;

	i = 0;
	if (lol[2][0] <= 1)
		return ;
	first_element = lol[0][0];
	while (i < lol[2][0] - 1)
	{
		lol[0][i] = lol[0][i + 1];
		i++;
	}
	lol[0][lol[2][0] - 1] = first_element;
	i = 0;
	if (lol[3][0] <= 1)
		return ;
	first_element = lol[1][0];
	while (i < lol[3][0] - 1)
	{
		lol[1][i] = lol[1][i + 1];
		i++;
	}
	lol[1][lol[3][0] - 1] = first_element;
	write(1, "rr\n", 3);
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

void	reverse_rotateboth(int **lol)
{
	int	i;
	int	last_element;

	if (lol[2][0] <= 1)
		return ;
	i = lol[2][0] - 1;
	last_element = lol[0][lol[2][0] - 1];
	while (i > 0)
	{
		lol[0][i] = lol[0][i - 1];
		i--;
	}
	lol[0][0] = last_element;

	if (lol[3][0] <= 1)
		return ;
	i = lol[3][0] - 1;
	last_element = lol[1][lol[3][0] - 1];
	while (i > 0)
	{
		lol[1][i] = lol[1][i - 1];
		i--;
	}
	lol[1][0] = last_element;
	write(1, "rrr\n", 4);
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

void	free2darray(int **array, int numrows)
{
	int	i;

	i = 0;
	while (i < numrows)
	{
		free(array[i]);
		i++;
	}
	free(array);
}


void	exitsuccess(int *tab, int *tab1)
{
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
		write(1, "ra\n", 3);
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
}

int	**create2DArray(int *array1, int length1, int *array2, int length2)
{
	int	**array2d;
	int	i;

	array2d = (int **)malloc(2 * sizeof(int *));
	array2d[0] = (int *)malloc(length1 * sizeof(int));
	array2d[1] = (int *)malloc(length2 * sizeof(int));
	array2d[2] = (int *)malloc(1 * sizeof(int));
	array2d[3] = (int *)malloc(1 * sizeof(int));
	i = 0;
	while (i < length1)
	{
		array2d[0][i] = array1[i];
		i++;
	}
	i = 0;
	while (i < length2)
	{
		array2d[1][i] = array2[i];
		i++;
	}
	array2d[2][0] = length1;
	array2d[3][0] = length2;
	return (array2d); // remember to free
}

int	find_big_index(int *arr, int len)
{
	int	i;
	int	max_index;

	if (len <= 0)
		return (-1);
	i = 1;
	max_index = 0;
	while (i < len)
	{
		if (arr[i] > arr[max_index])
			max_index = i;
		i++;
	}
	return (max_index);
}
int find_smallest_index(int *arr, int len)
{
    int i;
    int min_index;

    if (len <= 0)
        return (-1);
    i = 1;
    min_index = 0;
    while (i < len)
    {
        if (arr[i] < arr[min_index])
            min_index = i;
        i++;
    }
    return (min_index);
}

void	assign_targets(int *targets, int **lol)
{
	long	i;
	long	j;
	long	temp;
	long	diff;
	long	difftemp;

	i = 0;
	while (i < lol[2][0])
	{
		j = 0;
		diff = LONG_MAX;
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
		if (diff == LONG_MAX)
			temp = find_big_index(lol[1], lol[3][0]);
		targets[i] = temp;
		i++;
	}
}

int* rotationsToBringElementToTop(int* arr, int len, int target) {
    int targetIndex = -1;

    // Find the index of the target element
    for (int i = 0; i < len; i++) {
        if (arr[i] == target) {
            targetIndex = i;
            break;
        }
    }

    // Allocate memory for the result
    int* result = (int*)malloc(1 * sizeof(int*));

    // If the target element is not found, return -1
    if (targetIndex == -1) {
        result[0] = -1;
        result[1] = -1;
        return result;
    }

    // Calculate the number of upward rotations
    int upwardRotations = targetIndex;

    // Calculate the number of downward rotations
    int downwardRotations = len - targetIndex;

    // Determine the minimum rotations and the direction
    if (upwardRotations <= downwardRotations) {
        result[0] = 1;  // Upwards
        result[1] = upwardRotations;
    } else {
        result[0] = -1; // Downwards
        result[1] = downwardRotations;
    }

    return result;
}

void process(int *result, int **lol)
{
	if (result[0] == result[2] && result[0] == 1)
	{
		while (result[1] != 0 || result[3] != 0)
		{
			rotateboth(lol);
			result[1] -= 1;
			result[3] -= 1;
		}
		while (result[1] != 0)
		{
			rotate(lol[0], lol[2][0], 'a');
			result[1]--;
		}
		while (result[3] != 0)
		{
			rotate(lol[1], lol[3][0], 'b');
			result[3]--;
		}
	}
	else if (result[0] == result[2] && result[0] == -1)
	{
		while (result[1] != lol[2][0] + 1 || result[3] != lol[3][0] + 1)
		{
			reverse_rotateboth(lol);
			result[1] += 1;
			result[3] += 1;
		}
		while ((result[1] != lol[2][0] + 1) && (result[1] < lol[2][0] + 1))
		{
			reverse_rotate(lol[0], lol[2][0], 'a');
			result[1]++;
		}
		while ((result[3] != lol[3][0] + 1) && (result[3] < lol[3][0] + 1))
		{
			reverse_rotate(lol[1], lol[3][0], 'b');
			result[3]++;
		}
	}
	else if (result[0] != result[2] && result[0] == 1)
	{
		while ((result[1] != 0) && (result[1] > 0))
		{
			rotate(lol[0], lol[2][0], 'a');
			result[1]--;
		}
		while ((result[3] != lol[3][0] + 1) && (result[3] < lol[3][0]))
		{
			reverse_rotate(lol[1], lol[3][0], 'b');
			result[3]++;
		}
	}
	else if (result[0] != result[2] && result[0] == -1)
	{
		while ((result[1] != lol[2][0] + 1) && (result[1] < lol[2][0]))
		{
			reverse_rotate(lol[0], lol[2][0], 'a');
			result[1]++;
		}
		while ((result[3] != 0) && (result[3] > 0))
		{
			rotate(lol[1], lol[3][0], 'b');
			result[3]--;
		}
	}
}

int cases(int *a, int *b, int **lol)
{
	int a_direction = a[0];
	int b_direction = b[0];
	int a_index = a[1];
	int b_index = b[1];
	int a_len = lol[2][0];
	int b_len = lol[3][0];
	int cost = 0;
	if (a_direction == b_direction && b_direction == 1)
	{
		while (a_index != 0 || b_index != 0)
		{
			cost++;
			a_index -= 1;
			b_index -= 1;
		}
		if (a_index != 0)
		{
			while (a_index != 0)
			{
				cost++;
				a_index -= 1;
			}
		}
		else if (b_index != 0)
		{
			while (b_index != 0)
			{
				cost++;
				b_index -= 1;
			}
		}
	}
	else if (a[0] == b[0] && a[0] == -1)
	{
		while (a_index != a_len + 1 || b_index != b_len + 1)
		{
			cost++;
			a_index += 1;
			b_index += 1;
		}
		if (a_index != a_len + 1)
		{
			while (a_index != a_len + 1)
			{
				cost++;
				a_index += 1;
			}
		}
		else if (b_index != b_len + 1)
		{
			while (b_index != b_len + 1)
			{
				cost++;
				b_index += 1;
			}
		}
	}
	else if (a[0] != b[0] && a[0] == 1)
	{
		while (b_index != b_len + 1)
		{
			cost++;
			b_index += 1;
		}
		while (a_index != 0)
		{
			cost++;
			a_index -= 1;
		}
	}
	else if (a[0] != b[0] && a[0] == -1)
	{
		while (a_index != a_len + 1)
		{
			cost++;
			a_index += 1;
		}
		while (b_index != 0)
		{
			cost++;
			b_index -= 1;
		}
	}
	return (cost);
}

int	*find_cheapest(int **lol, int *targets)
{
	int	i;
	int	cheapest_index;
	int	cost;
	int	*result;
	int	*temp;
	int	*temp1;

	cost = INT_MAX;
	temp = (int *)malloc(sizeof(int) * 2);
	if (!temp)
	{
		free2darray(lol, 4);
		free(targets);
		exiterror();
	}
	temp1 = (int *)malloc(sizeof(int) * 2);
	if (!temp1)
	{
		free2darray(lol, 4);
		free(targets);
		free(temp);
		exiterror();
	}
	result = (int *)malloc(sizeof(int) * 4);
	if (!result)
	{
		free2darray(lol, 4);
		free(targets);
		free(temp);
		free(temp1);
		exiterror();
	}
	i = 0;
	printf("test1 %i\n", lol[2][0]);
	while (i < (int)lol[2][0])
	{
		printf("i: %i\n", i);
		temp = rotationsToBringElementToTop(lol[0], lol[2][0], i);
		temp1 = rotationsToBringElementToTop(lol[1], lol[3][0], targets[i]);
		if (cases(temp, temp1, lol) < cost)
		{
			cost = cases(temp, temp1, lol);
			result[0] = temp[0];
			result[2] = temp1[0];
			result[1] = i;
			result[3] = targets[i];
		}
		i++;
	}
	return (result);
}
void	sort11(int *a, int *len_a, int *b, int *len_b)
{
	int cost;
	int i;
	int temp_index;
	int temp_value;

	while(*len_b > 0)
	{
		i = 0;
		temp_value = INT_MAX;
		while(i < *len_a)
		{
			if(a[i] > b[0] && a[i] < temp_value)
			{
				temp_index = i;
				temp_value = a[i];
			}
			i++;
		}
		if (temp_value == INT_MAX)
			temp_index = find_smallest_index(b, *len_b);
		// now we have the target index and value
		if (temp_index < *len_a/2)
		{
			while(temp_index > 0)
			{
				rotate(a, *len_a, 'a');
				temp_index--;
			}
		}
		else if (temp_index >= *len_a/2)
		{
			while (temp_index < *len_a)
			{
				reverse_rotate(a, *len_a, 'a');
				temp_index++;
			}
		}
		push(b, len_b, a, len_a);
		write(1, "pa\n", 3);
	}
	temp_index = find_smallest_index(b, *len_b);
	if (temp_index < *len_a/2)
	{
		while(temp_index > 0)
		{
			rotate(a, *len_a, 'a');
			temp_index--;
		}
	}
	else if (temp_index >= *len_a/2)
	{
		while (temp_index < *len_a)
		{
			reverse_rotate(a, *len_a, 'a');
			temp_index++;
		}
	}
}

void	sort1(int *a, int *len_a, int *b, int *len_b)
{
	int	*targets;
	int	**lol;
	int	*result;
	int	i;

	if (*len_a >= 4)
	{
		push(a, len_a, b, len_b);
		write(1, "pb\n", 3);
		if (*len_a >= 4)
		{
			push(a, len_a, b, len_b);
			write(1, "pb\n", 3);
		}
	}
	if (*len_a != 3)
	{
		targets = (int *)malloc(sizeof(int) * (*len_a));
		if (!targets)
			exiterror1(a, b);
		lol = create2DArray(a, *len_a, b, *len_b);
		assign_targets(targets, lol);
		i = 0;
		printf("test\n");
		while (lol[2][0] != 3)
		{
			result = find_cheapest(lol, targets);
			printf("lol[2][0]: %i\n", lol[2][0]);
			process(result, lol);
		}
		printf("test\n");
		free(targets);
	}
	sort3(a);
	sort11(a, len_a, b, len_b);
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
	{
		free(b);
		return (a);
	}
	if (len_a == 2)
		sort2(a);
	else if (len_a == 3)
		sort3(a);
	else
		sort1(a, &len_a, b, &len_b);
	// free a in main
	free(b);
	return (a);
}
// Main function to test the push_swap function
int	main(void)
{
	int	case1[] = {1, 3, 2, 6, 4, 10};
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
	printf("Test case 1 (1, 3, 2, 4, 90, -3331):\n");
	arr1 = malloc(6 * sizeof(int));
	if (!arr1)
		exiterror();
	for (int i = 0; i < 6; i++)
		arr1[i] = case1[i];
	push_swap(arr1, 6);
	free(arr1);
	// // Test case 2: Two elements unsorted
	// printf("Test case 2 (2, 1):\n");
	// arr2 = malloc(2 * sizeof(int));
	// if (!arr2)
	// 	exiterror();
	// for (int i = 0; i < 2; i++)
	// 	arr2[i] = case2[i];
	// push_swap(arr2, 2);
	// free(arr2);
	// // Test case 3: Three elements reverse sorted
	// printf("Test case 3 (3, 2, 1):\n");
	// arr3 = malloc(3 * sizeof(int));
	// if (!arr3)
	// 	exiterror();
	// for (int i = 0; i < 3; i++)
	// 	arr3[i] = case3[i];
	// push_swap(arr3, 3);
	// free(arr3);
	// // Test case 4: Three elements middle unsorted
	// printf("Test case 4 (1, 3, 2):\n");
	// arr4 = malloc(3 * sizeof(int));
	// if (!arr4)
	// 	exiterror();
	// for (int i = 0; i < 3; i++)
	// 	arr4[i] = case4[i];
	// push_swap(arr4, 3);
	// free(arr4);
	// // Test case 5: Three elements last unsorted
	// printf("Test case 5 (2, 3, 1):\n");
	// arr5 = malloc(3 * sizeof(int));
	// if (!arr5)
	// 	exiterror();
	// for (int i = 0; i < 3; i++)
	// 	arr5[i] = case5[i];
	// push_swap(arr5, 3);
	// free(arr5);
	// printf("Test case 6 (2, 1, 3):\n");
	// arr6 = malloc(3 * sizeof(int));
	// if (!arr6)
	// 	exiterror();
	// for (int i = 0; i < 3; i++)
	// 	arr6[i] = case6[i];
	// push_swap(arr6, 3);
	// free(arr6);
	// printf("Test case 7 (3, 1, 2):\n");
	// arr7 = malloc(3 * sizeof(int));
	// if (!arr7)
	// 	exiterror();
	// for (int i = 0; i < 3; i++)
	// 	arr7[i] = case7[i];
	// push_swap(arr7, 3);
	// free(arr7);
	return (0);
}