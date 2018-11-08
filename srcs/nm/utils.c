/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 15:32:42 by nbouchin          #+#    #+#             */
/*   Updated: 2018/11/08 15:37:26 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/libft_nm.h"

void				run_nm(t_mach_header_64 *mach_header_64,
		t_fmetadata *fmetadata, t_stat buf, int fd)
{
	if (is_magic(mach_header_64->magic))
		run_regular_files(mach_header_64, fmetadata);
	else
		run_archive_files(mach_header_64, fmetadata);
	delete_data(mach_header_64, fmetadata, buf, fd);
}

void				init_file_metadata(t_fmetadata *fmetadata, int argc,
		char **argv, int nb_file)
{
	fmetadata->new_file = 1;
	fmetadata->fname = ft_strdup(argv[nb_file]);
	fmetadata->argc = argc;
	fmetadata->subfile = NULL;
	fmetadata->to_print = 1;
	fmetadata->alone = 0;
}
