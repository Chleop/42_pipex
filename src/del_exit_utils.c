/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_exit_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 11:24:59 by cproesch          #+#    #+#             */
/*   Updated: 2021/10/27 14:21:31 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_del_stringtab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		free(tab[i++]);
	free(tab);
}

void	ft_exit(t_data **data, int exit_code)
{
	if ((data != NULL) && ((*data) != NULL))
	{
		if ((*data)->cmd1 && (*(*data)->cmd1))
			ft_del_stringtab((*data)->cmd1);
		if ((*data)->cmd1_path && (*(*data)->cmd1_path))
			free ((*data)->cmd1_path);
		if ((*data)->cmd2 && (*(*data)->cmd2))
			ft_del_stringtab((*data)->cmd2);
		if ((*data)->cmd2_path && (*(*data)->cmd2_path))
			free ((*data)->cmd2_path);
		free (*data);
	}
	exit (exit_code);
}

void	error_message(char *error_message, t_data **data)
{
	perror(error_message);
	ft_exit(data, 2);
}
