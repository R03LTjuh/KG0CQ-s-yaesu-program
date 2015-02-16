#include <sys/file.h>
#include <stdio.h>
#include <config.h>
extern main();
extern stat_upd();
extern rd_flags();
extern int data_return_param;
extern data_array[];
extern outport();

mem_save(int fdSer) {
    int opcode, n, freq;
    int memory_contents[650];
    FILE *mem_fd;
    int jack;
    opcode = 0x10;
    data_return_param = 0;
    stat_upd(fdSer);
/*
 *  We are only interested in the last 608 bytes in data_array[].
 */
    mem_fd = fopen("./memory.dat", "w");
    fwrite(data_array,1,650,mem_fd);
    fread(memory_contents,1,649,mem_fd);
    fclose(mem_fd);
    n = 1;
    while (n != 650) {
         printf("%x   %x.\n", data_array[n], memory_contents[n]);
         n = n + 1;
    }
    freq = (memory_contents[6]*65536 + memory_contents[7]*256 + memory_contents[8]); 
    printf("freq is %d.\n", freq);
}
