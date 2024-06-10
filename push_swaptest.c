/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swaptest.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaktimur <eaktimur@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/18 20:19:07 by eaktimur          #+#    #+#             */
/*   Updated: 2024/06/10 17:51:36 by eaktimur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

void	free_two(int *a, int *b)
{
	free(a);
	free(b);
}

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

void	exit_free3(int *a, int *b, int *c)
{
	free(a);
	free(b);
	free(c);
	printf("Error\n");
	exit(0);
}

void	exit_free4(int *a, int *b, int *c, int *d)
{
	free(a);
	free(b);
	free(c);
	free(d);
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

	i = *len_b;
	if (*len_a == 0)
		return ;
	while (i > 0)
	{
		b[i] = b[i - 1];
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

long	find_closest_index(int a_elem, int *b, int length_b)
{
	long	diff;
	long	difftemp;
	long	j;
	long	temp;

	temp = 0;
	diff = LONG_MAX;
	j = 0;
	while (j < length_b)
	{
		if (a_elem > b[j])
		{
			difftemp = a_elem - b[j];
			if (difftemp < diff)
			{
				diff = difftemp;
				temp = j;
			}
		}
		j++;
	}
	if (diff == LONG_MAX)
		temp = find_big_index(b, length_b);
	return (temp);
}

void	assign_targets(int *targets, int *a, int *b, int *lengths)
{
	long	i;

	i = 0;
	while (i < lengths[0])
	{
		targets[i] = find_closest_index(a[i], b, lengths[1]);
		i++;
	}
}

int	*rotations_to_bring_to_top(int i, int len)
{
	int	*result;
	int	rotations_up;
	int	rotations_down;

	result = (int *)malloc(2 * sizeof(int));
	if (result == NULL)
	{
		write(1, "Failed to allocate memory", 25);
		exit(EXIT_FAILURE);
	}
	rotations_up = i;
	rotations_down = len - i;
	if (rotations_up <= rotations_down)
	{
		result[0] = 1;
		result[1] = rotations_up;
	}
	else
	{
		result[0] = -1;
		result[1] = rotations_down;
	}
	return (result);
}

void	process_case1(int *result, int *a, int *b, int *lengths)
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

void	process_case2(int *result, int *a, int *b, int *lengths)
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

void	process_case3(int *result, int *a, int *b, int *lengths)
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

void	process_case4(int *result, int *a, int *b, int *lengths)
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

void	process(int *result, int *a, int *b, int *lengths)
{
	if (result[0] == result[2] && result[0] == 1)
		process_case1(result, a, b, lengths);
	else if (result[0] == result[2] && result[0] == -1)
		process_case2(result, a, b, lengths);
	else if (result[0] != result[2] && result[0] == 1)
		process_case3(result, a, b, lengths);
	else if (result[0] != result[2] && result[0] == -1)
		process_case4(result, a, b, lengths);
	push(a, &lengths[0], b, &lengths[1]);
	write(1, "pb\n", 3);
}

int	process_case11(int a_index, int b_index, int a_len, int b_len)
{
	int	cost;

	cost = 0;
	while (a_index != 0 && b_index != 0)
	{
		cost++;
		a_index--;
		b_index--;
	}
	while (a_index != 0)
	{
		cost++;
		a_index--;
	}
	while (b_index != 0)
	{
		cost++;
		b_index--;
	}
	return (cost);
}

int	process_case22(int a_index, int b_index, int a_len, int b_len)
{
	int	cost;

	cost = 0;
	while (a_index != a_len && b_index != b_len)
	{
		cost++;
		a_index++;
		b_index++;
	}
	while (a_index != a_len)
	{
		cost++;
		a_index++;
	}
	while (b_index != b_len)
	{
		cost++;
		b_index++;
	}
	return (cost);
}

int	process_case33(int a_index, int b_index, int a_len, int b_len)
{
	int	cost;

	cost = 0;
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
	return (cost);
}

int	process_case44(int a_index, int b_index, int a_len, int b_len)
{
	int	cost;

	cost = 0;
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
	return (cost);
}

int	cases(int *a, int *b, int *lengths, int **temp)
{
	int	a_direction;
	int	b_direction;
	int	a_index;
	int	b_index;
	int	cost;

	a_direction = temp[0][0];
	b_direction = temp[1][0];
	a_index = temp[0][1];
	b_index = temp[1][1];
	if (a_direction == b_direction && b_direction == 1)
		cost = process_case11(a_index, b_index, lengths[0], lengths[0]);
	else if (a_direction == b_direction && b_direction == -1)
		cost = process_case22(a_index, b_index, lengths[0], lengths[0]);
	else if (a_direction != b_direction && a_direction == 1)
		cost = process_case33(a_index, b_index, lengths[0], lengths[0]);
	else if (a_direction != b_direction && a_direction == -1)
		cost = process_case44(a_index, b_index, lengths[0], lengths[0]);
	return (cost);
}

int	**create2d(int *a, int *b, int *lengths, int *targets)
{
	int	**combined;

	combined = malloc(4 * sizeof(int *));
	if (combined == NULL)
		return (NULL);
	combined[0] = a;
	combined[1] = b;
	combined[2] = lengths;
	combined[3] = targets;
	return (combined);
}

int	*do_stuff(int *result, int **temp, int **combined)
{
	int	i;
	int	cost;

	cost = INT_MAX;
	i = 0;
	while (i < combined[2][0])
	{
		temp[0] = rotations_to_bring_to_top(i, combined[2][0]);
		temp[1] = rotations_to_bring_to_top(*combined[3], combined[2][1]);
		if (cases(combined[0], combined[1], combined[2], temp) < cost)
		{
			cost = cases(combined[0], combined[1], combined[2], temp);
			result[0] = temp[0][0];
			result[2] = temp[1][0];
			result[1] = i;
			result[3] = combined[3][i];
		}
		free(temp[0]);
		free(temp[1]);
		i++;
	}
	return (result);
}

int	*find_cheapest(int *a, int *b, int *lengths, int *targets)
{
	int	*result;
	int	**temp;
	int	**combined;

	temp = (int **)malloc(2 * sizeof(int *));
	if (temp == NULL)
		exit_free4(a, b, lengths, targets);
	result = (int *)malloc(sizeof(int) * 4);
	if (!result)
	{
		free(temp);
		exit_free4(a, b, lengths, targets);
	}
	combined = create2d(a, b, lengths, targets);
	if (combined == NULL)
	{
		free(result);
		free(temp);
		exit_free4(a, b, lengths, targets);
	}
	do_stuff(result, temp, combined);
	free(combined);
	free(temp);
	return (result);
}

void	push_and_write(int *a, int *len_a, int *b, int *len_b)
{
	push(b, len_b, a, len_a);
	write(1, "pa\n", 3);
}

void	rotate_to_temp_index(int *a, int *len_a, int temp_index)
{
	while (temp_index > 0)
	{
		rotate(a, *len_a, 'a');
		temp_index--;
	}
}

void	reverse_rotate_to_temp_index(int *a, int *len_a, int temp_index)
{
	while (temp_index < *len_a)
	{
		reverse_rotate(a, *len_a, 'a');
		temp_index++;
	}
}

void	sort_until_b_empty(int *a, int *len_a, int *b, int *len_b)
{
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
		if (temp_index <= *len_a / 2)
			rotate_to_temp_index(a, len_a, temp_index);
		else if (temp_index > *len_a / 2)
			reverse_rotate_to_temp_index(a, len_a, temp_index);
		push_and_write(a, len_a, b, len_b);
	}
}

void	sort_rest_of_a(int *a, int *len_a)
{
	int	temp_index;

	temp_index = find_smallest_index(a, *len_a);
	if (temp_index < *len_a / 2)
		rotate_to_temp_index(a, len_a, temp_index);
	else if (temp_index >= *len_a / 2)
		reverse_rotate_to_temp_index(a, len_a, temp_index);
}

void	sort11(int *a, int *len_a, int *b, int *len_b)
{
	sort_until_b_empty(a, len_a, b, len_b);
	sort_rest_of_a(a, len_a);
}

void	process_remaining111(int *a, int *len_a, int *b, int *len_b)
{
	int	*targets;
	int	*lengths;
	int	*result;
	int	i;

	lengths = (int *)malloc(sizeof(int) * 2);
	lengths[0] = *len_a;
	lengths[1] = *len_b;
	i = 0;
	while (lengths[0] != 3)
	{
		targets = (int *)malloc(sizeof(int) * (*len_a));
		if (!targets)
			exit_free2(a, b);
		assign_targets(targets, a, b, lengths);
		result = find_cheapest(a, b, lengths, targets);
		if (!result)
			exit_free4(a, b, lengths, targets);
		process(result, a, b, lengths);
		*len_a = lengths[0];
		free_two(targets, result);
	}
	*len_a = lengths[0];
	*len_b = lengths[1];
	free(lengths);
}

void	sort1(int *a, int *len_a, int *b, int *len_b)
{
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
		process_remaining111(a, len_a, b, len_b);
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
	free(b);
	return (a);
}

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
			push_swap(tab, count);
			free(tab);
		}
		return (0);
	}
	tab = extract((argc), argv);
	push_swap(tab, (argc - 1));
	free(tab);
	return (0);
}
