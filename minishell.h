/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 14:48:31 by fkoehler          #+#    #+#             */
/*   Updated: 2016/06/11 17:39:36 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <libft.h>
# include <ft_printf.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/param.h>

# define DEFAULT_PATH "/usr/bin:/bin:/usr/sbin:/sbin"

typedef struct		s_env
{
	char			*var;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct		s_shell
{
	t_env			*env_lst;
	char			**args;
}					t_shell;

char				*g_prompt;

int					error(int errnum);
void				exec_error(int errnum, char *cmd);
void				env_var_error(int errnum, char *cmd, char *arg);
int					env_cmd_error(int errnum, int flag);
int					cd_cmd_error(int errnum, char *arg);

void				handle_sigint(int signum);
void				handle_sigint2(int signum);

int					parse_env_var(t_env **env_lst, char *env_var);
int					dup_env_lst(t_env **env_lst, t_env **env_lst_cpy);
int					check_env_var(char *env_var, char *cmd);
t_env				*get_env_var(t_env *env_lst, char *var);
int					store_env_var(t_env **env_lst, char *var, char *value);
int					del_env_var(t_env **env_lst, char *var);
char				**make_env_tab(t_env *env_lst);
int					read_cmd(t_shell *shell);
int					parse_cmd(t_env **env, char *cmd);

int					check_path(char *path);
int					set_new_pwd(t_env *env_lst);
char				*get_path_to_search(char *cmd, t_env *home, t_env *env_lst);
char				**get_paths(t_env *env_lst);
char				*get_prompt(t_env *env_lst);

int					execute_bin(char *bin, char **args, char **env);
int					check_bin_access(char **env_tab,
					char *bin_path, char **cmd);
int					check_bin_path(t_env *env_lst, char **env_tab, char **cmd);
int					binary_cmd(t_env *env_lst, char **env_tab, char **cmd);
int					builtins_cmd(t_env **env_lst, char **cmd);

int					ft_cd(char **cmd, t_env *env);
int					ft_env(char **cmd, t_env *env_lst, int i);
int					ft_setenv(char **cmd, t_env **env_lst, int flag);
int					ft_unsetenv(char **cmd, t_env **env_lst);
int					ft_exit(char **cmd);

void				free_env_var(t_env *env_var);
void				free_env_lst(t_env **env_lst);
char				*strdup_remove_quotes(char *str);
char				**strsplit_blanks_and_quotes(char const *s);

#endif
