/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_func.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarguri <rmarguri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/01 23:09:45 by qmalcom           #+#    #+#             */
/*   Updated: 2020/12/04 19:51:23 by rmarguri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	permission_error(char *var)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(var, 2);
	ft_putstr_fd(" Permission denied\n", 2);
	return (1);
}

int	no_func_error(char *func_name)
{
	ft_putstr_fd(func_name, 2);
	ft_putstr_fd(" : command not found\n", 2);
	return (0);
}

int	no_file_error(char *file_name)
{
	ft_putstr_fd("minishell : ", 2);
	ft_putstr_fd(file_name, 2);
	ft_putstr_fd(" : No such file or directory\n", 2);
	return (0);
}

int	wrong_var_error(char *var)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(var, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	return (1);
}

/*
** error while parse
*/

int	synt_error(char *token)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 1);
	ft_putstr_fd(token, 1);
	ft_putstr_fd("'\n", 1);
	return (1);
}
