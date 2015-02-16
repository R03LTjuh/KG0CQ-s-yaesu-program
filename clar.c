extern main();
extern data_array[];
extern data_return_param;
extern flag_data_return[];
extern memory_number;
extern outport();

clar(int fdSer) {
   int opcode, vfo_a_b_op, vfo_b_op, mem_op, clar_finder, n, kHz_freq, Hz_freq;
   int up_down, dummy;

/*  Get current VFO/Memory status to base decisions on.  */ 
   rd_flags(fdSer);
   vfo_a_b_op = flag_data_return[1];
   vfo_a_b_op = (vfo_a_b_op >> 7) & 0x01;
   vfo_b_op = flag_data_return[1];
   vfo_b_op = (vfo_b_op >> 6) & 0x01;
   mem_op = flag_data_return[1];
   mem_op = (mem_op >> 5) & 0x01;
   n = 1;

   if (vfo_a_b_op == 1 && vfo_b_op != 1 && mem_op == 0) {
      /*  For VFO A */
      data_return_param = 3;
      stat_upd(fdSer);
      clar_finder = (data_array[9] >> 5) & 0x01;
   }
   if (vfo_a_b_op == 1 && vfo_b_op == 1 && mem_op == 0) {
      /*  For VFO B */
      data_return_param = 3;
      stat_upd(fdSer);
      clar_finder = (data_array[18] >> 5) & 0x01;
   }
   if (vfo_a_b_op == 0 && mem_op == 1) {
      /*  For MEM */
      data_return_param = 1;
      stat_upd(fdSer);
      data_return_param = 4;
      memory_number = data_array[1] + 1;
      stat_upd(fdSer);
      clar_finder = (data_array[10] >> 5) & 0x01;
/*
 *  When in memory mode...
 *  clar_finder only tells us that clarifier is set in MEMORY, not if
 *  it is ACTUALLY in use or not, too bad.  There must be a way.
 */

   }
   if (clar_finder == 0) {
      dummy = 0x06;
      opcode = 0x09;
      clar_finder = 0x01;
      outport(fdSer, dummy, dummy, dummy, clar_finder, opcode);
/*  
 *  Here is where we try and set the clarifier if it is on.
 */

/*
 *      sleep (2);
 *     up_down = 0x00; 
 *     kHz_freq = 0x02;
 *     Hz_freq = 0xe1;
 *     dummy = 255;
 *     outport(fdSer, Hz_freq, kHz_freq, up_down, dummy, opcode);
 */
   } else {
      opcode = 0x09;
      clar_finder = 0x00;
      outport(fdSer, clar_finder, clar_finder, clar_finder, clar_finder, opcode);
   }
}
