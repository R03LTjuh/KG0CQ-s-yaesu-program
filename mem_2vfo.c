extern main();
extern flag_data_return[];
extern outport();

mem_2vfo(int fdSer) {
    int opcode, memory_number, bogus, tx_mode;
    bogus = 1;

    rd_flags(fdSer);
    tx_mode = flag_data_return[3];
    tx_mode = (tx_mode >> 7) && 0x01;
    if (tx_mode == 1) {
       printf("Cannot exec M->VFO hile transmission in progress!!!\n");
       return;
    }

    printf("Enter memory channel to copy [31=p1, 32=p2] -> ");
    scanf("%d", &memory_number);

    if (memory_number > 0 && memory_number <= 32) {
       opcode = 0x06;
       printf("%d\n", opcode);
    } else {
       printf("Invalid value!!!\n");
       return;
    }
    outport(fdSer, memory_number, memory_number, memory_number, memory_number, opcode);
}
