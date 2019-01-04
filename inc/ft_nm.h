#ifndef FT_NM_H
# define FT_NM_H

# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/mman.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <mach-o/stab.h>
# include <mach-o/fat.h>
# include <libft.h>
# include <ar.h>

typedef struct			s_symdata // NLIST_64
{
	char				*str;
	uint8_t				type;
	uint8_t				stab;
	uint8_t				ext;
	uint8_t				nsect;
	uint8_t				pext;
	uint64_t			value;
	int					t;
	struct s_symdata	*next;
}						t_symdata;

typedef struct			s_section
{
	char				*name;
	unsigned int		index;
	struct s_section	*end;
	struct s_section	*next;
}						t_section;

// nm.c
void		nm(void *ptr, char *av, size_t filesize, void *tmp);

					// 32 //
// loadcmd_32.c
void 		bits_32(void *ptr, uint32_t filesize);
// sections_32.c
void 		process_segment_32(struct load_command *lc, t_section **psects);
// symtable_32.c
void 		process_symtable_32(struct load_command *lc, void *ptr, t_symdata **psymbols, size_t filesize);
// sort_32.c
void 		insertion_sort(t_symdata **slist);
// mask_32.c
void		mask_32(uint64_t value, uint8_t type);

					// 64 //
// loadcmd_64.c
void 		bits_64(void *ptr, uint32_t filesize);
// sections_64.c
void 		process_segment_64(struct load_command *lc, t_section **psects);
// symtable_64.c
void 		process_symtable_64(struct load_command *lc, void *ptr, t_symdata **psymbols, size_t filesize);
// sort_64.c
void 		insertion_sort(t_symdata **slist);
// mask_64.c
void		mask_64(uint64_t value, uint8_t type);


					// ar_and_fat //
//ar.c
void		archive_lib(void *ptr, char *av, size_t filesize, void *tmp);

					// display //
//errors.c
int			no_file(char *av);
void 		display_av(char *av);
int 		file_is_dir(char *av);
int 		unvalid_object(char *av);
int			check_format(void *ptr, char *av);
// display/display.c
void		display_64(t_section *psects, t_symdata *psymbols);
void		display_32(t_section *psects, t_symdata *psymbols);
// display/symbols.c
void		display_symbol(t_section *psects, t_symdata *psymbols);

					// common //
// check_file.c
int			check_file_content(void *ptr, size_t filesize);
int			verify_symtab(struct load_command *lc, size_t filesize, size_t checksize);
// check_32.c
int			verify_lc_32(struct mach_header *header, size_t filesize, uint32_t nbcmd);
// check_64
int			verify_lc_64(struct mach_header_64 *header, size_t filesize, uint32_t nbcmd);
//tests.c
void		print_fat_header(void *ptr);


void do_fat(void *ptr, size_t filesize);
#endif