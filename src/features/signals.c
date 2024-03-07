/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laprieur <laprieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 14:58:54 by hsebille          #+#    #+#             */
/*   Updated: 2023/06/16 13:07:50 by laprieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	for_rl_event_hook(void)
{
	return (0);
}

void	ctrl_c(int signal)
{
	(void)signal;
	g_exit_code = 386;
	rl_done = 1;
}

void	ctrl_d(int signal)
{
	(void)signal;
	ft_putstr_fd("exit\n", 1);
	exit(g_exit_code);
}
