extern main();
extern flag_data_return[];
extern outport();

vfo_a2b(int fdSer) {
   int opcode, tx_mode;

    rd_flags(fdSer);
    tx_mode = flag_data_return[3];
    tx_mode = (tx_mode >> 7) && 0x01;
    if (tx_mode == 1) {
       printf("Cannot copy VFO's while transmission in progress!!!\n");
       return;
    }

   opcode = 0x85;
  
   outport(fdSer, opcode, opcode, opcode, opcode, opcode);   
}
