/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swaptest.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaktimur <eaktimur@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 20:19:07 by eaktimur          #+#    #+#             */
/*   Updated: 2024/06/10 16:09:04 by eaktimur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

void	exit_zero(void)
{
	printf("Error\n");
	exit(0);
}

void	exit_free(int *tab)
{
	free(tab);
	printf("Error\n");
	exit(0);
}

void	exit_free2(int *a, int *b)
{
	printf("Error\n");
	free(a);
	free(b);
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
		exit_zero();
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
		exit_zero();
	i = 1;
	while (i < argc)
	{
		tab[i - 1] = ft_atoi(argv[i]);
		if (check_duplicates(tab, tab[i - 1], i - 1))
			exit_free(tab);
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
			exit_free(tab);
	}
	return (tab);
}

int	*extract(int argc, char **argv)
{
	int	*tab;
	int	i;

	tab = (int *)malloc((argc - 1) * sizeof(int));
	if (!tab)
		exit_zero();
	i = 1;
	while (i < argc)
	{
		tab[i - 1] = ft_atoi(argv[i]);
		i++;
	}
	return (tab);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_alpha.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaktimur <eaktimur@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 20:19:07 by eaktimur          #+#    #+#             */
/*   Updated: 2024/06/09 14:14:39 by eaktimur         ###   ########.fr       */
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
	// Shift elements in b to the right to make space for the new element
	for (i = *len_b; i > 0; i--)
	{
		b[i] = b[i - 1];
	}
	b[0] = a[0]; // Move the first element of a to the first position of b
	(*len_b)++; // Increment the length of b
	(*len_a)--; // Decrement the length of a
	// Shift elements in a to the left to fill the gap
	for (i = 0; i < *len_a; i++)
	{
		a[i] = a[i + 1];
	}
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

void	rotateboth(int *a, int *b, int len_a, int len_b)
{
	int	i;
	int	first_element;

	i = 0;
	if (len_a <= 1)
		return ;
	first_element = a[0];
	while (i < len_a - 1)
	{
		a[i] = a[i + 1];
		i++;
	}
	a[len_a - 1] = first_element;
	i = 0;
	if (len_b <= 1)
		return ;
	first_element = b[0];
	while (i < len_b - 1)
	{
		b[i] = b[i + 1];
		i++;
	}
	b[len_b - 1] = first_element;
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

void	reverse_rotateboth(int *a, int *b, int len_a, int len_b)
{
	int	i;
	int	last_element;

	if (len_a <= 1)
		return ;
	i = len_a - 1;
	last_element = a[len_a - 1];
	while (i > 0)
	{
		a[i] = a[i - 1];
		i--;
	}
	a[0] = last_element;
	if (len_b <= 1)
		return ;
	i = len_b - 1;
	last_element = b[len_b - 1];
	while (i > 0)
	{
		b[i] = b[i - 1];
		i--;
	}
	b[0] = last_element;
	write(1, "rrr\n", 4);
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
int	find_smallest_index(int *arr, int len)
{
	int	i;
	int	min_index;

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

void	assign_targets(int *targets, int *a, int *b, int *lengths)
{
	long	i;
	long	j;
	long	temp;
	long	diff;
	long	difftemp;

	i = 0;
	while (i < lengths[0])
	{
		j = 0;
		diff = LONG_MAX;
		while (j < lengths[1])
		{
			if ((a[i] > b[j]))
			{
				difftemp = a[i] - b[j];
				if (difftemp < diff)
				{
					diff = difftemp;
					temp = j;
				}
			}
			j++;
		}
		if (diff == LONG_MAX)
			temp = find_big_index(b, lengths[1]);
		targets[i] = temp;
		i++;
	}
}

int	*rotations_to_bring_to_top(int i, int len)
{
	int	*result;

	// Allocate memory for the result array
	result = (int *)malloc(2 * sizeof(int));
	if (result == NULL)
	{
		perror("Failed to allocate memory for result array");
		exit(EXIT_FAILURE);
	}
	// Calculate rotations needed for both directions
	int rotations_up = i;        
		// Rotations needed to bring i to the top by rotating upwards
	int rotations_down = len - i;
		// Rotations needed to bring i to the top by rotating downwards
	// Determine the faster direction
	if (rotations_up <= rotations_down)
	{
		result[0] = 1; // 1 for upwards
		result[1] = rotations_up;
	}
	else
	{
		result[0] = -1; // -1 for downwards
		result[1] = rotations_down;
	}
	return (result);
}

void	process(int *result, int *a, int *b, int *lengths)
{
	if (result[0] == result[2] && result[0] == 1)
	{
		while (result[1] != 0 && result[3] != 0)
		{
			rotateboth(a, b, lengths[0], lengths[1]);
			result[1] -= 1;
			result[3] -= 1;
		}
		while (result[1] != 0)
		{
			rotate(a, lengths[0], 'a');
			result[1]--;
		}
		while (result[3] != 0)
		{
			rotate(b, lengths[1], 'b');
			result[3]--;
		}
	}
	else if (result[0] == result[2] && result[0] == -1)
	{
		while (result[1] != lengths[0] + 1 && result[3] != lengths[1] + 1)
		{
			reverse_rotateboth(a, b, lengths[0], lengths[1]);
			result[1] += 1;
			result[3] += 1;
		}
		while ((result[1] != lengths[0] + 1) && (result[1] < lengths[0] + 1))
		{
			reverse_rotate(a, lengths[0], 'a');
			result[1]++;
		}
		while ((result[3] != lengths[1] + 1) && (result[3] < lengths[1] + 1))
		{
			reverse_rotate(b, lengths[1], 'b');
			result[3]++;
		}
	}
	else if (result[0] != result[2] && result[0] == 1)
	{
		while ((result[1] != 0) && (result[1] > 0))
		{
			rotate(a, lengths[0], 'a');
			result[1]--;
		}
		while ((result[3] != lengths[1] + 1) && (result[3] < lengths[1]))
		{
			reverse_rotate(b, lengths[1], 'b');
			result[3]++;
		}
	}
	else if (result[0] != result[2] && result[0] == -1)
	{
		while ((result[1] != lengths[0] + 1) && (result[1] < lengths[0]))
		{
			reverse_rotate(a, lengths[0], 'a');
			result[1]++;
		}
		while ((result[3] != 0) && (result[3] > 0))
		{
			rotate(b, lengths[1], 'b');
			result[3]--;
		}
	}
	// printf("len_a before pa: %i\n", lengths[0]);
	push(a, &lengths[0], b, &lengths[1]);
	write(1, "pb\n", 3);
	// printf("len_a after pa: %i\n", lengths[0]);
}

int	cases(int *a, int *b, int *lengths, int **temp)
{
	int	a_direction;
	int	b_direction;
	int	a_index;
	int	b_index;
	int	a_len;
	int	b_len;
	int	cost;

	a_direction = temp[0][0];
	b_direction = temp[1][0];
	a_index = temp[0][1];
	b_index = temp[1][1];
	a_len = lengths[0];
	b_len = lengths[1];
	cost = 0;
	if (a_direction == b_direction && b_direction == 1)
	{
		while (a_index != 0 && b_index != 0)
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
	else if (a_direction == b_direction && b_direction == -1)
	{
		while (a_index != a_len && b_index != b_len)
		{
			cost++;
			a_index += 1;
			b_index += 1;
		}
		if (a_index != a_len)
		{
			while (a_index != a_len)
			{
				cost++;
				a_index += 1;
			}
		}
		else if (b_index != b_len)
		{
			while (b_index != b_len)
			{
				cost++;
				b_index += 1;
			}
		}
	}
	else if (a_direction != b_direction && a_direction == 1)
	{
		while (b_index != b_len)
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
	else if (a_direction != b_direction && a_direction == -1)
	{
		while (a_index != a_len)
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

int	*find_cheapest(int *a, int *b, int *lengths, int *targets)
{
	int	i;
	int	cheapest_index;
	int	cost;
	int	*result;
	int	**temp;

	cost = INT_MAX;
	temp = (int **)malloc(2 * sizeof(int *));
	if (temp == NULL)
	{
		free(a);
		free(b);
		free(lengths);
		free(targets);
		exit_zero();
	}
	result = (int *)malloc(sizeof(int) * 4);
	if (!result)
	{
		free(temp);
		free(temp[0]);
		free(temp[1]);
		free(a);
		free(b);
		free(lengths);
		free(targets);
		free(temp);
		exit_zero();
	}
	i = 0;
	while (i < lengths[0])
	{
		// rotationsToBringElementToTop(a, , i); // prob
		temp[0] = rotations_to_bring_to_top(i, lengths[0]);
		temp[1] = rotations_to_bring_to_top(targets[i], lengths[1]);
		// temp[1] = rotationsToBringElementToTop(b, lengths[1], targets[i]);
		if (cases(a, b, lengths, temp) < cost)
		{
			cost = cases(a, b, lengths, temp);
			result[0] = temp[0][0];
			result[2] = temp[1][0];
			result[1] = i;
			result[3] = targets[i];
			// printf("result: (a) dir: %i index: %i, b (target) dir: %i, ind:
			//	%i\n", temp[0][0], i, temp[1][0], targets[i]);
		}
		free(temp[0]);
		free(temp[1]);
		i++;
	}
	free(temp);
	return (result);
}
void	sort11(int *a, int *len_a, int *b, int *len_b)
{
	int	cost;
	int	i;
	int	temp_index;
	int	temp_value;

	while (*len_b > 0)
	{
		i = 0;
		temp_value = INT_MAX;
		while (i < *len_a)
		{
			if (a[i] > b[0] && a[i] < temp_value)
			{
				temp_index = i;
				temp_value = a[i];
			}
			i++;
		}
		if (temp_value == INT_MAX)
			temp_index = find_smallest_index(a, *len_a);
		// now we have the target index and value
		if (temp_index <= *len_a / 2)
		{
			while (temp_index > 0)
			{
				rotate(a, *len_a, 'a');
				temp_index--;
			}
		}
		else if (temp_index > *len_a / 2)
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
	temp_index = find_smallest_index(a, *len_a);
	if (temp_index < *len_a / 2)
	{
		while (temp_index > 0)
		{
			rotate(a, *len_a, 'a');
			temp_index--;
		}
	}
	else if (temp_index >= *len_a / 2)
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
	int	*lengths;
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
		lengths = (int *)malloc(sizeof(int) * 2);
		lengths[0] = *len_a;
		lengths[1] = *len_b;
		// lol = create2DArray(a, *len_a, b, *len_b);
		i = 0;
		// printf("start len: %i & %i\n", *len_a, lengths[0]);
		while (lengths[0] != 3)
		{
			targets = (int *)malloc(sizeof(int) * (*len_a));
			if (!targets)
				exit_free2(a, b);
			assign_targets(targets, a, b, lengths);
			// for (int j = 0; j < *len_a; j++)
			//	printf("target element #%i: %i\n", j, targets[j]);
			// printf("len_a: %i & %i\n", *len_a, lengths[0]);
			result = find_cheapest(a, b, lengths, targets);
			if (!result)
			{
				free(lengths);
				free(targets);
				exit_free2(a, b);
			}
			// len_a = &lengths[0];
			// len_b = &lengths[1];
			process(result, a, b, lengths);
			*len_a = lengths[0];
			free(targets);
			free(result);
		}
		*len_a = lengths[0];
		*len_b = lengths[1];
		free(lengths);
	}
	sort3(a);
	sort11(a, len_a, b, len_b);
}

int	*push_swap(int *a, int len_a)
{
	int	*b;
	int	len_b;

	b = (int *)malloc(sizeof(int) * (len_a));
	if (!b)
		exit_zero();
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
// int	main(void)
// {
// 	int	case2[] = {2, 1};
// 	int	case3[] = {3, 2, 1};
// 	int	case4[] = {1, 3, 2};
// 	int	case5[] = {2, 3, 1};
// 	int	case6[] = {2, 1, 3};
// 	int	case7[] = {3, 1, 2};
// 	int	*arr1;
// 	int	*arr2;
// 	int	*arr3;
// 	int	*arr4;
// 	int	*arr5;
// 	int	*arr6;
// 	int	*arr7;
// 	int	len;
// 	int	case1[] = {1, -3, -2, 4, -5, -1, -33333, 234, 2222, 3931, -222, 21};

// 	// Test case 1: Already sorted
// 	len = 12;
// 	arr1 = malloc(len * sizeof(int));
// 	if (!arr1)
// 		exit_zero();
// 	printf("Test case: ");
// 	for (int i = 0; i < len; i++)
// 	{
// 		arr1[i] = case1[i];
// 		if (i != len - 1)
// 			printf("%i, ", arr1[i]);
// 		else
// 			printf("%i", arr1[i]);
// 	}
// 	arr1 = push_swap(arr1, len);
// 	printf("\nSorted array:\n");
// 	for (int i = 0; i < len; i++)
// 		printf("Element #%i: %i\n", i, arr1[i]);
// 	free(arr1);
// 	// // Test case 2: Two elements unsorted
// 	// printf("Test case 2 (2, 1):\n");
// 	// arr2 = malloc(2 * sizeof(int));
// 	// if (!arr2)
// 	// 	exit_zero();
// 	// for (int i = 0; i < 2; i++)
// 	// 	arr2[i] = case2[i];
// 	// push_swap(arr2, 2);
// 	// free(arr2);
// 	// // Test case 3: Three elements reverse sorted
// 	// printf("Test case 3 (3, 2, 1):\n");
// 	// arr3 = malloc(3 * sizeof(int));
// 	// if (!arr3)
// 	// 	exit_zero();
// 	// for (int i = 0; i < 3; i++)
// 	// 	arr3[i] = case3[i];
// 	// push_swap(arr3, 3);
// 	// free(arr3);
// 	// // Test case 4: Three elements middle unsorted
// 	// printf("Test case 4 (1, 3, 2):\n");
// 	// arr4 = malloc(3 * sizeof(int));
// 	// if (!arr4)
// 	// 	exit_zero();
// 	// for (int i = 0; i < 3; i++)
// 	// 	arr4[i] = case4[i];
// 	// push_swap(arr4, 3);
// 	// free(arr4);
// 	// // Test case 5: Three elements last unsorted
// 	// printf("Test case 5 (2, 3, 1):\n");
// 	// arr5 = malloc(3 * sizeof(int));
// 	// if (!arr5)
// 	// 	exit_zero();
// 	// for (int i = 0; i < 3; i++)
// 	// 	arr5[i] = case5[i];
// 	// push_swap(arr5, 3);
// 	// free(arr5);
// 	// printf("Test case 6 (2, 1, 3):\n");
// 	// arr6 = malloc(3 * sizeof(int));
// 	// if (!arr6)
// 	// 	exit_zero();
// 	// for (int i = 0; i < 3; i++)
// 	// 	arr6[i] = case6[i];
// 	// push_swap(arr6, 3);
// 	// free(arr6);
// 	// printf("Test case 7 (3, 1, 2):\n");
// 	// arr7 = malloc(3 * sizeof(int));
// 	// if (!arr7)
// 	// 	exit_zero();
// 	// for (int i = 0; i < 3; i++)
// 	// 	arr7[i] = case7[i];
// 	// push_swap(arr7, 3);
// 	// free(arr7);
// 	return (0);
// }


int	main(int argc, char **argv)
{
	int	count;
	int	*tab;

	if (argc < 2 || (argc > 2 && check_inputs(argv, argc)))
		exit_zero();
	if (argc == 2)
	{
		count = words_count(argv[1]);
		if (count >= 1 && (((argv[1][0] >= '0') && (argv[1][0] <= '9'))
				|| argv[1][0] == '-' || argv[1][0] <= '+'))
		{
			tab = ft_split(argv[1]);
			if (check_duplicates1(tab, count))
				exit_free(tab);
			//for (int k = 0; k < count; k++)
			//	printf("Element %i before sorting: %i\n", k, tab[k]);
			push_swap(tab, count);
			//for (int b = 0; b < count; b++)
			//	printf("Element %i after sorting: %i\n", b, tab[b]);
			free(tab);
		}
		else
			exit_zero();
		return (0);
	}
	tab = extract((argc), argv);
	for (int k = 0; k < argc - 1; k++)
		printf("1Element %i before sorting: %i\n", k, tab[k]);
	push_swap(tab, (argc - 1));
	for (int b = 0; b < argc - 1; b++)
		printf("Element %i after sorting: %i\n", b, tab[b]);
	free(tab);
	return (0);
}
