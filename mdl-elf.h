#ifndef MDL_ELF_H
#define MDL_ELF_H

#include <elf.h>
#include <link.h>
#include "mdl.h"

#if __ELF_NATIVE_CLASS == 32
#define ELFW_R_SYM ELF32_R_SYM
#define ELFW_R_TYPE ELF32_R_TYPE
#define ELFW_ST_BIND(val) ELF32_ST_BIND(val)
#define ELFW_ST_TYPE(val) ELF32_ST_TYPE(val)
#define ELFW_ST_INFO(bind, type) ELF32_ST_INFO(bind,type)
#else
#define ELFW_R_SYM ELF64_R_SYM
#define ELFW_R_TYPE ELF64_R_TYPE
#define ELFW_ST_BIND(val) ELF64_ST_BIND(val)
#define ELFW_ST_TYPE(val) ELF64_ST_TYPE(val)
#define ELFW_ST_INFO(bind, type) ELF64_ST_INFO(bind,type)
#endif

ElfW(Phdr) *mdl_elf_search_phdr (ElfW(Phdr) *phdr, int phnum, int type);
char *mdl_elf_search_file (const char *name);
struct MappedFile *mdl_elf_map_single (struct Context *context, 
				       const char *filename, 
				       const char *name);
int mdl_elf_map_deps (struct MappedFile *item);
int mdl_elf_file_get_info (uint32_t phnum,
			   ElfW(Phdr) *phdr,
			   struct FileInfo *info);
struct MappedFileList *mdl_elf_gather_all_deps_breadth_first (struct MappedFile *file);
unsigned long mdl_elf_hash (const char *n);
void mdl_elf_call_init (struct MappedFile *file);
unsigned long mdl_elf_get_entry_point (struct MappedFile *file);
void mdl_elf_reloc (struct MappedFile *file);
ElfW(Dyn) *mdl_elf_file_get_dynamic (const struct MappedFile *file, unsigned long tag);
struct SymbolMatch
{
  const struct MappedFile *file;
  const ElfW(Sym) *symbol;
};
int mdl_elf_symbol_lookup (const char *name, const struct MappedFile *file,
			   struct SymbolMatch *match);
struct MappedFile *mdl_elf_main_file_new (unsigned long phnum,
					  ElfW(Phdr)*phdr,
					  int argc, 
					  const char **argv, 
					  const char **envp);
unsigned long mdl_elf_symbol_lookup_local (const char *name, const struct MappedFile *file);

void mdl_elf_tls (struct MappedFile *file);
void mdl_elf_tcb_initialize (unsigned long sysinfo);

#endif /* MDL_ELF_H */
