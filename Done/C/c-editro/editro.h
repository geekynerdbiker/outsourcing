#include <stdio.h>
#include <assert.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>
#include <elf.h>

bool is_elf(int32_t fd);
void read_elf_header(int32_t fd, Elf64_Ehdr *elf_header);
void print_elf_header(Elf64_Ehdr elf_header);
char *read_section(int32_t fd, Elf64_Shdr sh);
void print_section_headers(int32_t fd, Elf64_Ehdr eh, Elf64_Shdr sh_table[]);
void modify(int32_t fd, Elf64_Ehdr eh, Elf64_Shdr sh_table[]);

//Implement this function to check whether an input file is an elf file or not.
// 파일이 elf인지 확인
bool is_elf(int32_t fd)
{
    char buffer[4]; // magic number를 캐릭터 배열
    read(fd, buffer, sizeof(char) * 4); // 파일로부터 4바이트를 읽음
    
    if (buffer[0] == 0x7f && buffer[1] == 0x45 && buffer[2] == 0x4c && buffer[3] == 0x46) { // magic number를 비교하여 elf 파일이 맞는 경우, True를 출력 및 반환
        printf("ELF File: True\n");
        return true;
    } else { // 그렇지 않은 경우 False를 출력 및 반환
        printf("ELF File: False\n");
        return false;
    }
        
}

void read_elf_header(int32_t fd, Elf64_Ehdr *elf_header)
{
    assert(elf_header != NULL);
    assert(lseek(fd, (off_t)0, SEEK_SET) == (off_t)0);
    assert(read(fd, (void *)elf_header, sizeof(Elf64_Ehdr)) == sizeof(Elf64_Ehdr));
}

void print_elf_header(Elf64_Ehdr elf_header)
{
    printf("Storage class\t= ");
    switch(elf_header.e_ident[EI_CLASS])
    {
        case ELFCLASS32:
            printf("32-bit objects\n");
            break;

        case ELFCLASS64:
            printf("64-bit objects\n");
            break;

        default:
            printf("Unknwon CLASS\n");
            break;
    }

    printf("Data format\t= ");
    switch(elf_header.e_ident[EI_DATA])
    {
        case ELFDATA2LSB:
            printf("2's complement, little endian\n");
            break;

        case ELFDATA2MSB:
            printf("2's complement, big endian\n");
            break;

        default:
            printf("Unknwon Format\n");
            break;
    }

    printf("OS ABI\t\t= ");
    switch(elf_header.e_ident[EI_OSABI])
    {
        case ELFOSABI_SYSV:
            printf("UNIX System V ABI\n");
            break;

        case ELFOSABI_HPUX:
            printf("HP-UX\n");
            break;

        case ELFOSABI_NETBSD:
            printf("NetBSD\n");
            break;

        case ELFOSABI_LINUX:
            printf("Linux\n");
            break;

        case ELFOSABI_SOLARIS:
            printf("Sun Solaris\n");
            break;

        case ELFOSABI_AIX:
            printf("IBM AIX\n");
            break;

        case ELFOSABI_IRIX:
            printf("SGI Irix\n");
            break;

        case ELFOSABI_FREEBSD:
            printf("FreeBSD\n");
            break;

        case ELFOSABI_TRU64:
            printf("Compaq TRU64 UNIX\n");
            break;

        case ELFOSABI_MODESTO:
            printf("Novell Modesto\n");
            break;

        case ELFOSABI_OPENBSD:
            printf("OpenBSD\n");
            break;

        case ELFOSABI_ARM_AEABI:
            printf("ARM EABI\n");
            break;

        case ELFOSABI_ARM:
            printf("ARM\n");
            break;

        case ELFOSABI_STANDALONE:
            printf("Standalone (embedded) app\n");
            break;

        default:
            printf("Unknown (0x%x)\n", elf_header.e_ident[EI_OSABI]);
            break;
    }

    printf("Filetype \t= ");
    switch(elf_header.e_type)
    {
        case ET_NONE:
            printf("N/A (0x0)\n");
            break;

        case ET_REL:
            printf("Relocatable\n");
            break;

        case ET_EXEC:
            printf("Executable\n");
            break;

        case ET_DYN:
            printf("Shared Object\n");
            break;
        default:
            printf("Unknown (0x%x)\n", elf_header.e_type);
            break;
    }

    printf("Machine\t\t= ");
    switch(elf_header.e_machine)
    {
        case EM_NONE:
            printf("None (0x0)\n");
            break;

        case EM_386:
            printf("INTEL x86 (0x%x)\n", EM_386);
            break;

        case EM_X86_64:
            printf("AMD x86_64 (0x%x)\n", EM_X86_64);
            break;

        case EM_AARCH64:
            printf("AARCH64 (0x%x)\n", EM_AARCH64);
            break;

        default:
            printf(" 0x%x\n", elf_header.e_machine);
            break;
    }
    printf("\n");
}

char *read_section(int32_t fd, Elf64_Shdr sh)
{
    char* buff = malloc(sh.sh_size);
    if(!buff) {
        printf("%s:Failed to allocate %ldbytes\n",
                __func__, sh.sh_size);
    }

    assert(buff != NULL);
    assert(lseek(fd, (off_t)sh.sh_offset, SEEK_SET) == (off_t)sh.sh_offset);
    assert(read(fd, (void *)buff, sh.sh_size) == sh.sh_size);

    return buff;
}

void print_section_headers(int32_t fd, Elf64_Ehdr eh, Elf64_Shdr sh_table[])
{
    uint32_t i;
    char* sh_str;

    assert(lseek(fd, (off_t)eh.e_shoff, SEEK_SET) == (off_t)eh.e_shoff);

    for(i=0; i<eh.e_shnum; i++) {
        assert(read(fd, (void *)&sh_table[i], eh.e_shentsize) == eh.e_shentsize);
    }

    /* section-header string-table */
    sh_str = read_section(fd, sh_table[eh.e_shstrndx]);

    for(i=0; i<eh.e_shnum; i++) {
        if(!strncmp((sh_str + sh_table[i].sh_name), ".rodata", 7))
        {
            printf("%s section info\n", (sh_str + sh_table[i].sh_name));
            printf("    file offset = 0x%08lx\n", sh_table[i].sh_offset);
            printf("           size = 0x%08lx\n", sh_table[i].sh_size);
        }
    }

}

// "difficult!" 문자열을 "funny!" 문자열로 바꾸는 함수
void modify(int32_t fd, Elf64_Ehdr eh, Elf64_Shdr sh_table[]) {
    uint32_t i;
    char *sh_str;

    // 디스크립터의 커서를 맨앞으로부터 eh.e_shoff 만큼 이동함. 성공시 무시, 실패시 프로그램 종료
    assert(lseek(fd, (off_t) eh.e_shoff, SEEK_SET) == (off_t) eh.e_shoff);

    for (i = 0; i < eh.e_shnum; i++)
        assert(read(fd, (void *) &sh_table[i], eh.e_shentsize) == eh.e_shentsize);

    // 섹션헤더 테이블
    sh_str = read_section(fd, sh_table[eh.e_shstrndx]);

    // rodata 위치 및 크기
    off_t offset = 0;
    off_t size = 0;
    // 비교할 문자열
    char buf[strlen("difficult!")];

    // rodata 정보 확인
    for (i = 0; i < eh.e_shnum; i++)
        if (!strncmp((sh_str + sh_table[i].sh_name), ".rodata", strlen(".rodata"))) {
            // 사이즈 및 크기 비교 갱신
            size = sh_table[i].sh_size;
            offset = sh_table[i].sh_offset;
        }

    // rodata 내에서 문자열 탐색
    for (int j = 0; j < size - strlen("difficult!"); ++j) {
        // 커서를 한칸씩 이동하며 문자열의 시작점을 찾음
        lseek(fd, (off_t) offset + j, SEEK_SET);
        // 커서의 위치부터 문자열의 크기만큼 읽어 버퍼에 저장
        read(fd, buf, sizeof(char) * strlen("difficult!"));

        // 해당 문자열을 찾았다면,
        if (!strncmp(buf, "difficult!", strlen("difficult!"))) {
            // 커서를 문자열의 시작위치로 옮기고,
            lseek(fd, (off_t) offset + j, SEEK_SET);
            // 새로운 문자열을 덮어씀
            write(fd, "funny!\0", sizeof(char) * strlen("difficult!"));
        }
    }
}
