/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilahi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/04 21:51:41 by mfilahi           #+#    #+#             */
/*   Updated: 2019/02/05 14:01:32 by mfilahi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <signal.h>

int				g_signal_num;

typedef struct	s_env
{
	char			*var;
	struct s_env	*next;
}				t_env;

void			minishell_2(char **command, t_env *head_ref, char **tmp);
void			minishell(t_env *first_node_ref, char **tmp);
void			child_pid(char **command, t_env *first_node_ref);
void			sys_cmd(char **command, char *path_found,
				t_env *first_node_ref);
void			execute(char **command, char *path_found,
				t_env *first_node_ref);
char			**get_env(t_env *head_ref);
int				len_of_list(t_env *head_ref);
void			builtin_cmds(char **ptrcmd, int *j, char *tmp,
				t_env *first_node_head);
void			builtin_cmds_2(char **ptrcmd, int *j, t_env *head_ref);
void			which_cmd(char **command, t_env *first_node_ref);
int				cmd_is_found(char **tab, char **ptrcmd, char *temp);
void			print_error(char **ptrcmd);
int				own_cmds(char *ptab);
void			delete_node(t_env *head_ref, char *str);
void			append(t_env *head_ref, char *ptrcmd, char *str);
void			echo_cmd(char **command, t_env *first_node_ref);
void			echo_cmd_2(char **command, t_env *head_ref, int i);
void			change_dir(char **path, t_env *first_node_head);
void			change_dir_2(char *path, t_env *head_ref, t_env *temp);
void			change_dir_3(char *path, t_env *head_ref);
void			gestion_error(char *path);
void			swap(t_env *ptr_head, char *path);
char			*get_var(char *deli, t_env *ptrnode);
char			**get_input(char *str);
void			manipulate(char *pstring);
void			print_env(t_env *head_ref);
t_env			*copy_of_env(char **tab);
void			createnode(t_env **head_ref, char *var);
void			reverse_list(t_env **head_ref);
char			**get_path(t_env *head_ref);
int				find_path(char *penv);
void			signal_handler(int sign);
char			*color(char *pstr);
void			free_list(t_env *first_node);

#endif
