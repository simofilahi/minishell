/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 18:50:38 by mfilahi           #+#    #+#             */
/*   Updated: 2019/02/05 13:12:57 by mfilahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int		cmd_is_found(char **tab, char **ptrcmd, char *temp)
{
	int		i;

	i = 0;
	while (tab[i])
	{
		(*ptrcmd) = ft_strdup(temp);
		(*ptrcmd) = ft_strjoin(tab[i], (*ptrcmd));
		if (access((*ptrcmd), F_OK) == 0)
			return (1);
		i++;
	}
	return (0);
}

void	which_cmd(char **command, t_env *first_node_ref)
{
	char	*temp;
	char	*cmd;
	char	**tab;
	int		j;

	tab = get_path(first_node_ref);
	j = 1;
	while (command[j])
	{
		cmd = ft_strdup(command[j]);
		cmd = ft_strjoin(cmd, " not found");
		temp = ft_strjoin("/", command[j]);
		if (cmd_is_found(tab, &command[j], temp))
			ft_putendl_fd(command[j], 1);
		else
			ft_putendl_fd(cmd, 2);
		j++;
	}
}

void	builtin_cmds_2(char **ptrcmd, int *j, t_env *head_ref)
{
	int		i;

	if (*j == 4)
	{
		i = 1;
		while (ptrcmd[i])
			delete_node(head_ref, ptrcmd[i++]);
	}
	else if (*j == 5)
		print_env(head_ref);
	else if (*j == 6)
		which_cmd(ptrcmd, head_ref);
	else
	{
		free_list(head_ref);
		exit(0);
	}
}

void	builtin_cmds(char **ptrcmd, int *j, char *tmp, t_env *first_node_head)
{
	if (*j == 1)
		echo_cmd(ptrcmd, first_node_head);
	else if (*j == 2)
		change_dir(ptrcmd, first_node_head);
	else if (*j == 3)
	{
		if (ptrcmd[1] == NULL)
			print_env(first_node_head);
		else if (ptrcmd[2] == NULL)
		{
			tmp = ft_trim(ptrcmd[1], '=');
			append(first_node_head, tmp, ptrcmd[1]);
			free(tmp);
		}
		else if (ptrcmd[3] == NULL)
		{
			ptrcmd[1] = ft_strjoin(ptrcmd[1], "=");
			append(first_node_head, ptrcmd[1],
					ft_strjoin(ptrcmd[1], ptrcmd[2]));
		}
		else
			print_error(ptrcmd);
	}
	else
		builtin_cmds_2(ptrcmd, j, first_node_head);
}

int		own_cmds(char *ptab)
{
	char	*list_of_cmd[9];
	int		i;

	list_of_cmd[1] = "echo";
	list_of_cmd[2] = "cd";
	list_of_cmd[3] = "setenv";
	list_of_cmd[4] = "unsetenv";
	list_of_cmd[5] = "env";
	list_of_cmd[6] = "which";
	list_of_cmd[7] = "exit";
	list_of_cmd[8] = NULL;
	i = 1;
	while (list_of_cmd[i])
	{
		if ((ft_strcmp(ptab, list_of_cmd[i]) == 0))
			return (i);
		i++;
	}
	return (0);
}
