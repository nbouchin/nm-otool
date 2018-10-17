/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nbouchin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/16 10:34:04 by nbouchin          #+#    #+#             */
/*   Updated: 2018/10/16 10:34:04 by nbouchin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft_nm.h"

int		main(int argc, char **argv)
{
	(void)argc;
	int						fd;
	uint32_t				ncmds;
	uint32_t				nsyms;
	unsigned long 			nsects;
	t_mach_header			*mach_header;
	t_load_command			*load_command;
	t_stat					buf;
	t_symtab_command		*symtab_command;
	t_segment_command		*segment_command;
	t_section				*section;
	t_nlist					*nlist;
	char					*string_table;

	fd = open(argv[1], O_RDONLY);// Get file descriptor from file.
	if (fstat(fd, &buf) == -1)// Check file openning error.
		return (0);
	mach_header = mmap(NULL, buf.st_size, PROT_WRITE | PROT_READ, MAP_PRIVATE, fd, 0);// mmap mach-o header.
	if (mach_header == MAP_FAILED)// If MAP_FAILED return.
		return (0);
	ncmds = mach_header->ncmds;// Getting number of command from mach_header.
	load_command = (t_load_command*)(mach_header + 1);// Get load_command.
	while (ncmds)// Run while there is a command.
	{
		if (load_command->cmd == LC_SEGMENT_64)// Enter if command is a symtab.
		{
			segment_command = (t_segment_command*)(load_command);// Casting command into segment_command.
			dprintf(2, "%s\n", segment_command->segname);
			nsects = segment_command->nsects;	
			section = (t_section*)(segment_command + 1);
			while (nsects)
			{
				dprintf(2, "%s\n", section->sectname);
				section++;
				nsects--;
			}
		}
		else if (load_command->cmd == LC_SYMTAB)// Enter if command is a symtab.
		{
			symtab_command = (t_symtab_command*)(load_command);// Casting command into symtab_command.
			nsyms = symtab_command->nsyms;// Get symbol number.
			nlist = (t_nlist *)((char *)mach_header + symtab_command->symoff);// Access to symtab using the symoff.
			string_table = (char *)((char *)mach_header + symtab_command->stroff);// Access to the string table using stroff.
			while (nsyms)// Run while there is a symbol.
			{
				if ((nlist->n_type & N_STAB))
					dprintf(2, "%-17llx %c %s\n", nlist->n_value, 'S', (char *)string_table + nlist->n_un.n_strx);// Print string from string table (which is currently just a string).
				else if ((nlist->n_type & N_TYPE) == N_UNDF)
					dprintf(2, "%-17llx %c %s\n", nlist->n_value, 'U', (char *)string_table + nlist->n_un.n_strx);// Print string from string table (which is currently just a string).
				else if ((nlist->n_type & N_TYPE) == N_ABS)
					dprintf(2, "%-17llx %c %s\n", nlist->n_value, 'A', (char *)string_table + nlist->n_un.n_strx);// Print string from string table (which is currently just a string).
				else if ((nlist->n_type & N_TYPE) == N_SECT)
					dprintf(2, "%-17llx %c %s\n", nlist->n_value, 'T', (char *)string_table + nlist->n_un.n_strx);// Print string from string table (which is currently just a string).
				else if ((nlist->n_type & N_TYPE) == N_PBUD)
					dprintf(2, "%-17llx %c %s\n", nlist->n_value, 'P', (char *)string_table + nlist->n_un.n_strx);// Print string from string table (which is currently just a string).
				else if ((nlist->n_type & N_TYPE) == N_INDR)
					dprintf(2, "%-17llx %c %s\n", nlist->n_value, 'I', (char *)string_table + nlist->n_un.n_strx);// Print string from string table (which is currently just a string).
				else if ((nlist->n_type & N_EXT))
					dprintf(2, "%-17llx %c %s\n", nlist->n_value, 'E', (char *)string_table + nlist->n_un.n_strx);// Print string from string table (which is currently just a string).
				nlist += 1;// Inc. symbol.
				nsyms--;
			}
		}
		load_command = (t_load_command*)((char*)load_command + load_command->cmdsize);// Inc. command.
		ncmds--;
	}
	close(fd);
}