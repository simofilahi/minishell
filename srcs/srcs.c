/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   srcs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 20:27:06 by mfilahi           #+#    #+#             */
/*   Updated: 2019/02/04 23:36:15 by mfilahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int		find_path(char *penv)
{
	char	*str;

	str = "PATH";
	if ((ft_strncmp(str, penv, 4)) == 0)
		return (1);
	return (0);
}

void	free_list(t_env *first_node)
{
	t_env	*tmp;
	t_env	*current;

	current = first_node;
	while (current)
	{
		tmp = current;
		current = current->next;
		free(current);
	}
}

char	*color(char *pstr)
{
	char	*tmp;

	tmp = ft_strjoin("\x1b[34m ", pstr);
	pstr = ft_strjoin(tmp, " \x1b[0m");
	free(tmp);
	return (pstr);
}

void	print_error(char **ptrcmd)
{
	ft_putstr_fd(ptrcmd[0], 1);
	ft_putstr_fd(": Too many arguments.\n", 1);
}

void	gestion_error(char *path)
{
	ft_putstr_fd("cd: no such file or directory: ", 1);
	ft_putstr_fd(path, 1);
	ft_putchar_fd('\n', 1);
}
