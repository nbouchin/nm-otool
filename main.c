#include <sys/mman.h>
#include <sys/stat.h>
#include <mach-o/loader.h>
#include <mach-o/nlist.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

typedef struct mach_header_64		t_mach_header;
typedef struct load_command 		t_load_command;
typedef struct segment_command_64	t_segment_command;
typedef struct stat					t_stat;
typedef struct section_64			t_section;
typedef struct symtab_command		t_symtab_command;
typedef struct nlist_64				t_nlist;

int		main(int argc, char **argv)
{
	int						fd;
	uint32_t				ncmds;
	uint32_t				nsyms;
	t_mach_header			*mach_header;
	t_load_command			*load_command;
	t_stat					buf;
	t_symtab_command		*symtab_command;
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
		if (load_command->cmd == LC_SYMTAB)// Enter if command is a symtab.
		{
			symtab_command = (t_symtab_command*)(load_command);// Casting command into symtab_command.
			nsyms = symtab_command->nsyms;// Get symbol number.
			nlist = (t_nlist *)((char *)mach_header + symtab_command->symoff);// Access to symtab using the symoff.
			string_table = (char *)((char *)mach_header + symtab_command->stroff);// Access to the string table using stroff.
			while (nsyms)// Run while there is a symbol.
			{
				dprintf(2, "%-17llx %hhu %s\n", nlist->n_value, nlist->n_type, (char *)string_table + nlist->n_un.n_strx);// Print string from string table (which is currently just a string).
				nlist += 1;// Inc. symbol.
				nsyms--;
			}
		}
		load_command = (t_load_command*)((char*)load_command + load_command->cmdsize);// Inc. command.
		ncmds--;
	}
	close(fd);
}
