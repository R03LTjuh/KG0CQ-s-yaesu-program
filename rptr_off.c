extern main();
extern flag_data_return[];
extern outport();

rptr_off(int fdSer) {
    int hundreds_kHz, tens_kHz, ones_kHz, fm_byte, tx_mode;
    int packed_to_kHz, hundreds_Hz, tens_Hz, packed_ht_Hz, opcode;
    float freq;

    rd_flags(fdSer);
    tx_mode = flag_data_return[3];
    tx_mode = (tx_mode >> 7) && 0x01;
    if (tx_mode == 1) {
       printf("Cannot change frequency while transmission in progress!!!\n");
       return;
    }

    printf("Input kHz to offset -> ");
    scanf("%f", &freq);
    if ( freq > 200.0 || freq < 0.0) {  
	printf("Invalid value!!!\n");
        return;
    }
    fm_byte = 0x06;
    opcode = 0x0c;
    outport(fdSer, fm_byte, fm_byte, fm_byte, fm_byte, opcode);
/*
 *  The following line saved me from rewriting this portion
 *  of the code, I originally wrote it so the value had to be
 *  put in dHz, which few people even know what is.  Of course
 *  the time it is taking me to write this could have been 
 *  well spent on making cleaner code, oh well. Uhh...My hands hurt :P~
 */

    freq = freq*1000;
	/* We need to mask out the freq integers and BCD pack them */
    hundreds_kHz = freq/100000;
    tens_kHz = freq/10000 - hundreds_kHz*10;
    ones_kHz = freq/1000 - hundreds_kHz*100 - tens_kHz*10;
    packed_to_kHz = tens_kHz*16 + ones_kHz;
    hundreds_Hz = freq/100 - hundreds_kHz*1000 - tens_kHz*100 - ones_kHz*10;
    tens_Hz = freq/10 - hundreds_kHz*10000 - tens_kHz*1000 - ones_kHz*100 - hundreds_Hz*10;
    packed_ht_Hz = hundreds_Hz*16 + tens_Hz; 
    /* printf("ones_kHz = %x, hundreds_Hz = %x, tens_Hz = %x\n", ones_kHz, hundreds_Hz, tens_Hz); */
    printf(" hundreds_kHz = %x  packed_to_kHz= %x  packed_ht_Hz=%x\n", hundreds_kHz, packed_to_kHz, packed_ht_Hz);
    opcode = 0x0f9;   /* freq change opcode */
    fm_byte = 0x00;  /* may as well use it again */

   outport(fdSer, packed_ht_Hz, packed_to_kHz, hundreds_kHz, fm_byte, opcode);
   write(fdSer,&packed_ht_Hz,1);
   write(fdSer,&packed_to_kHz,1);
   write(fdSer,&hundreds_kHz,1);
   write(fdSer,&fm_byte,1);
   write(fdSer,&opcode,1);
  
}
