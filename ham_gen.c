extern main();
extern flag_data_return[];
extern outport();

ham_gen(int fdSer) {
   int opcode, ham_gen_byte;

   rd_flags(fdSer);
   
   ham_gen_byte = flag_data_return[1];
   ham_gen_byte = (ham_gen_byte >> 1) & 0x01;
   ham_gen_byte = (ham_gen_byte + 1) & 0x01;

   opcode = 0x0d;
   if (ham_gen_byte != 1 && ham_gen_byte != 0) {
      printf("The HAM/GEN bit value is incorrect.  Serious program error!!!\n");
      return;
   }
    outport(fdSer, ham_gen_byte, ham_gen_byte, ham_gen_byte, ham_gen_byte, opcode);
}
