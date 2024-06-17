/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eaktimur <eaktimur@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 16:07:28 by eaktimur          #+#    #+#             */
/*   Updated: 2024/06/17 17:34:31 by eaktimur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <limits.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>

typedef struct a_list
{
	int				nbr;
	int				index;
	int				push_cost;
	int				median;
	struct a_list	*target_node;
	struct a_list	*next;
	struct a_list	*prev;
}					t_l;

void push_a(t_l **a, t_l **b);
void push_b(t_l **a, t_l **b);
void r(t_l **b, char which);
void rr(t_l **a, t_l **b);
void reverse_rotate(t_l **stack, char which);
void rrr(t_l **a, t_l **b);
void s(t_l **stack, char which);
void ss(t_l **a, t_l **b);
void update_indexes(t_l **a, t_l **b);
void	point_to_first(t_l **list, t_l **list2);
t_l	*find_last_node(t_l *a);


#endif
