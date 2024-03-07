/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsebille <hsebille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 10:08:58 by laprieur          #+#    #+#             */
/*   Updated: 2023/06/15 13:50:50 by hsebille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_code;

int	main(int argc, char **argv, char **envp)
{
	t_program	data;
	t_env		*env;

	(void)argv;
	if (argc != 1)
	{
		ft_putstr_fd("Error: Minishell does not take any arguments\n", 2);
		return (1);
	}
	env = get_env(envp, &data);
	if (env == NULL)
		return (1);
	data.env = envp;
	prompt(&data, env);
	return (g_exit_code);
}
