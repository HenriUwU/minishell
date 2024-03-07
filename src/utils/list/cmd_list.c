/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laprieur <laprieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 18:34:31 by laprieur          #+#    #+#             */
/*   Updated: 2023/06/14 14:05:06 by laprieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*cmd_lstnew(void)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (new == NULL)
		return (NULL);
	new->cmd = NULL;
	new->cmd_path = NULL;
	new->infile = NULL;
	new->outfile = NULL;
	new->input = -42;
	new->output = -42;
	new->heredoc = -42;
	new->pid = -1;
	new->index = -1;
	new->next = NULL;
	return (new);
}

t_cmd	*cmd_lstlast(t_cmd *lst)
{
	if (lst != NULL)
	{
		while (lst->next != NULL)
		{
			lst = lst->next;
		}
		return (lst);
	}
	return (NULL);
}

void	cmd_lstadd_back(t_cmd **cmd, t_cmd *new)
{
	t_cmd	*tmp;

	if (new == NULL)
		return ;
	if (*cmd == NULL)
		*cmd = new;
	else
	{
		tmp = cmd_lstlast(*cmd);
		tmp->next = new;
	}
}

void	free_list_cmd(t_cmd *lst)
{
	t_cmd	*tmp;

	while (lst != NULL)
	{
		tmp = lst;
		lst = lst->next;
		ft_free_taboftab(tmp->cmd);
		free(tmp->infile);
		tmp->infile = NULL;
		free(tmp->outfile);
		tmp->outfile = NULL;
		free(tmp->cmd_path);
		tmp->cmd_path = NULL;
		free(tmp);
	}
}
