# ifndef NM_H
# define NM_H

#include <universal.h>

typedef struct			s_symdata
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
void		nm(void *ptr, char *av, size_t filesize);
					// 32 //
// loadcmd_32.c
void 		do_bits_32(void *ptr, size_t filesize);
// sections_32.c
void 		process_segment_32(struct load_command *lc, t_section **psects);
// symtable_32.c
void 		process_symtable_32(struct load_command *lc, void *ptr, t_symdata **psymbols, size_t filesize);
// sort_32.c
void 		insertion_sort(t_symdata **slist);
// mask_32.c
void		nm_mask_32(uint64_t value, uint8_t type);
					// 64 //
// loadcmd_64.c
void 		do_bits_64(void *ptr, size_t filesize);
// sections_64.c
void 		process_segment_64(struct load_command *lc, t_section **psects);
// symtable_64.c
void 		process_symtable_64(struct load_command *lc, void *ptr, t_symdata **psymbols, size_t filesize);
// sort_64.c
void 		insertion_sort(t_symdata **slist);
// mask_64.c
void		nm_mask_64(uint64_t value, uint8_t type);
					// ar_and_fat //
//ar.c
void		archive_lib(void *ptr, char *av, size_t filesize);
					// display //
// display/display
void		display_64(t_section *psects, t_symdata *psymbols);
void		display_32(t_section *psects, t_symdata *psymbols);
// display/symbols
void		display_symbol(t_section *psects, t_symdata *psymbols);
//fat
void        do_fat_32(void *ptr, size_t filesize, char *av);
void        do_fat_64(void *ptr, size_t filesize, char *av);

#endif