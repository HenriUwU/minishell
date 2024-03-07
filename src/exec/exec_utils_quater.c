/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils_quater.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsebille <hsebille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 16:26:02 by hsebille          #+#    #+#             */
/*   Updated: 2023/06/13 16:29:06 by hsebille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_all(t_env *env, t_cmd *cmd)
{
	int	fd;

	if (env != NULL)
		free_list_env(env);
	if (cmd != NULL)
		free_list_cmd(cmd);
	fd = 3;
	while (fd < 1024)
	{
		close(fd);
		fd++;
	}
}
