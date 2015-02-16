extern main();
extern flag_data_return[];
extern outport();

vfo_2mem(int fdSer) {
    int opcode, memory_number, hide_byte, tx_mode;

    rd_flags(fdSer);
    tx_mode = flag_data_return[3];
    tx_mode = (tx_mode >> 7) && 0x01;
    if (tx_mode == 1) {
       printf("Cannot exec VFO->M while transmission in progress!!!\n");
       return;
    }
    
    opcode = 0x03;
    printf("Enter memory channel to copy to [31=p1, 32=p2] -> ");
    scanf("%d", &memory_number);
    if (memory_number <= 0 || memory_number >= 33) {
       printf("Invalid value!!!\n");
       return;
    }  
 
    hide_byte = 0x00;

    outport(fdSer, opcode, opcode, hide_byte, memory_number, opcode);   
}
