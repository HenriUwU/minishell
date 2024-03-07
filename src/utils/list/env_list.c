/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsebille <hsebille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 10:00:35 by laprieur          #+#    #+#             */
/*   Updated: 2023/06/13 11:07:04 by hsebille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*env_lstnew(char *var, char *value, int index, int is_value)
{
	t_env	*new;

	if (var == NULL || value == NULL)
		return (NULL);
	new = ft_calloc(sizeof(t_env), 1);
	if (new == NULL)
		return (NULL);
	new->var = var;
	new->value = value;
	new->index = index;
	new->is_value = is_value;
	new->next = NULL;
	return (new);
}

t_env	*env_lstlast(t_env *env)
{
	if (env == NULL)
		return (NULL);
	while (env->next != NULL)
		env = env->next;
	return (env);
}

void	env_lstadd_back(t_env **env, t_env *new)
{
	t_env	*tmp;

	if (new == NULL)
		return ;
	if (*env == NULL)
		*env = new;
	else
	{
		tmp = env_lstlast(*env);
		tmp->next = new;
	}
}

int	env_lstsize(t_env *env)
{
	int	i;

	if (env == NULL)
		return (-1);
	i = 0;
	while (env != NULL)
	{
		i++;
		env = env->next;
	}
	return (i);
}

void	free_list_env(t_env *lst)
{
	t_env	*tmp;

	while (lst != NULL)
	{
		tmp = lst;
		free(lst->var);
		lst->var = NULL;
		if (lst->value[0] != '\0')
		{
			free(lst->value);
			lst->value = NULL;
		}
		lst = lst->next;
		free(tmp);
	}
}
