/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaktimur <eaktimur@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 16:04:15 by eaktimur          #+#    #+#             */
/*   Updated: 2024/05/22 17:20:21 by eaktimur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

void	swap(int *array, int length)
{
	int	temp;

	if (length > 1)
	{
		temp = array[0];
		array[0] = array[1];
		array[1] = temp;
	}
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

void	rotate(int *arr, int length)
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
}

void	reverse_rotate(int *arr, int length)
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
}

void	print_array(const char *name, const int *arr, int length)
{
	printf("%s: ", name);
	for (int i = 0; i < length; i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
}

int main() {
    int arr1[] = {1, 2, 3, 4, 5};
    int arr2[] = {10, 20, 30, 40, 50};
    int len1 = sizeof(arr1) / sizeof(arr1[0]);
    int len2 = sizeof(arr2) / sizeof(arr2[0]);
	
	printf("\n");
    printf("Testing swap:\n");
    print_array("Before swap", arr1, len1);
    swap(arr1, len1);
    print_array("After swap", arr1, len1);

    printf("\nTesting push:\n");
    int a[] = {6, 7, 8, 9};
    int b[] = {1, 2, 3, 4, 5};
    int len_a = sizeof(a) / sizeof(a[0]);
    int len_b = sizeof(b) / sizeof(b[0]);

    print_array("Before push, a", a, len_a);
    print_array("Before push, b", b, len_b);
    push(a, &len_a, b, &len_b);
    print_array("After push, a", a, len_a);
    print_array("After push, b", b, len_b);

    printf("\nTesting rotate:\n");
    print_array("Before rotate", arr2, len2);
    rotate(arr2, len2);
    print_array("After rotate", arr2, len2);

    printf("\nTesting reverse_rotate:\n");
    print_array("Before reverse_rotate", arr2, len2);
    reverse_rotate(arr2, len2);
    print_array("After reverse_rotate", arr2, len2);
	printf("\n");

    return 0;
}
