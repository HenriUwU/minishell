/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils_bis.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsebille <hsebille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 14:57:15 by laprieur          #+#    #+#             */
/*   Updated: 2023/06/15 10:59:43 by hsebille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	replace_var(t_env *env, char *var, char *value, char *line)
{
	if (line[ft_strlen(line) - 1] != '=' && value[0] == '\0')
		return (1);
	while (env != NULL)
	{
		if (ft_strncmp(env->var, var, ft_strlen(var) + 1) == 0)
		{
			env->is_value = 1;
			if (value[0] == '\0')
			{
				if (env->value[0] != '\0')
					free(env->value);
				env->value = "\0";
			}
			else
			{
				if (env->value[0] != '\0')
					free(env->value);
				env->value = ft_strdup(value);
			}
			return (1);
		}
		env = env->next;
	}
	return (0);
}

static int	process_list(t_env *env, char *line, char *var, char *value)
{
	var = get_var(line);
	value = get_value(line);
	while (env != NULL)
	{
		if (ft_strncmp(env->var, var, ft_strlen(var) + 1) == 0)
		{
			env->is_value = 1;
			if (env->value[0] == '\0' && value[0] != '\0')
				env->value = ft_strdup(value);
			else if (value[0] != '\0')
				env->value = ft_strjoin(env->value, (value));
			free(var);
			if (value[0] != '\0')
				free(value);
			return (1);
		}
		env = env->next;
	}
	free(var);
	if (value[0] != '\0')
		free(value);
	return (0);
}

int	add_value(t_env *env, char *line)
{
	int		i;
	char	*var;
	char	*value;

	i = 0;
	var = NULL;
	value = NULL;
	while (line[i] != '\0' && ft_strlen(line) >= 4)
	{
		if (line[i] == '+' && line[i + 1] == '=')
			if (process_list(env, line, var, value) == 1)
				return (1);
		i++;
	}
	return (0);
}

bool	is_var_valid(char *var)
{
	int	i;

	if (var == NULL)
		return (false);
	i = 0;
	if (ft_isalpha(var[0]) == 0 && var[0] != '_')
		return (false);
	while (var[i] != '\0')
	{
		if (ft_isalnum(var[i]) == 0 && var[i] != '_')
			return (false);
		i++;
	}
	return (true);
}

int	get_index(t_env *env, char *var)
{
	t_env	*tmp;
	int		index;
	int		i;

	tmp = env;
	i = 0;
	index = 0;
	while (i < env_lstsize(env))
	{
		if (ft_strncmp(var, tmp->var, ft_strlen(var)) > 0)
			index++;
		tmp = tmp->next;
		i++;
	}
	return (index);
}
