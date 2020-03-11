#ifndef INC_ELF_H
#define INC_ELF_H

struct elf_header{
    uint32_t e_magic; // 标识文件是否是 ELF 文件
    uint8_t e_elf[12]; // 魔数和相关信息
    uint16_t e_type; // 文件类型
    uint16_t e_machine;// 针对体系结构
    uint32_t e_version; // 版本信息
    uint32_t e_entry; // Entry point 程序入口点，是虚拟的链接地址
    uint32_t e_phoff; // 程序头表偏移量，是程序头表的第一项相对于 ELF 文件的开始位置的偏移
    uint32_t e_shoff; // 节头表偏移量
    uint32_t e_flags; // 处理器特定标志
    uint16_t e_ehsize; // 文件头长度
    uint16_t e_phentsize;// 程序头部长度
    uint16_t e_phnum; // 程序头部表项个数
    uint16_t e_shentsize;// 节头部长度
    uint16_t e_shnum; // 节头部个数
    uint16_t e_shstrndx; // 节头部字符索引
};

struct prog_header{
    uint32_t p_type; // 段类型
    uint32_t p_offset; // 段位置相对于 ELF 文件开始处的偏移量，标识出了磁盘位置(相对的位置，这里没有包括 ELF 文件之前的磁盘)
    uint32_t p_va; // 段放置在内存中的地址(虚拟的链接地址)
    uint32_t p_pa; // 段的物理地址
    uint32_t p_filesz; // 段在文件中的长度
    uint32_t p_memsz; // 段在内存中的长度
    uint32_t p_flags; // 段标志
    uint32_t p_align; // 段在内存中的对齐标志
};

#endif
