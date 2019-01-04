#include <ft_nm.h>

static int verify_sections_32(size_t filesize, size_t checksize, struct section *sect, uint32_t nbsect)
{
    while (nbsect)
    {
        if (checksize > filesize)
            return (0);
        if ((size_t)sect->offset > filesize)
			return (0);
        checksize += sizeof(struct section);
        sect += 1;
        nbsect--;
    }
    return (1);
}

static int verify_segname_32(struct segment_command *segment)
{
    if (!(ft_strcmp(segment->segname, "__DATA"))
        || (!(ft_strcmp(segment->segname, "__TEXT"))))
    {
        if (segment->cmdsize == 0)
            return (0);
        if (segment->filesize == 0)
            return (0);
        if (segment->nsects == 0)
            return (0);
    }
    return (1);
}

static int verify_seg_32(size_t filesize, struct load_command *lc, size_t checksize)
{
    struct segment_command  *segment;
    struct section          *sect;
    uint32_t                nbsect;

    segment = (struct segment_command *)lc;
    nbsect = segment->nsects;
    sect = (struct section *)((void *)segment + sizeof(*segment));
    if (!(verify_segname_32(segment)))
        return (0);
    if (!(verify_sections_32(filesize, checksize, sect, nbsect)))
        return (0);
    return (1);
}

static int verify_lc_32_2(struct load_command *lc, size_t filesize, size_t checksize)
{
    if (lc->cmd == LC_SEGMENT)
    {
        if (!(verify_seg_32(filesize, lc, checksize)))
            return (0);
    }
    if (lc->cmd == LC_SYMTAB)
    {
        if (!(verify_symtab(lc, filesize, checksize)))
            return (0);
    }
    return (1);
}

int verify_lc_32(struct mach_header *header, size_t filesize, uint32_t nbcmd)
{
    struct load_command     *lc;
    size_t		            checksize;

    checksize = 0;
    lc = (struct load_command *)(header + 1);
    while (nbcmd)
    {
        if (checksize > filesize)
            return (0);
        if (!(verify_lc_32_2(lc, filesize, checksize)))
            return (0);
        if (lc->cmdsize % 4 != 0)
            return (0);
        checksize += (size_t)lc->cmdsize;
        lc = (void *)lc + lc->cmdsize;
        nbcmd--;
    }
    return (1);
}