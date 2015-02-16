extern main();
extern flag_data_return[];
extern outport();

ptt(int fdSer) {
   int opcode, tx_status, cat_tx_status;

/*  We have to make sure we can tx, we need to look for tx inhibitors */
   
   rd_flags(fdSer);
   
   tx_status = flag_data_return[2];
   tx_status = (tx_status >> 2) & 0x01;
   if (tx_status != 1 && tx_status != 0) {
      printf("Serious program error!!!\n");
      return;
   }
   if (tx_status == 1) {
      printf("The transmitter is inhibited by the memory scan function.\n");
      return;
   }
   tx_status = flag_data_return[3];
   tx_status = (tx_status >> 6) & 0x01;
   if (tx_status != 1 && tx_status != 0) {
      printf("Serious program error!!!\n");
      return;
   }
   if (tx_status == 1) {
      printf("The transmitter is inhibited because the transeiver is/was tuned out of band.\n");
      return;
   }
    
/*
 *  We made it this far, now we need to find out the current tx status.
 */
   
   tx_status = flag_data_return[3];
   tx_status = (tx_status >> 7) & 0x01;
   tx_status = (tx_status + 1) & 0x01;
 
   if (tx_status != 1 && tx_status != 0) {
      printf("Serious program error!!!\n");
      return;
   } else {
     opcode = 0x0f; 
   }
  
/*
 * Toggle tx line if we can.
 */
  outport(fdSer, tx_status, tx_status, tx_status, tx_status, opcode); 

/*  Get current tx status again */

   rd_flags(fdSer);

/*  Looks like we need both cat and the other tx bit */
   
   cat_tx_status = flag_data_return[2];
   cat_tx_status = tx_status & 0x01;
   tx_status = flag_data_return[3];
   tx_status = (tx_status >> 7) & 0x01;
 
   if (tx_status != 1 && tx_status != 0) {
      printf("The tx_status bit value is incorrect. Serious program error!!!\n");
      return;
   } 
   if (cat_tx_status != 1 && cat_tx_status != 0) {
      printf("The cat_tx_status bit value is incorrect. Serious program error!!!\n");
      return;
   } else {
      if (cat_tx_status == 1) {
         printf("The transmitter is[33m[01m enabled[00m via CAT!!!\n");
      } else {
         if (tx_status == 1) {
            printf("The transmitter is already enabled via the PTT or MOX.\n");
         }
      }
   }
   if (tx_status == 0) {
      printf("The transmitter is off.\n");
   }
   rd_flags(fdSer);
   tx_status = flag_data_return[2];
   tx_status = (tx_status >> 6) & 0x01;
   if (tx_status != 1 && tx_status != 0) {
      printf("The tx_status bit value is incorrect. Serious program error!!!\n");
      return;
   }
/*
 *  Dunno if this works, no tuner.
 */

   if (tx_status == 1) {
      printf("WARNING!!!  The radio reports [33m[05mHIGH SWR!!! [00m.\n");
   }
}
