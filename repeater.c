extern main();
extern flag_data_return[];
extern outport();

repeater_simplex(int fdSer) {
   int opcode, rptr_simplex, fm_byte, tx_mode;

    rd_flags(fdSer);
    tx_mode = flag_data_return[3];
    tx_mode = (tx_mode >> 7) && 0x01;
    if (tx_mode == 1) {
       printf("Cannot change FM mode while transmission in progress!!!\n");
       return;
    }
/*
 *  Off to the real function.
 */

   printf("Repeater on or off?  Include offset.\n");
   printf("1 = on with positive offset, -1 for negative offset, 0 for off -> ");
   scanf("%d", &rptr_simplex);
   if (rptr_simplex != 0 && rptr_simplex != 1 && rptr_simplex != -1) {
      printf("Invalid value!!!\n");
      return;
   } else {

/*
 *  We need to switch to FM first...Reminds me of DOS; a program
 *  that does something without your permission.  Eat your heart
 *  out Mr. Gates.
 */
      fm_byte = 0x06;
      opcode = 0x0c;
      outport(fdSer, fm_byte, fm_byte, fm_byte, fm_byte, opcode);

      if (rptr_simplex == 1) {
         rptr_simplex = 0x02;
      }
      if (rptr_simplex == -1) {
         rptr_simplex = 0x01;
      }
   }

   opcode = 0x84;
   outport(fdSer, rptr_simplex, rptr_simplex, rptr_simplex, rptr_simplex, opcode);
}
