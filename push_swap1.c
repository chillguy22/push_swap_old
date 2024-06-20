/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaktimur <eaktimur@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 15:24:17 by eaktimur          #+#    #+#             */
/*   Updated: 2024/06/20 15:29:27 by eaktimur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	exit_free_list(t_l *list)
{
	t_l	*tmp;

	while (list)
	{
		tmp = list;
		list = list->next;
		free(tmp);
	}
	exit(0);
}

void	exit_error(void) // good
{
	printf("Error\n");
	exit(0);
}

void	exit_error_free(t_l *stack)
{
	t_l	*tmp;

	printf("Error\n");
	while (stack)
	{
		tmp = stack;
		stack = stack->next;
		free(tmp);
	}
	exit(0);
}

void	free_list(t_l *list)
{
	t_l	*tmp;

	while (list)
	{
		tmp = list;
		list = list->next;
		free(tmp);
	}
}

t_l	*find_last_node(t_l *a)
{
	t_l	*node;

	if (!a)
		return (NULL);
	node = a;
	while (node->next)
		node = node->next;
	return (node);
}

//	stworz kolejnego node do listy

void	populate_a(t_l **a, int n)
{
	t_l	*node;
	t_l	*last_node;

	node = malloc(sizeof(t_l));
	if (!node)
		exit_error();
	node->nbr = n;
	node->next = NULL;
	if (!*a)
	{
		*a = node;
		node->prev = NULL;
	}
	else
	{
		last_node = find_last_node(*a);
		last_node->next = node;
		node->prev = last_node;
	}
}

int	ft_atoi(char *str)
{
	int				i;
	long long int	result;
	int				is_negative;

	i = 0;
	result = 0;
	is_negative = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
		{
			is_negative = -1;
		}
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	if (result > INT_MAX || result < INT_MIN)
		exit_error();
	return ((int)result * is_negative);
}

int	is_num(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	is_sign(char c)
{
	if (c == '+' || c == '-')
		return (1);
	return (0);
}

int	check_doubles(t_l *a, int n)
{
	t_l	*node;

	node = a;
	if (!a)
		return (0);
	while (node)
	{
		if (node->nbr == n)
			exit_error();
		node = node->next;
	}
	return (0);
}

void	ft_split(char **argv, char c, t_l **a)
{
	t_l		*a_list;
	char	*str;
	int		num;
	int		is_num_started;
	int		is_negative;

	a_list = NULL;
	num = 0;
	is_num_started = 0;
	is_negative = 0;
	str = argv[1];
	while (*str)
	{
		if (*str == c)
		{
			if (is_num_started)
			{
				if (is_negative)
					num = -num;
				if (check_doubles(a_list, num))
					exit_error();
				populate_a(&a_list, num);
				is_num_started = 0;
				is_negative = 0;
			}
		}
		else if (is_num(*str) || (*str == '-' && !is_num_started))
		{
			if (!is_num_started)
			{
				is_num_started = 1;
				num = 0;
				if (*str == '-')
				{
					is_negative = 1;
					str++;
					continue ;
				}
			}
			num = num * 10 + (*str - '0');
		}
		else
			exit_error();
		str++;
	}
	if (is_num_started)
	{
		if (is_negative)
			num = -num;
		if (check_doubles(a_list, num))
			exit_error();
		populate_a(&a_list, num);
	}
	*a = a_list;
}

void	update_indexes(t_l **a, t_l **b)
{
	t_l	*current;
	int	index;

	if (a && *a)
	{
		current = *a;
		index = 0;
		while (current)
		{
			current->index = index++;
			current = current->next;
		}
	}
	if (b && *b)
	{
		current = *b;
		index = 0;
		while (current)
		{
			current->index = index++;
			current = current->next;
		}
	}
}

void	print_stack(t_l **stack)
{
	t_l	*current;

	// Check if the stack is empty
	if (!stack || !*stack)
	{
		printf("Stack is empty\n");
		return ;
	}
	// Find the first element where prev is NULL
	current = *stack;
	while (current && current->prev != NULL)
	{
		current = current->next;
	}
	// If no such element is found, the stack is invalid or empty
	if (!current)
	{
		printf("Stack is empty or no node with prev == NULL\n");
		return ;
	}
	// Print the stack starting from the first element
	while (current)
	{
		printf("Value: %d, Index: %d, Push Cost: %d, Median: %d\n",
			current->nbr, current->index, current->push_cost, current->median);
		current = current->next;
	}
}

void	handle_input(char **argv, int argc, t_l **a) // correct
{
	int i;
	int j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j])
		{
			if (!is_num(argv[i][j]) && !is_sign(argv[i][j]))
				exit_error();
			j++;
		}
		if (check_doubles(*a, ft_atoi(argv[i])))
			exit_error();
		populate_a(a, ft_atoi(argv[i]));
		i++;
	}
}

int	stack_size(t_l *a)
{
	t_l	*current;
	int	count;

	if (!a || !a)
		return (0);
	current = a;
	count = 0;
	while (current && current->index != 0)
		current = current->next;
	if (!current)
		return (0);
	while (current)
	{
		count++;
		current = current->next;
	}
	return (count);
}

t_l	*find_highest(t_l *head)
{
	long	highest;
	t_l		*highest_node;
	t_l		*current;

	current = head;
	if (!current)
		return (NULL);
	highest = LONG_MIN;
	while (current)
	{
		if (current->nbr > highest)
		{
			highest = current->nbr;
			highest_node = current;
		}
		current = current->next;
	}
	return (highest_node);
}

int	is_sorted(t_l *a)
{
	t_l	*current;

	if (!a)
		return (1);
	current = a;
	while (current && current->index != 0)
		current = current->next;
	if (!current)
		return (1);
	while (current->next)
	{
		if (current->nbr > current->next->nbr)
			return (0);
		current = current->next;
	}
	return (1);
}

void	two_elem_sort(t_l *a)
{
	t_l	*first;
	t_l	*second;

	first = a;
	second = first->next;
	if (stack_size(a) == 1)
		exit_free_list(a);
	if (stack_size(a) == 2)
	{
		if (first->nbr > second->nbr)
			s(&a, 'a');
	}
	// 	exit_free_list(a);
	// a = first;
	// a->next = a->prev;
	// a->prev = NULL;
	// a->next->next = NULL;
	update_indexes(&a, NULL);
}

void	three_elem_sort(t_l **a)
{
	t_l	*highest;

	highest = find_highest(*a);
	if (*a == highest)
		r(a, 'a');
	else if ((*a)->next == highest)
		reverse_rotate(a, 'a');
	if ((*a)->nbr > (*a)->next->nbr)
		s(a, 'a');
	// 	exit_free_list(a);
}

void	update_targets(t_l **a, t_l **b)
{
	t_l	*b_current;
	t_l	*a_current;
	t_l	*closest;

	b_current = *b;
	while (b_current != NULL)
	{
		closest = NULL;
		a_current = *a;
		while (a_current != NULL)
		{
			if (a_current->nbr > b_current->nbr)
			{
				if (closest == NULL || a_current->nbr < closest->nbr)
				{
					closest = a_current;
				}
			}
			a_current = a_current->next;
		}
		if (closest == NULL)
			closest = find_highest(*a);
		b_current->target_node = closest;
		b_current = b_current->next;
	}
}

void	update_median(t_l **stack)
{
	t_l	*current;
	int	total_nodes;
	int	index;
	int	mid;

	if (stack == NULL || *stack == NULL)
	{
		return ;
	}
	current = *stack;
	total_nodes = stack_size(current);
	while (current != NULL)
	{
		index = current->index;
		mid = total_nodes / 2;
		if (index < mid)
			current->median = 1;
		else
			current->median = -1;
		current = current->next;
	}
}

t_l	*push_cost(t_l **a_node, t_l **b_node)
{
	t_l	*b;
	t_l	*a;
	t_l	*cheapest;
	int	min_cost;
	int	temp;

	b = *b_node;
	cheapest = NULL;
	min_cost = INT_MAX;
	while (b != NULL)
	{
		a = b->target_node;
		b->push_cost = 0;
		temp = a->index + b->index;
		if (b->index + (stack_size(*a_node) - a->index) < temp)
			temp = b->index + (stack_size(*a_node) - a->index);
		if (a->index + (stack_size(*b_node) - b->index) < temp)
			temp = a->index + (stack_size(*b_node) - b->index);
		if ((stack_size(*a_node) - a->index) + (stack_size(*b_node)
				- b->index) < temp)
			temp = (stack_size(*a_node) - a->index) + (stack_size(*b_node)
					- b->index);
		b->push_cost = temp;
		if (b->push_cost < min_cost)
		{
			min_cost = b->push_cost;
			cheapest = b;
		}
		b = b->next;
	}
	return (cheapest);
}

void	execute_operations(t_l **a, t_l **b, t_l *to_push)
{
	t_l	*target;

	target = to_push->target_node;
	while (to_push->index > 0 && target->index > 0)
	{
		if (to_push->median == 1 && target->median == 1)
			rr(a, b);
		else if (to_push->median == -1 && target->median == -1)
			rrr(a, b);
		else
			// if ((to_push->median == -1 && target->median == 1) && (to_push->index < target->index + (stack_size(*b) - to_push->index)))
			// 	while (to_push->index > 0 && target->index > 0)
			// 		rr(a, b);
			// else if ((to_push->median == 1 && target->median == -1) && (target->index < to_push->index + (stack_size(*a) - target->index)))
			// 	while (to_push->index > 0 && target->index > 0)
			// 		rr(a, b);
			break ;
	}
	if (target->index != 0 && to_push->index != 0)
	{
		if (target->index > to_push->index)
		{
			if (target->index < to_push->push_cost)
			{
				while (to_push->index > 0)
					rr(a, b);
			}
		}
		if (to_push->index > target->index)
		{
			if (to_push->index < to_push->push_cost)
			{
				while (target->index > 0)
					rr(a, b);
			}
		}
		if (stack_size(*a) - target->index > stack_size(*b) - to_push->index)
		{
			if (stack_size(*a) - target->index < to_push->push_cost)
			{
				while (to_push->index > 0)
					rrr(a, b);
			}
		}
		if (stack_size(*b) - to_push->index > stack_size(*a) - target->index)
		{
			if (stack_size(*b) - to_push->index < to_push->push_cost)
			{
				while (target->index > 0)
					rrr(a, b);
			}
		}
	}
	while (to_push->index > 0)
	{
		if (to_push->median == 1)
			r(b, 'b');
		else if (to_push->median == -1)
			reverse_rotate(b, 'b');
	}
	while (target->index > 0)
	{
		if (target->median == 1)
			r(a, 'a');
		else if (target->median == -1)
			reverse_rotate(a, 'a');
	}
}

int	find_lowest(t_l **stack)
{
	t_l	*lowest;
	t_l	*current;

	lowest = *stack;
	current = *stack;
	while (current != NULL)
	{
		if (current->nbr < lowest->nbr)
			lowest = current;
		current = current->next;
	}
	return (lowest->index);
}

int	find_lowest2(t_l **stack)
{
	t_l	*lowest;
	t_l	*current;

	lowest = *stack;
	current = *stack;
	while (current != NULL)
	{
		if (current->nbr < lowest->nbr)
			lowest = current;
		current = current->next;
	}
	return (lowest->median);
}

void	final_rotate(t_l **a)
{
	int	index;
	int	median;
	int	i;

	index = find_lowest(a);
	median = find_lowest2(a);
	i = 0;
	if (median == -1)
	{
		while(i < (stack_size(*a) - index))
		{
			reverse_rotate(a, 'a');
			i++;
		}
	}
	else if (median == 1)
	{
		while(i < index)
		{
			r(a, 'a');
			i++;
		}
	}
}

void	actual_push_swap(t_l **a, t_l **b)
{
	t_l	*to_push;

	while (stack_size(*a) >= 3)
	{
		if (stack_size(*a) > 3)
		{
			if (*a == find_highest(*a))
				r(a, 'a');
			push_b(a, b);
		}
		else
		{
			three_elem_sort(a);
			while (stack_size(*b) > 0)
			{
				// update_targets(a, b);
				// printf("stack size b: %i\n", stack_size(*b));
				// for (int i = 0; i < stack_size(*b); i++)
				// 	printf("Target #%i: %i\n", i, (*b)->target_node->nbr);
				// // print_stack(&b);
				// break ;
				// // push_swap(&b, &a);
				//
				// next steps: assign a targets to b nodes,calc costs and find cheapest push_a(&a,	&b);
				update_indexes(a, b);
				update_targets(a, b);
				to_push = push_cost(a, b); //
				update_median(a);
				update_median(b);
				execute_operations(a, b, to_push); //
				push_a(a, b);
			}
			// break ;
		}
		if (stack_size(*b) == 0)
			break ;
	}
	update_median(a);
	final_rotate(a);
	// if (stack_size(*b) == 0 && is_sorted(*a))
	// 	printf("Sorted");
}

void	sizebased_operation(t_l **a, t_l **b)
{
	if (is_sorted(*a))
		exit_free_list(*a);
	if (stack_size(*a) == 2)
		two_elem_sort(*a);
	else if (stack_size(*a) == 3)
		three_elem_sort(a);
	else
		actual_push_swap(a, b);
	// point_to_first(a, b);
}

int	main(int argc, char **argv)
{
	t_l	*a;
	t_l	*b;

	a = NULL;
	b = NULL;
	if (argc == 1 || (argc == 2 && !argv[1][0]))
		return (1);
	if (argc == 2)
		ft_split(argv, ' ', &a);
	else if (argc > 2)
		handle_input(argv, argc, &a);
	update_indexes(&a, &b);
	// printf("\nbefore:\n a:\n");
	// print_stack(&a);
	// printf("\nb:\n");
	// print_stack(&b);
	sizebased_operation(&a, &b);
	// point_to_first(&a, &b);
//	printf("\nafter:\n a:\n");
//	print_stack(&a);
//	printf("\nb:\n");
//	print_stack(&b);
	exit_free_list(a);
	return (0);
}
