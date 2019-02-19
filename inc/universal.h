#ifndef UNIVERSAL_H
# define UNIVERSAL_H

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

// mask.c
void		mask_32(uint64_t value);
void		mask_64(uint64_t value);
// check_file.c
int         verify_32(void *ptr, size_t filesize);
int         verify_64(void *ptr, size_t filesize);
int			check_file_content(void *ptr, size_t filesize);
int			verify_symtab_32(struct load_command *lc, size_t filesize, size_t checksize);
int 		verify_symtab_64(struct load_command *lc, size_t filesize, size_t checksize);
// check_32.c
int			verify_lc_32(struct mach_header *header, size_t filesize, uint32_t nbcmd);
// check_64
int			verify_lc_64(struct mach_header_64 *header, size_t filesize, uint32_t nbcmd);
//check_fat
int         verify_fat_32(void *ptr, size_t filesize);
int         verify_fat_64(void *ptr, size_t filesize);
// ppc / swap
uint32_t		swap_32(uint32_t n);
void			set_ppc(u_int8_t ppc);
uint32_t		ppc_32(uint32_t n);
uint64_t		ppc_64(uint64_t n);
uint8_t			*get_ppc(void);
uint64_t		swap_64(uint64_t n);

//errors.c
int			no_file(char *av);
void 		display_av(char *av);
int 		file_is_dir(char *av);
int 		invalid_object(char *av);
int			check_format(void *ptr, char *av);

#endif 