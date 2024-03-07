/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laprieur <laprieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/10 14:29:28 by hsebille          #+#    #+#             */
/*   Updated: 2023/06/16 13:18:47 by laprieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env_error_case(char **cmd, int i)
{
	while (cmd[i])
	{
		if (cmd[i][0] == '-')
		{
			ft_putstr_fd("env: ", 2);
			ft_putstr_fd("invalid option '", 2);
			ft_putstr_fd(cmd[i], 2);
			ft_putstr_fd("'\n", 2);
			g_exit_code = 125;
			return (1);
		}
		else
		{
			ft_putstr_fd("env: '", 2);
			ft_putstr_fd(cmd[i], 2);
			ft_putstr_fd("': No such file or directory\n", 2);
			g_exit_code = 127;
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_invalid_var(char *var, char *line)
{
	if (is_var_valid(var) == false)
	{
		g_exit_code = 1;
		ft_putstr_fd("export: '", 2);
		ft_putstr_fd(line, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		free(var);
		return (1);
	}
	return (0);
}

void	set_index(t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp != NULL)
	{
		tmp->index = get_index(env, tmp->var);
		tmp = tmp->next;
	}
}

void	print_export_core(t_env *tmp)
{
	if (tmp->var && tmp->value && tmp->is_value)
		printf("declare -x %s=\"%s\"\n", tmp->var, tmp->value);
	else if (tmp->is_value == 0)
		printf("declare -x %s\n", tmp->var);
}
