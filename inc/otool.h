#ifndef  OTOOL_H
# define OTOOL_H

#include <universal.h>

// otool
void			otool(void *ptr, char *av, size_t filesize);

// otool_ar
void    archive_lib(void *ptr, char *av, size_t filesize);

// otool_Fat
void		do_fat_32(void *ptr, char *av);
void		do_fat_64(void *ptr, char *av);

// otool_macho
void do_bits_64(void *ptr);
void do_bits_32(void *ptr);

// otool_display
void display_m64(struct section_64 *sect, char *header);
void display_m32(struct section *sect, char *header);

//otool_mask
void				mask_32(unsigned long long n);
void				mask_64(unsigned long long n);

#endif