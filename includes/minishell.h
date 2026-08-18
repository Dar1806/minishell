/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akkolitozer <akkolitozer@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 13:38:57 by nmeunier          #+#    #+#             */
/*   Updated: 2026/08/18 02:46:35 by akkolitozer      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <sys/types.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <unistd.h>
# include <errno.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include "libft.h"

typedef enum e_token_type
{
	TOKEN_REDIR_OUT,		/*type = 0 // value = >*/
	TOKEN_REDIR_IN,			/*type = 1 // value = <*/
	TOKEN_REDIR_APPEND,		/*type = 2 // value = >>*/
	TOKEN_HEREDOC,			/*type = 3 // value = <<*/
	TOKEN_PIPE,				/*type = 4 // value = |*/
	TOKEN_WORD,				/*type = 5 // value = abc*/
	TOKEN_SINGLE_QUOTES,	/*type = 6 // value = 'abc'*/
	TOKEN_DOUBLE_QUOTES,	/*type = 7 // value = "abc"*/
}	t_token_type;

/*STRUCT LEXER*/
typedef struct s_token
{
	int						joined;
	char					*value;
	struct s_token			*next;
	t_token_type			type;
}	t_token;

/*STRUCT VARIABLE D'ENVIRONNEMENT*/
typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

/*STRUCT PARSER*/
typedef struct s_cmd
{
	char			*here_doc;
	char			*outfile;
	char			*infile;
	char			**args;
	int				append;
	struct s_cmd	*next;
}	t_cmd;

/*STRUCT SHELL*/
typedef struct s_shell
{
	char			**env;
	t_env			*envl;
	int				ex_status;
}	t_shell;

int		choose_tokens(t_token **tokens, char *line, int *i, t_shell *shell);
void	run_child(t_cmd *cmd, t_shell *shell, int *pipes, int n_cmds);
void	add_token(t_token **tokens, t_token_type type, char *value);
t_token	*fill_cmd(t_cmd *cmd, t_token *cursor, int *parse_error);
void	exec_built_ins(t_cmd *cmd, t_shell *shell, int code);
void	set_last_joined(t_token *tokens, char *line, int i);
int		clean_all(pid_t *pids, int *pipes, int n_cmds);
void	handle_heredoc(t_cmd *cmd, t_token *token);
t_cmd	*parser(t_token *tokens, t_shell *shell);
t_env	*env_new_node(t_env **head, char *env);
char	*get_path(char *cmd_name, char **env);
void	execution(t_cmd *cmd, t_shell *shell);
void	expander(char **word, t_shell *shell);
void	ft_export(t_cmd *cmd, t_shell *shell);
void	ft_unset(t_cmd *cmd, t_shell *shell);
void	env_export(t_env **envl, char *envv);
void	ft_exit(t_cmd *cmd, t_shell *shell);
void	ft_echo(t_cmd *cmd, t_shell *shell);
t_token	*lexer(char *line, t_shell *shell);
void	ft_cd(t_cmd *cmd, t_shell *shell);
void	close_all(int *pipes, int n_cmds);
char	*get_envv(t_env *envl, char *key);
char	**env_list_to_array(t_env *envl);
void	exec_cmd(t_cmd *cmd, char **env);
int		is_redir_type(t_token_type type);
int		write_read(char *file, int mode);
int		is_word_type(t_token_type type);
int		exec_here_doc(char *limiter);
void	free_tokens(t_token *tokens);
void	env_free_nodes(t_env *head);
t_env	*env_init_list(char **env);
void	env_free_list(t_env *head);
t_env	*ft_expdup(t_env **envl);
int		is_built_ins(char *line);
int		is_valid_key(char *str);
int		*open_pipes(int n_cmds);
void	env_print(t_env **envl);
int		count_cmds(t_cmd *cmd);
void	ft_pwd(t_shell *shell);
void	free_cmd(t_cmd *cmd);
void	ft_env(t_env *envl);
int		find_feq(char *s);
t_cmd	*new_cmd(void);
#endif