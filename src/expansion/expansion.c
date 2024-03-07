/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laprieur <laprieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 10:39:58 by laprieur          #+#    #+#             */
/*   Updated: 2023/06/16 10:01:51 by laprieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	len_before_dollar(char *str, int mode)
{
	int	len;

	len = ft_strcspn(str, "$");
	while (str[len])
	{
		if (!is_in_quotes(str, (str + len))
			|| (is_in_quotes(str, (str + len)) == '\"' && mode))
			break ;
		else
			len += ft_strcspn(&str[len + 1], "$") + 1;
	}
	return (len);
}

static char	*join_lst(t_list *lst)
{
	char	*expand_str;

	expand_str = ft_strdup(lst->content);
	lst = lst->next;
	while (lst != NULL)
	{
		expand_str = ft_strjoin(expand_str, lst->content);
		if (expand_str == NULL)
			return (NULL);
		lst = lst->next;
	}
	return (expand_str);
}

static char	*get_env_var(t_env *env, char *name)
{
	t_env	*tmp;

	tmp = env;
	if (name[0] == '\0')
		return (ft_strdup("$"));
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->var, name, ft_strlen(tmp->var) + 1) == 0)
		{
			if (tmp->value[0] == '\0')
				return ("\0");
			return (ft_strdup(tmp->value));
		}
		tmp = tmp->next;
	}
	return ("\0");
}

static int	add_var(t_list **lst, char *str, t_env *env)
{
	char	*var_name;
	char	*var;
	int		len;

	if (str[0] == '?')
	{
		var = ft_itoa(g_exit_code);
		ft_lstadd_back(lst, ft_lstnew(var));
		return (1);
	}
	len = ft_strspn(str, \
		"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ_abcdefghijklmnopqrstuvwxyz");
	var_name = ft_substr(str, 0, len);
	if (var_name == NULL)
		return (-1);
	var = get_env_var(env, var_name);
	free(var_name);
	ft_lstadd_back(lst, ft_lstnew(var));
	return (len);
}

char	*expansion(char *str, t_env *env, int mode)
{
	int		i;
	int		len;
	char	*final_str;
	t_list	*lst;

	i = 0;
	lst = NULL;
	while (str[i] != '\0')
	{
		if (str[i] == '$' && (!is_in_quotes(str, &str[i])
				|| (is_in_quotes(str, &str[i]) == '\"' && mode)))
		{
			i++;
			len = add_var(&lst, &str[i], env);
			i += len;
			continue ;
		}
		len = len_before_dollar(&str[i], mode);
		ft_lstadd_back(&lst, ft_lstnew(ft_substr(str, i, len)));
		i += len;
	}
	final_str = join_lst(lst);
	free_list(lst);
	return (final_str);
}
