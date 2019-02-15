/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 20:31:34 by mfilahi           #+#    #+#             */
/*   Updated: 2019/02/05 12:27:39 by mfilahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int		len_of_list(t_env *head_ref)
{
	int		counter;

	counter = 0;
	while (head_ref)
	{
		head_ref = head_ref->next;
		counter++;
	}
	return (counter);
}

void	print_env(t_env *head_ref)
{
	while (head_ref)
	{
		ft_putendl_fd(head_ref->var, 1);
		head_ref = head_ref->next;
	}
}

char	*get_var(char *deli, t_env *ptrnode)
{
	while (ptrnode)
	{
		if (ft_strncmp(deli, ptrnode->var, ft_strlen(deli)) == 0)
			return (ptrnode->var + ft_strlen(deli));
		ptrnode = ptrnode->next;
	}
	return (NULL);
}

void	swap(t_env *ptr_head, char *path)
{
	t_env	*temp;
	char	*str1;

	temp = ptr_head;
	str1 = get_var("PWD=", temp);
	while (ptr_head)
	{
		if (ft_strncmp("OLDPWD=", ptr_head->var, 7) == 0)
			ptr_head->var = ft_strjoin("OLDPWD=", str1);
		if (ft_strncmp("PWD=", ptr_head->var, 4) == 0)
			ptr_head->var = ft_strjoin("PWD=", path);
		ptr_head = ptr_head->next;
	}
}

t_env	*copy_of_env(char **tab)
{
	t_env	*head;
	int		i;

	i = -1;
	head = NULL;
	while (tab[++i])
		createnode(&head, tab[i]);
	reverse_list(&head);
	return (head);
}
