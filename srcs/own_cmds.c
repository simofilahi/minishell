/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   own_cmds.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 18:55:56 by mfilahi           #+#    #+#             */
/*   Updated: 2019/02/05 13:06:22 by mfilahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	change_dir_3(char *path, t_env *head_ref)
{
	char	buff[1024];

	if (access(path, X_OK) == 0)
	{
		chdir(path);
		swap(head_ref, getcwd(buff, sizeof(buff)));
	}
	else
	{
		path = ft_strjoin("cd: permission denied: ", path);
		ft_putendl_fd(path, 1);
	}
}

void	change_dir_2(char *path, t_env *head_ref, t_env *temp)
{
	char	buff[1024];
	char	*tmp;

	tmp = ft_strsub(path, 1, ft_strlen(path));
	path = ft_strjoin(get_var("HOME=", temp), tmp);
	free(tmp);
	if (access(path, F_OK) == 0)
	{
		chdir(path);
		swap(head_ref, getcwd(buff, sizeof(buff)));
	}
	else
		gestion_error(path);
	free(path);
}

void	change_dir(char **path, t_env *first_node_head)
{
	t_env	*temp;
	char	buff[1024];
	char	*pwd;

	temp = first_node_head;
	if (path[1] == NULL)
	{
		pwd = ft_strdup(get_var("HOME=", temp));
		chdir(get_var("HOME=", temp));
		swap(first_node_head, getcwd(buff, sizeof(buff)));
	}
	else if ((ft_strncmp(path[1], "~/", 2) == 0) ||
			((ft_strncmp(path[1], "~", 1) == 0) && path[2] == NULL))
		change_dir_2(path[1], first_node_head, temp);
	else if (ft_strcmp("-", path[1]) == 0)
	{
		pwd = ft_strdup(get_var("OLDPWD=", temp));
		chdir(get_var("OLDPWD=", temp));
		swap(first_node_head, getcwd(buff, sizeof(buff)));
	}
	else if (access(path[1], F_OK) == 0)
		change_dir_3(path[1], first_node_head);
	else
		gestion_error(path[1]);
}

void	echo_cmd_2(char **command, t_env *head_ref, int i)
{
	t_env	*temp;
	char	*tmp;

	command[i] = ft_strsub(command[i], 1, ft_strlen(command[i]));
	temp = head_ref;
	while (temp)
	{
		if ((ft_strncmp(command[i], temp->var, ft_strlen(command[i]))) == 0)
		{
			tmp = ft_strsub(temp->var, ft_strlen(command[i]) + 1, \
					ft_strlen(temp->var));
			ft_putstr_fd(tmp, 1);
			free(tmp);
			break ;
		}
		temp = temp->next;
	}
}

void	echo_cmd(char **command, t_env *first_node_ref)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (command[++i])
	{
		if ((command[i][0] != '$') && (ft_strcmp("-n", command[i]) != 0))
			ft_putstr_fd(command[i], 1);
		else if ((ft_strcmp("-n", command[1]) == 0) && command[i + 1] != NULL)
		{
			ft_putstr_fd(command[i + 1], 1);
			j = 1;
			i++;
		}
		else if (command[i][0] == '$')
			echo_cmd_2(command, first_node_ref, i);
		if (command[i + 1] != NULL)
			ft_putchar_fd(' ', 1);
	}
	if (j == 0)
		ft_putchar_fd('\n', 1);
}
