/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 10:34:00 by nbouchin          #+#    #+#             */
/*   Updated: 2018/10/16 15:48:07 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft_nm.h"

void		print_symtab(t_load_command *load_command, t_mach_header *mach_header, t_nlist *symtab)
{
	uint32_t	i;
	t_nlist		*nlist;
	char		*string_table;

	i = -1;
	nlist = (t_nlist *)((char *)mach_header + ((t_symtab_command*)load_command)->symoff);
	string_table = (char *)((char *)mach_header + ((t_symtab_command*)load_command)->stroff);
	while (++i < ((t_symtab_command*)load_command)->nsyms)
	{
		if ((symtab[i].n_type & N_STAB))
			printf("%-17llx %c %s\n", symtab[i].n_value, 'S', (char *)string_table + symtab[i].n_un.n_strx);
		else if ((symtab[i].n_type & N_TYPE) == N_UNDF)
			printf("%-17llx %c %s\n", symtab[i].n_value, 'U', (char *)string_table + symtab[i].n_un.n_strx);
		else if ((symtab[i].n_type & N_TYPE) == N_ABS)
			printf("%-17llx %c %s\n", symtab[i].n_value, 'A', (char *)string_table + symtab[i].n_un.n_strx);
		else if ((symtab[i].n_type & N_TYPE) == N_SECT)
			printf("%-17llx %c %s\n", symtab[i].n_value, 'T', (char *)string_table + symtab[i].n_un.n_strx);
		else if ((symtab[i].n_type & N_TYPE) == N_PBUD)
			printf("%-17llx %c %s\n", symtab[i].n_value, 'P', (char *)string_table + symtab[i].n_un.n_strx);
		else if ((symtab[i].n_type & N_TYPE) == N_INDR)
			printf("%-17llx %c %s\n", symtab[i].n_value, 'I', (char *)string_table + symtab[i].n_un.n_strx);
		else if ((symtab[i].n_type & N_EXT))
			printf("%-17llx %c %s\n", symtab[i].n_value, 'E', (char *)string_table + symtab[i].n_un.n_strx);
		nlist += 1;
	}
}

t_nlist		*get_symtab(t_load_command *load_command, t_mach_header *mach_header)
{
	uint32_t			i;
	t_nlist				*nlist;
	t_nlist				*symtab;

	i = -1;
	nlist = (t_nlist *)((char *)mach_header + ((t_symtab_command*)load_command)->symoff);
	symtab = malloc(((t_symtab_command*)load_command)->nsyms);
	while (++i < ((t_symtab_command*)load_command)->nsyms + 1)
	{
		symtab[i] = *nlist;
		nlist += 1;
	}
	return (symtab);
}

int		ft_nm(t_mach_header *mach_header)
{
	uint32_t		ncmds;
	t_nlist			*symtab;
	t_load_command	*load_command;

	ncmds = mach_header->ncmds + 1;
	load_command = (t_load_command*)(mach_header + 1);
	while (--ncmds)
	{
		if (load_command->cmd == LC_SYMTAB)
		{
			symtab = get_symtab(load_command, mach_header);
			print_symtab(load_command, mach_header, symtab);
			free (symtab);
		}
		load_command = (t_load_command*)((char*)load_command + load_command->cmdsize);
	}
	return (1);
}

int		main(int argc, char **argv)
{
	int				fd;
	int	nb_file;
	t_stat			buf;
	t_mach_header	*mach_header;

	nb_file = 0;
	while (++nb_file < argc) 
	{
		fd = open(argv[nb_file], O_RDONLY);
		if (fstat(fd, &buf) == -1)
		{
			printf("%s: No such file or directory.\n", argv[nb_file]);
			(nb_file + 1 < argc) ? ft_putendl("") : 0;
			continue ;
		}
		mach_header = mmap(NULL, buf.st_size, PROT_WRITE | PROT_READ, MAP_PRIVATE, fd, 0);
		if (mach_header == MAP_FAILED)
			return (0);
		(argc > 2) ? printf("%s:\n", argv[nb_file]) : 0;
		ft_nm(mach_header);
		munmap(mach_header, buf.st_size);
		close(fd);
		(nb_file + 1 < argc) ? ft_putendl("") : 0;
	}
}

