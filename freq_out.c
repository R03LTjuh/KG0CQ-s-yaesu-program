extern main();
extern float freq_to_change_to;
extern flag_data_return[];
extern outport();

freq_out(int fdSer) {
    int tens_MHz, ones_MHz, hundreds_kHz, tens_kHz, packed_oh_MkHz, ones_kHz;
    int packed_to_kHz, hundreds_Hz, tens_Hz, packed_ht_Hz, opcode, tx_mode;

    if (freq_to_change_to != 0 ) {
        goto auto_freq;
    }
    rd_flags(fdSer);
    tx_mode = flag_data_return[3];
    tx_mode = (tx_mode >> 7) && 0x01;
    if (tx_mode == 1) {
       printf("Cannot change frequency while transmission in progress!!!\n");
       return;
    }
    printf("Input MHz to jump to -> ");
    scanf(" %f", &freq_to_change_to);
    if ( freq_to_change_to > 30.0 || freq_to_change_to <= 0.00999999) {  
        /* I wish I knew why ...                           ^that was necassary */
	printf("Invalid value!!!\n");
        return;
    }

auto_freq:
/*
 *  The following line saved me from rewriting this portion
 *  of the code, I originally wrote it so the value had to be
 *  put in dHz, which few people even know what is.  Of course
 *  the time it is taking me to write this could have been 
 *  well spent on making cleaner code, oh well. Uhh...My hands hurt :P~
 */
    freq_to_change_to = freq_to_change_to*100000;
	/* We need to mask out the freq integers and BCD pack them */
    tens_MHz = freq_to_change_to/1000000;
    ones_MHz = freq_to_change_to/100000 - tens_MHz*10;
    hundreds_kHz = freq_to_change_to/10000  - tens_MHz*100 - ones_MHz*10;
    packed_oh_MkHz = ones_MHz*16 + hundreds_kHz;
    tens_kHz = freq_to_change_to/1000 - tens_MHz*1000 - ones_MHz*100  - hundreds_kHz*10;
    ones_kHz = freq_to_change_to/100 - tens_MHz*10000 - ones_MHz*1000 - hundreds_kHz*100 - tens_kHz*10;
    packed_to_kHz = tens_kHz*16 + ones_kHz;
    hundreds_Hz = freq_to_change_to/10 - tens_MHz*100000 - ones_MHz*10000 - hundreds_kHz*1000 - tens_kHz*100 - ones_kHz*10;
    tens_Hz = freq_to_change_to - tens_MHz*1000000 - ones_MHz*100000 - hundreds_kHz*10000 - tens_kHz*1000 - ones_kHz*100 - hundreds_Hz*10;
    packed_ht_Hz = hundreds_Hz*16 + tens_Hz; 
/*    printf("MHz= %x  packed_oh_MkHz= %x  packed_to_kHz= %x  packed_ht_Hz=%x\n", tens_MHz, packed_oh_MkHz, packed_to_kHz, packed_ht_Hz); */
    opcode = 0x0A;   /* freq change opcode */
    if (freq_to_change_to < 0) {
        freq_to_change_to = freq_to_change_to * -1;
    }
   outport(fdSer, packed_ht_Hz, packed_to_kHz, packed_oh_MkHz, tens_MHz, opcode);
}
