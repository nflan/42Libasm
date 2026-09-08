%ifndef PLATFORM_INC
%define PLATFORM_INC

%ifidn __OUTPUT_FORMAT__, elf64
 %define NAME(x) x
 %define ERRNO_FN __errno_location
 %define SYS_READ 0
 %define SYS_WRITE 1
%else
 %define NAME(x) _ %+ x
 %define ERRNO_FN ___error
 %define SYS_READ 0x2000003
 %define SYS_WRITE 0x2000004
%endif

%endif
