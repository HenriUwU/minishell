/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laprieur <laprieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 14:00:56 by hsebille          #+#    #+#             */
/*   Updated: 2023/06/13 16:11:02 by laprieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*reset_var(char *var, char *line)
{
	char	*new_var;
	int		i;

	i = ft_strlen(var) - 1;
	if (i > 0 && var[i] == '+' && line[i + 1] == '=')
	{
		new_var = ft_substr(var, 0, i);
		free(var);
	}
	else
		return (var);
	return (new_var);
}

char	*get_var(char *line)
{
	int		i;
	char	*var;

	if (line == NULL)
		return (NULL);
	i = 0;
	while (line[i] != '=' && line[i] != '\0')
		i++;
	var = ft_calloc(sizeof(char), i + 1);
	if (var == NULL)
		return (NULL);
	i = 0;
	while (line[i] != '=' && line[i] != '\0')
	{
		var[i] = line[i];
		i++;
	}
	var = reset_var(var, line);
	return (var);
}

char	*get_value(char *line)
{
	int		i;
	int		j;
	char	*value;

	i = 0;
	while (line[i] != '\0' && line[i] != '=')
		i++;
	if (line[i] != '\0')
		i++;
	j = i;
	while (line[i] != '\0')
		i++;
	if (j == i)
		return ("\0");
	value = ft_calloc(sizeof(char), i - j + 1);
	i = 0;
	while (line[j] != '\0')
	{
		value[i] = line[j];
		i++;
		j++;
	}
	return (value);
}

t_env	*get_env(char **envp, t_program *data)
{
	t_env	*env;
	char	*var;
	char	*value;
	int		i;

	env = NULL;
	i = 0;
	while (envp[i])
	{
		var = get_var(envp[i]);
		value = get_value(envp[i]);
		if (var == NULL || value == NULL)
			return (NULL);
		env_lstadd_back(&env, env_lstnew(var, value, 0, 1));
		i++;
	}
	data->env_size = env_lstsize(env);
	return (env);
}

void	env(t_env *env, char **cmd)
{
	int	i;

	i = 1;
	if (env_error_case(cmd, i) == 1)
		return ;
	if (env == NULL)
		return ;
	while (env != NULL)
	{
		if (env->var && env->value && env->value[0] != '\0')
			printf("%s=%s\n", env->var, env->value);
		else if (env->var && env->value && env->is_value)
			printf("%s=\n", env->var);
		env = env->next;
	}
	g_exit_code = 0;
}
