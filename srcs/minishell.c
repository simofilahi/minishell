/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 19:53:19 by mfilahi           #+#    #+#             */
/*   Updated: 2019/03/04 09:13:26 by mfilahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	sys_cmd(char **command, char *path_found, t_env *first_node_ref)
{
	int		i;
	char	*temp;
	char	**tab;
	char	*tmp;

	if (ft_strncmp(command[0], "./", 2) != 0)
	{
		temp = ft_strjoin("/", command[0]);
		tab = get_path(first_node_ref);
		i = 0;
		while (tab[i])
		{
			tmp = ft_strdup(temp);
			command[0] = ft_strjoin(tab[i], tmp);
			free(tmp);
			if (access(command[0], F_OK) == 0)
				break ;
			free(command[0]);
			free(tab[i]);
			i++;
		}
		free(temp);
	}
	execute(command, path_found, first_node_ref);
}

void	child_pid(char **command, t_env *first_node_ref)
{
	pid_t	child_pid;
	char	*path_found;

	child_pid = fork();
	if (child_pid == 0)
	{
		path_found = ft_strdup(command[0]);
		if (command[0][0] == '/')
			execute(command, path_found, first_node_ref);
		else
			sys_cmd(command, path_found, first_node_ref);
		free(path_found);
		exit(0);
	}
	else
	{
		g_signal_num = 1;
		wait(NULL);
	}
	g_signal_num = 0;
}

void	minishell(t_env *first_node_ref, char **tmp)
{
	char	**command;
	int		i;
	char	buff[1024];
	char	**argv;
	char	*string;

	while (1)
	{
		string = ft_strjoin(getcwd(buff, sizeof(buff)), " $> ");
		(*tmp) = color(string);
		free(string);
		argv = get_input((*tmp));
		i = -1;
		while (argv[++i])
		{
			command = ft_strsplit(argv[i], ' ');
			minishell_2(command, first_node_ref, tmp);
		}
		i = -1;
		while (argv[++i])
			free(argv[i]);
		free(argv);
		free((*tmp));
	}
}

void	minishell_2(char **command, t_env *head_ref, char **tmp)
{
	int		j;
	int		i;
	char	*temp;

	j = 1;
	temp = NULL;
	if (command[0] == NULL)
		minishell(head_ref, tmp);
	else
	{
		if ((ft_strcmp(command[0], "/bin/echo") == 0) && \
				(ft_strncmp(command[1], "$", 1) == 0))
			builtin_cmds(command, &j, temp, head_ref);
		else if ((j = own_cmds(command[0])))
			builtin_cmds(command, &j, temp, head_ref);
		else
			child_pid(command, head_ref);
	}
	i = -1;
	while (command[++i])
		free(command[i]);
	free(command);
}

int		main(int argc, char **argv, char **envp)
{
	t_env	*first_node;
	char	*tmp;

	g_signal_num = 0;
	signal(SIGINT, signal_handler);
	(void)argc;
	(void)argv;
	first_node = copy_of_env(envp);
	minishell(first_node, &tmp);
	free_list(first_node);
	return (0);
}
