#include <ft_nm.h>

#define SWAP32(x) ((((x) & 0xff000000) >> 24) | (((x) & 0xff0000) >> 8) | (((x) & 0xff00) << 8) | (((x) & 0xff) << 24))

void print_fat_header(void *buf)
{
    struct fat_header *hdr = buf;
    if(hdr->magic != FAT_CIGAM)
    {
        fprintf(stderr, "bad magic: %08x\n", hdr->magic);
        return;
    }
    struct fat_arch *archs = (struct fat_arch*)(hdr + 1);
    uint32_t num = SWAP32(hdr->nfat_arch);
    for(size_t i = 0; i < num; ++i)
    {
        const char *name = "unknown";
        switch(SWAP32(archs[i].cputype))
        {
            case CPU_TYPE_I386:     name = "i386";      break;
            case CPU_TYPE_X86_64:   name = "x86_64";    break;
            case CPU_TYPE_ARM:      name = "arm";       break;
            case CPU_TYPE_ARM64:    name = "arm64";     break;
            case CPU_TYPE_POWERPC64: name = "ppc64";     break;
            case CPU_TYPE_POWERPC:   name = "ppc";       break;
        }
        uint32_t off = SWAP32(archs[i].offset);
        uint32_t magic = *(uint32_t*)((uintptr_t)buf + off);
        printf("%08x-%08x: %-8s (magic %8x)\n", off, off + SWAP32(archs[i].size), name, magic);
    }
}
