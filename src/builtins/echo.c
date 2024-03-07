/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laprieur <laprieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 11:47:42 by hsebille          #+#    #+#             */
/*   Updated: 2023/06/13 16:10:50 by laprieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	int	correct_param(char *str)
{
	int	i;

	i = 1;
	if (str == NULL)
		return (0);
	if ((str != NULL && str[0] != '-') || ft_strlen(str) < 2)
		return (0);
	while (str && str[i] != '\0')
	{
		if (str[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

void	echo(char **cmd)
{
	int	i;

	i = 0;
	while (cmd[i + 1] && correct_param(cmd[i + 1]) == 1)
		i++;
	while (cmd[i + 1])
	{
		printf("%s", cmd[i + 1]);
		if (cmd[i + 2] != NULL)
			printf(" ");
		i++;
	}
	if (correct_param(cmd[1]) == 0)
		printf("\n");
	g_exit_code = 0;
}
