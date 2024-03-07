/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laprieur <laprieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 14:30:07 by hsebille          #+#    #+#             */
/*   Updated: 2023/06/16 13:19:06 by laprieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_export(t_env *env, int env_size)
{
	t_env	*tmp;
	int		i;
	int		booleen;

	tmp = env;
	i = 0;
	while (tmp != NULL)
	{
		while (i < env_size)
		{
			booleen = 1;
			if (tmp->index == i)
			{
				print_export_core(tmp);
				i++;
				tmp = env;
				booleen = 0;
			}
			if (booleen == 1)
				tmp = tmp->next;
		}
		tmp = tmp->next;
	}
}

static int	export_type_core(t_env *tmp, char *var, char *value, char *line)
{
	if (ft_strncmp(tmp->var, var, ft_strlen(var) + 1) == 0
		&& ft_strncmp(ft_strchr(line, '+'), "+=", 2) != 0)
	{
		free(var);
		if (value[0] != '\0')
			free(value);
		return (REPLACE);
	}
	else if (ft_strncmp(ft_strchr(line, '+'), "+=", 2) == 0
		&& ft_strncmp(tmp->var, var, ft_strlen(var) + 1) == 0)
	{
		if (value[0] != '\0')
			free(value);
		free(var);
		return (EX_APPEND);
	}
	return (-2);
}

int	export_type(t_env *env, char *line)
{
	t_env	*tmp;
	char	*var;
	char	*value;
	int		ret;

	tmp = env;
	var = get_var(line);
	value = get_value(line);
	while (tmp != NULL)
	{
		ret = export_type_core(tmp, var, value, line);
		if (ret == -1)
			return (-1);
		else if (ret >= 0)
			return (ret);
		tmp = tmp->next;
	}
	free(var);
	if (value[0] != '\0')
		free(value);
	if (tmp == NULL)
		return (NEW_VAR);
	return (-1);
}

static int	export_core(t_env *env, char *cmd, char *var, char *value)
{
	if (export_type(env, cmd) == NEW_VAR)
	{
		if (cmd[ft_strlen(cmd) - 1] != '=' && value[0] == '\0')
			env_lstadd_back(&env, env_lstnew(get_var(cmd), \
				get_value(cmd), 0, 0));
		else
			env_lstadd_back(&env, env_lstnew(get_var(cmd), \
				get_value(cmd), 0, 1));
		return (1);
	}
	else if (export_type(env, cmd) == REPLACE)
		replace_var(env, var, value, cmd);
	else if (export_type(env, cmd) == EX_APPEND)
		add_value(env, cmd);
	return (0);
}

void	export(t_env *env, char **cmd, t_program *data)
{
	int		i;
	char	*var;
	char	*value;

	i = 0;
	while (cmd[i + 1] != NULL)
	{
		var = get_var(cmd[i + 1]);
		if (check_invalid_var(var, cmd[i + 1]) == 1)
		{
			i++;
			continue ;
		}
		value = get_value(cmd[i + 1]);
		data->env_size += export_core(env, cmd[i + 1], var, value);
		free(var);
		if (value[0] != '\0')
			free(value);
		i++;
	}
	set_index(env);
	if (i == 0)
		print_export(env, data->env_size);
}
