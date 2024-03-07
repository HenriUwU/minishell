/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laprieur <laprieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 10:44:15 by hsebille          #+#    #+#             */
/*   Updated: 2023/06/13 13:03:47 by laprieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_error(char *str)
{
	g_exit_code = 2;
	ft_putstr_fd("exit: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": numeric argument required\n", 2);
}

void	mini_exit(t_env *env, t_cmd *cmd, t_cmd *all_cmd)
{
	if (cmd->cmd[1] == NULL)
	{
		free_all(env, all_cmd);
		exit(g_exit_code);
	}
	else if (ft_strncmp(cmd->cmd[1], "0", 2) != 0
		&& ft_strncmp(cmd->cmd[1], "-9223372036854775808", 21) != 0
		&& ft_atol(cmd->cmd[1]) == 0)
		print_error(cmd->cmd[1]);
	else if (cmd->cmd[2] != NULL)
	{
		g_exit_code = 1;
		ft_putstr_fd("exit: too many arguments\n", 2);
		return ;
	}	
	else
	{
		if (ft_strncmp(cmd->cmd[1], "-9223372036854775808", 21) == 0)
			g_exit_code = 0;
		else
			g_exit_code = ft_atol(cmd->cmd[1]) % 256;
		ft_putstr_fd("exit\n", 1);
	}
	free_all(env, all_cmd);
	exit(g_exit_code);
}
