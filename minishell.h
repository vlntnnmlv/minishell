/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmalcom <qmalcom@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/30 15:36:44 by rmarguri          #+#    #+#             */
/*   Updated: 2020/12/08 14:01:01 by qmalcom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
# include <signal.h>
# include <dirent.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <errno.h>
# include "gnl/get_next_line.h"
# include "libft/libft.h"
# define ESC "\033[0m"
# define BLK "\e[0;30m"
# define RED "\e[0;31m"
# define WHTB "\e[47m"
# define BMGT "\e[1;35m"
# define BLU "\e[0;34m"

# define ERR_SYNT ("minishell: syntax error near unexpected token `newline';\n")
# define CONTINUE ("> ")

/*
** TOK_COUTF 	>>
** TOK_OUTF		>
** TOK_INF		<
** TOK_PIPE		|
** TOK_NEXT		;
** TOK_GETPIPE	$?
*/

# define TOK_INF			(0b00000001u)
# define TOK_OUTF			(0b00000010u)
# define TOK_AOUTF			(0b00000100u)
# define TOK_PIPE			(0b00001000u)
# define TOK_NEXT			(0b00010000u)
# define TOK_GETPIPE		(0b00100000u)
# define TOK_CLOB_OUTF		(0b01000000u)

typedef	struct stat	t_stat;

typedef	enum
{
	NIF = -1,
	NSF = 0,
	REG = 1,
	DRC = 2
}	t_state;

/*
** ret_to_dq - if we handle $ btw dquote marks
*/

typedef struct			s_currword
{
	int					start;
	int					len;
	int					join;
	int					spec_symb;
	int					ret_to_dq;
}						t_currword;

/*
** draft words list
*/

typedef struct			s_wlist
{
	char				*word;
	struct s_wlist		*next;
	int					join_next;
	int					spec_symb;
}						t_wlist;

/*
** tokens list
** token - can be regular word (command or it's argument, or any symbol)
** or special symbol (| ; $? < > >>)
** next - pointer to next token
** spec_symb - is it a special symbol.
** 		2 - env variable
** 		1 - < > >> | ;
** 		0 - reg word
*/

typedef struct			s_tlist
{
	char				*token;
	struct s_tlist		*next;
	struct s_tlist		*prev;
	int					spec_symb;
}						t_tlist;

typedef struct			s_parsed
{
	t_wlist				**wlist;
	int					w_count;
}						t_parsed;

/*
** command list
** cmd - command
** fd_in_f - fd of input file for this command
** fd_out_f - fd of program result
** first_arg - pointer to first atg of command
** args_count - how many argumens is given
** next_com - pointer to next command, so its next element of clist
** prev_com - pointer to previous command
*/

typedef struct			s_clist
{
	char				*cmd;
	int					fd_in_f;
	char				*in_file_name;
	char				*out_file_name;
	int					fd_out_f;
	struct s_tlist		*first_arg;
	int					args_count;
	struct s_clist		*next_com;
	struct s_clist		*prev_com;
	int					pipe_next;
}						t_clist;

typedef struct			s_shell
{
	int					(*cmds[7])(t_clist*, struct s_shell*);

	char				*prompt;
	char				**commands;
	t_list				*env;
	char				**env_std;
	char				**paths;
	char				**av;
	pid_t				pid;
	int					status;
}						t_shell;

int						shell_init(t_shell *shell, char **env);
int						shell_iter(t_shell *shell);
void					new_command(char *str, t_shell *shell);
char					**list_to_char(t_list *env);
int						check_quote(char *str, int i);
int						check_dquote(char *str, int i);
int						find_quotes(char *str, int gnl_res);
int						do_redir(t_shell *shell);
int						show_prompt(t_shell shell);
int						is_executable(char *exec);
char					**clist_to_char(t_clist *cmd);
int						before_exit(int err, char *fun_name, \
						char *mess, t_shell *shell);
t_state					exist_check(char *path);
int						exec_builtout(t_clist *clist, t_shell *shell);
int						exec_direct(char *exec, t_shell *shell);
char					*get_env_var(t_list *env, char *name);
int						set_env_var(t_list *env, char *name, char *value);
int						del_env_var(t_list *env, char *name);
void					free_darr(char **darr);
char					*sum_strings(char *str1, char *str2);
int						check_pipe(char *str);
t_clist					*command_list(t_tlist *tlist);
void					free_clist(t_clist *clist);
int						ft_strcmp(char *s1, char *s2);
int						no_func_error(char *func_name);
int						no_file_error(char *file_name);
int						wrong_var_error(char *var);
int						permission_error(char *var);
int						synt_error(char *token);
int						f_new_echo(t_clist *clist, t_shell *shell);
int						f_new_pwd(t_clist *clist, t_shell *shell);
int						f_new_exit(t_clist *clist, t_shell *shell);
int						f_new_cd(t_clist *clist, t_shell *shell);
int						f_new_export(t_clist *clist, t_shell *shell);
int						f_new_unset(t_clist *clist, t_shell *shell);
int						f_new_env(t_clist *clist, t_shell *shell);
t_wlist					*new_word(char *str, t_currword *currword);
t_wlist					*wlistlast(t_wlist *words);
t_wlist					*wslist_add(t_wlist *first_elem, t_wlist *new_word);
t_wlist					*create_draft_list(char *str, t_shell *shell);
void					free_wlist(t_wlist *wlist);
void					skip_spaces(char *str, int *i_cur);
int						get_var_pos(char *str);
t_clist					*executor(t_clist *cmds, t_shell *shell);
int						close_fds(t_clist *clist);
int						search_env_var(char *new_envv, t_list **env);
int						set_exit_status(int res, t_shell *shell);
void					handle_sigquit(int sign);
void					handle_sigint(int sign);
char					*sum_strings(char *str1, char *str2);
t_tlist					*create_token(char *str);
int						check_wlist(t_wlist *wlist);
t_tlist					*tlist_add(t_tlist *first_elem, \
						t_tlist *new_word);
void					print_list(t_list **env);
char					*find_env_var(char *str, t_list **env);
void					free_struct(t_parsed *parse_result);
int						search_word(char *str, int *i, t_currword *currword);
int						set_exit_status(int res, t_shell *shell);
int						show_prompt(t_shell shell);
void					tlist_clean(t_tlist *tlist);
void					wlist_clean(t_wlist *wlist);
void					free_clist(t_clist *clist);
int						get_var_pos(char *str);
int						hndl_spec_symb(char *str, int *i, t_currword *currword);
int						isn_spec_symb(char *str, int *i);
void					is_join_next(char *str, int *i, t_currword *currword);
void					reg_word(char *str, int *i, t_currword *currword);
int						search_word(char *str, int *i, t_currword *currword);
int						fill_currword(t_currword *currword, \
						int *i, int len);
int						fill_spec_symb(t_currword *currword, \
						int *i, int len);
int						is_just_dollar(char *str, int *i, \
						t_currword *currword);
int						get_envvar_name(char *str, int *i, \
						t_currword *currword);
void					word_btw_dquote(char *str, \
						int *i, t_currword *currword);
void					dollar_btw_dq(char *str, int *i, t_currword *currword);
void					word_btw_qoute(char *str, int *i, t_currword *currword);
void					create_tokens_list(t_wlist *draft_list, t_shell *shell);
t_tlist					*tlist_add(t_tlist *first_elem, t_tlist *new_word);
t_tlist					*tlistlast(t_tlist *tokens);
t_clist					*init_command(void);
int						handle_inf(t_wlist **wlist, t_clist *clist,
															t_shell *shell);
int						handle_outf(t_wlist **wlist, t_clist *clist,
															t_shell *shell);
int						handle_aoutf(t_wlist **wlist, t_clist *clist,
															t_shell *shell);
int						handle_pipe(t_wlist **wlist, t_clist **clist,
															t_shell *shell);
int						handle_next(t_wlist **wlist, t_clist **clist,
															t_shell *shell);
int						clist_reg_comm(t_wlist **wlist, t_clist *clist,
															t_shell *shell);
int						what_spec_symb(t_wlist *wlist);
char					*get_token(t_wlist **draft_list, t_shell *shell);
int						permission_re_wr(char *var);
t_clist					*find_head(t_clist *clist);
char					*find_env_forexport(char *str, t_list **env);
t_wlist					*skip_fname_token(t_wlist *wlist);
t_wlist					*skip_curr_command(t_wlist *wlist);
void					is_join_dq(char *str, int *i, t_currword *currword);
int						is_env_var(char *str, int *i, t_currword *currword);
int						is_only_dollar(char *str, int *i, t_currword *currword);
int						is_reg_symb(char *str, int *i, t_currword *currword);
int						is_bslash(char *str, int *i, t_currword *currword);

#endif
