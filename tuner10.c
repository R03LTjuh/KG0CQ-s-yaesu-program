extern main();
extern flag_data_return[];
extern outport();

tuner10(int fdSer) {
   /*
    *  I do not know if this function works, I do not have a 
    *  tuner to test it with.
    */

   int opcode, on_off;
   rd_flags(fdSer);

   opcode = 0x81;
   on_off = flag_data_return[3];
   on_off = (on_off >> 4) & 0x01;
   on_off = (on_off + 1) & 0x01;
   
 
   if (on_off != 1 && on_off != 0) {
      printf("The tuner on/off bit value is incorrect. Serious program error!!!?\n");
      return;
   }
   outport(fdSer, on_off, on_off, on_off, on_off, opcode);
}
