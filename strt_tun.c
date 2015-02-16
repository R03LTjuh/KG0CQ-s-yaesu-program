extern main();
extern flag_data_return[];
extern outport();

strt_tun(int fdSer) {

  /* 
   * I do not know if this function works, I do not have
   *  an antenna tuner.
   */

   int opcode, tuner_status;
   rd_flags(fdSer);
   
   tuner_status = flag_data_return[2];
   tuner_status = (tuner_status >> 5) & 0x01;
 
   if (tuner_status != 1 && tuner_status != 0) {
      printf("The tuner_status bit value is incorrect.  Serious program error!!!\n");
      return;
   } else {
     if (tuner_status == 1) {
        printf("Cannot start tuner, tuning in progress!!!\n");
        return;
     } else {
       opcode = 0x82;
     }
   }
   outport(fdSer, opcode, opcode, opcode, opcode, opcode);   
}
