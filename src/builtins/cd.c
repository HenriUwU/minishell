/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laprieur <laprieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/02 16:42:59 by hsebille          #+#    #+#             */
/*   Updated: 2023/06/16 12:34:34 by laprieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_old_pwd(t_env *env)
{
	t_env	*tmp;
	char	*pwd;

	tmp = env;
	pwd = NULL;
	while (tmp != NULL && ft_strncmp(tmp->var, "PWD", 4) != 0)
		tmp = tmp->next;
	if (tmp != NULL && tmp->value[0] != '\0')
		pwd = ft_strdup(tmp->value);
	else if (tmp == NULL)
		pwd = ft_strdup(" ");
	tmp = env;
	while (tmp != NULL && ft_strncmp(tmp->var, "OLDPWD", 7) != 0)
		tmp = tmp->next;
	if (tmp != NULL)
	{
		if (tmp->value[0] != '\0')
			free(tmp->value);
		tmp->value = ft_strdup(pwd);
		free(pwd);
	}
	else
		free(pwd);
}

static void	set_new_pwd(t_env *env)
{
	t_env	*tmp;
	char	buf[PATH_MAX];
	char	*new_pwd;

	tmp = env;
	while (tmp != NULL && ft_strncmp(tmp->var, "PWD", 4) != 0)
		tmp = tmp->next;
	if (tmp == NULL)
		return ;
	if (tmp != NULL)
	{
		if (tmp->value[0] != '\0')
			free(tmp->value);
		new_pwd = getcwd(buf, sizeof(buf));
		tmp->value = ft_strdup(new_pwd);
	}
}

void	cd(char **cmd, t_env *env)
{
	if (cmd[1] == NULL)
	{
		ft_putstr_fd("minishell: cd: too few arguments\n", 2);
		g_exit_code = 1;
		return ;
	}
	if (cmd[2] != NULL)
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		g_exit_code = 1;
		return ;
	}
	chdir(cmd[1]);
	if (errno == EACCES || errno == ENOENT || errno == ENOTDIR)
	{
		perror("minishell: cd");
		g_exit_code = 1;
		return ;
	}
	set_old_pwd(env);
	set_new_pwd(env);
	g_exit_code = 0;
}
