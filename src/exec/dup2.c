/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laprieur <laprieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/07 12:19:13 by laprieur          #+#    #+#             */
/*   Updated: 2023/06/07 15:13:19 by laprieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	dup2_input(int input)
{
	if (input > 2)
	{
		dup2(input, 0);
		close(input);
	}
}

static void	dup2_output(int output)
{
	if (output > 2)
	{
		dup2(output, 1);
		close(output);
	}
}

int	make_dup2_first(t_cmd *cmd, int *pipe1)
{
	dup2_input(cmd->input);
	if (cmd->input == -1)
		return (1);
	dup2_output(cmd->output);
	if (cmd->output == -42 && cmd->next != NULL)
	{
		dup2(pipe1[1], 1);
		close(pipe1[1]);
	}
	return (0);
}

int	make_dup2_within(t_cmd *cmd, int *pipe1, int *pipe2, int mode)
{
	dup2_input(cmd->input);
	if (cmd->input == -1)
		return (1);
	else if (cmd->input == -42 && mode == WITHIN_EVEN)
	{
		dup2(pipe2[0], 0);
		close(pipe2[0]);
	}
	else if (cmd->input == -42 && mode == WITHIN_ODD)
	{
		dup2(pipe1[0], 0);
		close(pipe1[0]);
	}
	dup2_output(cmd->output);
	if (cmd->output == -42 && mode == WITHIN_EVEN)
	{
		dup2(pipe1[1], 1);
		close(pipe1[1]);
	}
	else if (cmd->output == -42 && mode == WITHIN_ODD)
	{
		dup2(pipe2[1], 1);
		close(pipe2[1]);
	}
	return (0);
}

int	make_dup2_last(t_cmd *cmd, int *pipe1, int *pipe2, int mode)
{
	dup2_input(cmd->input);
	if (cmd->input == -1)
		return (1);
	else if (cmd->input == -42 && mode == LAST_EVEN)
	{
		dup2(pipe2[0], 0);
		close(pipe2[0]);
	}
	else if (cmd->input == -42 && mode == LAST_ODD)
	{
		dup2(pipe1[0], 0);
		close(pipe1[0]);
	}
	dup2_output(cmd->output);
	return (0);
}
