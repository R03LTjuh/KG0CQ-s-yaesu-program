extern main();
extern flag_data_return[];
extern outport();

vfo_ab(int fdSer) {
    int opcode, vfo_choice, tx_mode;

    rd_flags(fdSer);
    tx_mode = flag_data_return[3];
    tx_mode = (tx_mode >> 7) && 0x01;
    if (tx_mode == 1) {
       printf("Cannot change frequency while transmission in progress!!!\n");
       return;
    }

    rd_flags(fdSer);
    vfo_choice = flag_data_return[1];
    vfo_choice = vfo_choice >> 6; 
    vfo_choice = (vfo_choice + 1) & 0x01; 
    opcode = 0x05; 
  
    if (vfo_choice != 0 && vfo_choice !=1) {
      printf("The VFO B bit value is incorrect. Serious program error!!!\n");
      return;
    }
    outport(fdSer, vfo_choice, vfo_choice, vfo_choice, vfo_choice, opcode);        
} 
