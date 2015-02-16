extern main();
extern flag_data_return[];
extern outport();

mem_rec(int fdSer) {
   int opcode;
   int memory_number, tx_mode;

    rd_flags(fdSer);
    tx_mode = flag_data_return[3];
    tx_mode = (tx_mode >> 7) && 0x01;
    if (tx_mode == 1) {
       printf("Cannot recall memory while transmission in progress!!!\n");
       return;
    }
   opcode = 0x02;
   printf("Enter the channel number to recall [31=p1, 32=p2]  -> ");
   scanf("%d", &memory_number);
   if (memory_number <= 0 || memory_number >= 33) {
      printf("Invalid value!!!\n");
      return;
   }   
   outport(fdSer, memory_number, memory_number, memory_number, memory_number, opcode);
}
