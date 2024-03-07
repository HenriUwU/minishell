/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsebille <hsebille@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/16 11:07:36 by laprieur          #+#    #+#             */
/*   Updated: 2023/06/13 11:45:40 by hsebille         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	heredoc_core(char *content, char *delimiter, int fd)
{
	if (g_exit_code != 386)
		g_exit_code = 0;
	while (g_exit_code != 386)
	{
		content = readline("> ");
		if (content == NULL)
		{
			ft_putstr_fd("minishell: warning: end-of-file ", 2);
			ft_putstr_fd("here-document delimited by end-of-file (wanted '", 2);
			ft_putstr_fd(delimiter, 2);
			ft_putstr_fd("')\n", 2);
			break ;
		}
		if (ft_strncmp(content, delimiter, ft_strlen(delimiter) + 1) == 0)
		{
			free(content);
			content = NULL;
			close(fd);
			break ;
		}
		ft_putstr_fd(content, fd);
		ft_putstr_fd("\n", fd);
		free(content);
		content = NULL;
	}
}

void	heredoc(t_cmd *cmd, char *delimiter)
{
	int		fd;
	char	*content;

	fd = open("/tmp/.heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		perror("heredoc");
		g_exit_code = 1;
		return ;
	}
	cmd->heredoc = 1;
	content = NULL;
	heredoc_core(content, delimiter, fd);
}
