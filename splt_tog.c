extern main();
extern flag_data_return[];
extern outport();

splt_tog(int fdSer) {
   int opcode, split_toggler, split_byte, tx_mode;
    rd_flags(fdSer);
    tx_mode = flag_data_return[3];
    tx_mode = (tx_mode >> 7) && 0x01;
    if (tx_mode == 1) {
       printf("Cannot toggle split while transmission in progress!!!\n");
       return;
    }

/*
 *  Here we capture the flag byte to get the split on/off bit
 */

   rd_flags(fdSer);

/*
 *  Now we need to mask out other bits and get only the split bit,
 *  so we can complement it and send it out the port.  This is a 
 *  very messy way to complement a bit, too much time to think
 *  through it :^)
 */

   split_byte = flag_data_return[1] & 0x04;
   split_byte = split_byte >> 2;
   opcode = 1;

/*
 * A little safety check.
 */

   if (split_byte != 1 && split_byte != 0) {
      printf("The split flag bit value is incorrect.  Serious program error!!!\n");
      return;
   }
   split_byte = (split_byte + 1) & 0x01;

 /*
  *  We got the bit, now we can toggle it based on that value.
  */
   outport(fdSer, split_byte, split_byte, split_byte, split_byte, opcode);
}
