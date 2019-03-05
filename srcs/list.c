/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 18:59:55 by mfilahi           #+#    #+#             */
/*   Updated: 2019/03/03 17:51:34 by mfilahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	reverse_list(t_env **head_ref)
{
	t_env	*prev;
	t_env	*current;
	t_env	*next;

	prev = NULL;
	next = NULL;
	current = (*head_ref);
	while (current != NULL)
	{
		next = current->next;
		current->next = prev;
		prev = current;
		current = next;
	}
	*head_ref = prev;
}

void	createnode(t_env **head_ref, char *var)
{
	t_env	*new_node;

	if (!(new_node = malloc(sizeof(t_env))))
		return ;
	new_node->var = ft_strdup(var);
	new_node->next = (*head_ref);
	(*head_ref) = new_node;
}

char	**get_env(t_env *head_ref)
{
	char	**tab;
	int		i;

	if (!(tab = (char **)malloc(sizeof(char *) * len_of_list(head_ref) + 1)))
		return (NULL);
	i = 0;
	while (head_ref)
	{
		tab[i] = ft_strdup(head_ref->var);
		head_ref = head_ref->next;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

void	delete_node(t_env *head_ref, char *str)
{
	t_env	*temp;
	t_env	*prev;

	temp = head_ref;
	if (str != NULL)
	{
		while ((temp != NULL) &&
				(ft_strncmp(str, temp->var, ft_strlen(str)) != 0))
		{
			prev = temp;
			temp = temp->next;
		}
		if (temp == NULL)
			return ;
		prev->next = temp->next;
		free(temp->var);
		free(temp);
	}
}

void	append(t_env *head_ref, char *ptrcmd, char *str)
{
	t_env	*new_node;
	t_env	*temp;
	t_env	*current;

	temp = head_ref;
	delete_node(temp, ptrcmd);
	current = head_ref;
	if (!(new_node = malloc(sizeof(t_env))))
		return ;
	new_node->var = ft_strdup(str);
	new_node->next = NULL;
	while (current->next)
		current = current->next;
	current->next = new_node;
}
