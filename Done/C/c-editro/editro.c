#include <editro.h>

int32_t main(int32_t argc, char *argv[])
{
	int32_t fd;
    // 디스크립터 하나 더 생성
    int32_t fd2;

	if(argc!=2) {
		printf("Usage: editro <file>\n");
		return 0;
	}

    // 읽기 전용 디스크립터를 읽기 및 쓰기로 열기
	fd = open(argv[1], O_RDWR|O_SYNC);
	if(fd<0) {
		printf("Error %d Unable to open %s\n", fd, argv[1]);
		return 0;
	}
    // 추가한 디스크립터를 원래의 디스크립터로써 읽기 전용으로 열기
    fd2 = open(argv[1], O_RDONLY|O_SYNC);
    
	Elf64_Ehdr ehdr;
	Elf64_Shdr* sh_tbl;
	
	read_elf_header(fd, &ehdr);
	
    // 읽기 전용으로 열었던 새 디스크립터로 elf 파일인지 검사하여 false 이면 프로그램 종료
    if(!is_elf(fd2)) {
		return 0;
	}
	
    // 파일 정보 출력
	print_elf_header(ehdr);

	sh_tbl = malloc(ehdr.e_shentsize * ehdr.e_shnum);
	if(!sh_tbl) {
		printf("Failed to allocate %d bytes\n", (ehdr.e_shentsize * ehdr.e_shnum));
	}
	print_section_headers(fd, ehdr, sh_tbl);

    // 정보 출력을 모두 마치고 문자열 modify
    modify(fd, ehdr, sh_tbl);
	return 0;

}

