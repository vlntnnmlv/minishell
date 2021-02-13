/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qmalcom <qmalcom@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/28 18:27:22 by rmarguri          #+#    #+#             */
/*   Updated: 2020/12/07 00:43:02 by qmalcom          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	find_closing_quote(char **whole_line)
{
	char	*line;
	int		gnl_res;

	line = NULL;
	gnl_res = get_next_line(0, &line);
	if (gnl_res)
		*whole_line = sum_strings(*whole_line, "\n");
	*whole_line = sum_strings(*whole_line, line);
	free(line);
	line = NULL;
}

static void	find_closing_command(char **whole_line)
{
	char	*line;

	line = NULL;
	get_next_line(0, &line);
	*whole_line = sum_strings(*whole_line, line);
	free(line);
	line = NULL;
}

char		*get_std_args(void)
{
	char	*whole_line;
	int		gnl_res;

	whole_line = NULL;
	gnl_res = get_next_line(0, &whole_line);
	while (find_quotes(whole_line, gnl_res))
		find_closing_quote(&whole_line);
	while (check_pipe(whole_line))
		find_closing_command(&whole_line);
	return (whole_line);
}

int			shell_iter(t_shell *shell)
{
	char	*whole_line;

	while (1)
	{
		signal(SIGQUIT, &handle_sigquit);
		signal(SIGINT, &handle_sigint);
		show_prompt(*shell);
		if (!(whole_line = get_std_args()))
			continue;
		new_command(whole_line, shell);
	}
	return (0);
}
