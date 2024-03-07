/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: laprieur <laprieur@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 14:58:31 by hsebille          #+#    #+#             */
/*   Updated: 2023/06/16 13:18:53 by laprieur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <signal.h>
# include <limits.h>
# include <unistd.h>
# include <stdbool.h>
# include <sys/wait.h>
# include <errno.h>
# include "fcntl.h"

extern int	g_exit_code;

typedef enum e_redir
{
	INPUT,
	OUTPUT,
	PIPE,
	APPEND,
	HEREDOC,
}	t_redir;

typedef enum e_pipe
{
	FIRST,
	WITHIN_EVEN,
	WITHIN_ODD,
	LAST_EVEN,
	LAST_ODD,
}	t_pipe;

typedef enum e_export
{
	NEW_VAR,
	REPLACE,
	EX_APPEND,
}	t_export;

typedef struct s_cmd
{
	char			**cmd;
	char			*cmd_path;
	char			*infile;
	char			*outfile;
	int				input;
	int				output;
	int				heredoc;
	int				pid;
	int				index;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_env
{
	char			*var;
	char			*value;
	int				index;
	int				is_value;
	struct s_env	*next;
}	t_env;

typedef struct s_unset
{
	t_env	*to_free;
	t_env	*current;
	t_env	*prev;
}	t_unset;

typedef struct s_program
{
	int		env_size;
	char	*line;
	char	**env;
	int		pipe1[2];
	int		pipe2[2];

}	t_program;

/* BUILTINS */

void	cd(char **cmd, t_env *env);
void	echo(char **cmd);
void	env(t_env *env, char **cmd);
void	mini_exit(t_env *env, t_cmd *cmd, t_cmd *all_cmd);
void	export(t_env *env, char **cmd, t_program *data);
void	pwd(void);
void	unset(t_env **head, t_program *data, char **cmd);

/* BUILTINS UTILS */

int		add_value(t_env *env, char *line);
int		check_invalid_var(char *var, char *line);
int		env_error_case(char **cmd, int i);
int		get_index(t_env *env, char *var);
int		mini_char_chr(char *str, char c);
int		replace_var(t_env *env, char *var, char *value, char *line);
bool	is_var_valid(char *var);
char	*get_value(char *line);
char	*get_var(char *line);
void	print_export_core(t_env *tmp);
void	print_export(t_env *env, int env_size);
void	set_index(t_env *env);
t_env	*get_env(char **envp, t_program *data);

/* EXEC */

int		count_nb_cmd(t_cmd *cmd);
int		exec_builtins(t_program *data, t_env *envp, t_cmd *cmd, t_cmd *all);
int		exit_child(t_cmd *cmd, t_env *env, int pid);
int		make_dup2_first(t_cmd *cmd, int *pipe1);
int		make_dup2_last(t_cmd *cmd, int *pipe1, int *pipe2, int mode);
int		make_dup2_within(t_cmd *cmd, int *pipe1, int *pipe2, int mode);
int		parse_dup2(int index, t_cmd *cmd, t_program *data);
void	close_input_output(int input, int output);
void	close_pipes(int index, int *pipe1, int *pipe2);
void	create_pipes(int index, t_cmd *cmd, t_program *data);
void	cmd_not_found(t_env *env, t_cmd *cmd, t_cmd *all);
void	exec(t_program *data, t_env *env, t_cmd *cmd);
void	exit_status(t_cmd *cmd);
void	fork_exec(t_cmd *tmp, t_cmd *cmd, t_program *data, t_env *env);
void	free_all(t_env *env, t_cmd *cmd);
void	handle_path(t_env *env, t_cmd *cmd, t_cmd *all);

/* EXPANSION */

int		count_words(char *str, char *charset);
int		get_redir_len(char *str, char *charset, int len, int i);
int		is_charset(char *charset, char c);
char	*expansion(char *str, t_env *env, int mode);
char	*get_next_word(char *str, char *charset);
char	is_in_quotes(char *str, char *substr);
void	free_list(t_list *lst);
void	mfree(char **words, int position);

/* FEATURES */

int		for_rl_event_hook(void);
void	ctrl_c(int signal);
void	ctrl_d(int signal);
void	heredoc(t_cmd *cmd, char *delimiter);
void	prompt(t_program *data, t_env *env);	

/* PARSING / COMMANDS*/

int		define_infile(t_cmd *cmd, t_env *env, char *str, int old_redir);
int		define_outfile(t_cmd *cmd, t_env *env, char *str, int old_redir);
int		final_check(char *str);
int		redirections_core(int *i, char *str, char redir);
bool	is_last_redir(char **redir, int type);
bool	is_there_quote(char *str);
char	**get_cmd(t_env *env, char *command);
char	**get_redir(char *cmd);
char	**mini_split(char *str);
char	*quote_removal_bis(char *str);
char	**quote_removal(char **str);
char	*restructure_string(char *str);
char	**turbo_split(char *str, char *charset);
void	commands(t_program *data, t_env *env, t_cmd **cmd);
void	free_infile_outfile(t_cmd *cmd, int mode);
void	open_infile(t_cmd *cmd, int *redir_in, bool *is_file_ok);
void	open_outfile(t_cmd *cmd, int *redir_out, bool *is_file_ok);

/* PARSING / SYNTAX */

int		left_redirections(int *i, char *str);
int		right_redirections(int *i, char *str);
int		skip_quotes(char *str, char quote);
int		syntax(char *line);

/* UTILS / LIST */

int		env_lstsize(t_env *env);
void	cmd_lstadd_back(t_cmd **lst, t_cmd *new);
void	env_lstadd_back(t_env **env, t_env *new);
void	free_list_cmd(t_cmd *lst);
void	free_list_env(t_env *lst);
t_cmd	*cmd_lstlast(t_cmd *lst);
t_cmd	*cmd_lstnew(void);
t_env	*env_lstnew(char *var, char *value, int index, int is_new_var);
t_env	*env_lstlast(t_env *env);

#endif
