/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laprieur <laprieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 13:16:48 by hsebille          #+#    #+#             */
/*   Updated: 2023/06/08 16:43:41 by laprieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	first_var(t_env **head, t_env *current, t_program *data, char **cmd)
{
	if (current != NULL && ft_strncmp(current->var, cmd[1],
			ft_strlen(current->var) + 1) == 0)
	{
		*head = current->next;
		data->env_size--;
	}
}

static void	print_error(char *cmd)
{
	if (is_var_valid(cmd) == false)
	{
		g_exit_code = 1;
		ft_putstr_fd("unset: '", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
	}
}

static void	unset_core(t_unset *unset, t_env **head, t_program *data, char *cmd)
{
	if (ft_strncmp(unset->current->var, cmd, \
		ft_strlen(unset->current->var) + 1) == 0)
	{
		g_exit_code = 0;
		free(unset->current->var);
		if (unset->current->value[0])
			free(unset->current->value);
		if (unset->prev != NULL)
			unset->prev->next = unset->current->next;
		else
			*head = unset->current->next;
		unset->to_free = unset->current;
		unset->current = unset->current->next;
		free(unset->to_free);
		data->env_size--;
	}
	else
	{
		unset->prev = unset->current;
		unset->current = unset->current->next;
	}
}

void	unset(t_env **head, t_program *data, char **cmd)
{
	t_unset	unset;
	int		i;

	if (cmd == NULL || cmd[1] == NULL)
		return ;
	unset.current = *head;
	i = 1;
	first_var(head, unset.current, data, cmd);
	while (cmd[i] != NULL)
	{
		print_error(cmd[i]);
		unset.current = *head;
		unset.prev = NULL;
		while (unset.current != NULL)
			unset_core(&unset, head, data, cmd[i]);
		i++;
	}
}
