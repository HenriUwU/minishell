/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laprieur <laprieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/24 09:43:57 by laprieur          #+#    #+#             */
/*   Updated: 2023/06/07 11:12:52 by laprieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(void)
{
	char	*absolute_pathname;
	char	buf[PATH_MAX];

	absolute_pathname = getcwd(buf, sizeof(buf));
	printf("%s\n", absolute_pathname);
	g_exit_code = 0;
}
