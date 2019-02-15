/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 19:56:52 by mfilahi           #+#    #+#             */
/*   Updated: 2019/02/05 13:06:10 by mfilahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	execute(char **command, char *path_found, t_env *first_node_ref)
{
	char	*newstring;
	char	**env;
	int		i;

	env = get_env(first_node_ref);
	if (execve(command[0], command, env) == -1)
	{
		if (access(command[0], F_OK) == -1)
		{
			newstring = ft_strjoin("command not found: ", path_found);
			ft_putendl_fd(newstring, 2);
		}
		if (access(command[0], F_OK) == 0 && access(command[0], X_OK) != 0)
		{
			newstring = ft_strjoin("permission denied: ", path_found);
			ft_putendl_fd(newstring, 2);
		}
		free(newstring);
	}
	i = -1;
	while (env[++i])
		free(env[i]);
	free(env);
}

char	**get_input(char *str)
{
	char	buff[2];
	char	**tab;
	int		ret;
	char	*line;
	char	*tmp;

	ft_putstr_fd(str, 1);
	line = ft_strnew(1);
	tab = NULL;
	while ((ret = (read(0, buff, 1))))
	{
		buff[ret] = '\0';
		if (ft_strchr(buff, '\n'))
			break ;
		if (!(ft_strchr(buff, '"')))
		{
			tmp = ft_strjoin(line, buff);
			free(line);
			line = tmp;
		}
	}
	manipulate(line);
	tab = ft_strsplit(line, ';');
	free(line);
	return (tab);
}

void	manipulate(char *pstring)
{
	while (*pstring)
	{
		while (*pstring == '\t')
		{
			*pstring = ' ';
			pstring++;
		}
		pstring++;
	}
	*pstring = '\0';
}

char	**get_path(t_env *head_ref)
{
	char	**tab;
	char	*str;
	t_env	*temp;

	temp = head_ref;
	tab = NULL;
	while (temp)
	{
		if (find_path(temp->var))
		{
			str = ft_strsub(temp->var, 5, ft_strlen(temp->var));
			tab = ft_strsplit(str, ':');
			free(str);
			break ;
		}
		temp = temp->next;
	}
	return (tab);
}

void	signal_handler(int sign)
{
	char	buff[1024];
	char	*str;

	ft_putchar_fd('\n', 1);
	if (sign == SIGINT && g_signal_num != 1)
	{
		str = ft_strjoin(getcwd(buff, sizeof(buff)), " $> ");
		str = color(str);
		ft_putstr_fd(str, 1);
	}
}
