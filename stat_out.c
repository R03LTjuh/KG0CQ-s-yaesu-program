extern main();
extern data_array[];
extern data_return_param;
extern flag_data_return[];
extern memory_number;
extern mode1;
extern mode2;
extern mode3;
extern narrow1;
extern narrow2;
extern narrow3;
extern narrow4;
extern narrow5;
extern narrow6;
extern white_space;

stat_out(int fdSer, int current_freq_mode) {
/*
 *  This function is intended to be called via some other function
 *  that needs some kind of output.  current_freq_mode is the 
 *  integer used to communicate this to the function.  As different
 *  kinds of status are needed, more goto's can be added.
 */
   int opcode, vfo_a_b_op, vfo_b_op, mem_op, clar_finder, n;
   int freq_MHz, freq_kHz, freq_htHz, freq;
   float freq_fl; 

/*  Get current VFO/Memory status to base decisions on.  */ 
   rd_flags(fdSer);
   vfo_a_b_op = flag_data_return[1];
   vfo_a_b_op = (vfo_a_b_op >> 7) & 0x01;
   vfo_b_op = flag_data_return[1];
   vfo_b_op = (vfo_b_op >> 6) & 0x01;
   mem_op = flag_data_return[1];
   mem_op = (mem_op >> 5) & 0x01;

   if (current_freq_mode == 1 ) {
      goto output_freq;
   }



/*  This portion finds the current freq if needed */
output_freq: 
   if (vfo_a_b_op == 1 && vfo_b_op != 1 && mem_op == 0 ) {
      data_return_param = 3;
      stat_upd(fdSer);
      freq = (data_array[2]*65536 +  data_array[3]*256 + data_array[4]);
/*
 *      freq_MHz = freq/100000;
 *      freq_kHz = freq/100 - freq_MHz*1000; 
 *      freq_htHz =  freq - freq_MHz*100000 - freq_kHz*100;
 *      find_mode(data_array[7], data_array[9]);
 */
      freq_fl = freq;
      freq_fl = freq_fl/100000;
      find_mode(data_array[7], data_array[9]);
      printf("\nThe current VFO frequency in VFO A is %.5f MHz, operating in %c%c%c%c%c%c%c%c%c%c%c.\n", freq_fl, mode1, mode2, mode3, white_space, narrow1, narrow2, narrow3, narrow4, narrow5, narrow6); 
/*      printf("\nThe current VFO frequency in VFO A is %d.%d%d MHz, operating in %c%c%c%c%c%c%c%c%c%c%c.\n", freq_MHz, freq_kHz, freq_htHz, mode1, mode2, mode3, white_space, narrow1, narrow2, narrow3, narrow4, narrow5, narrow6); */
   }
   if (vfo_a_b_op == 1 && vfo_b_op == 1 && mem_op == 0) {
      data_return_param = 3;
      stat_upd(fdSer);
      freq = (data_array[11]*65536 +  data_array[12]*256 + data_array[13]);
/*
 *      freq_MHz = freq/100000;
 *      freq_kHz = freq/100 - freq_MHz*1000; 
 *      freq_htHz =  freq - freq_MHz*100000 - freq_kHz*100;
 */

      freq_fl = freq;
      freq_fl = freq_fl/100000;
      find_mode(data_array[16], data_array[18]);
      printf("\nThe current VFO frequency in VFO B is %.5f MHz, operating in %c%c%c%c%c%c%c%c%c%c%c.\n", freq_fl, mode1, mode2, mode3, white_space, narrow1, narrow2, narrow3, narrow4, narrow5, narrow6); 
/*      printf("\nThe current VFO frequency in VFO B is %d.%d%d MHz, operating in %c%c%c%c%c%c%c%c%c%c%c.\n", freq_MHz, freq_kHz, freq_htHz, mode1, mode2, mode3, white_space, narrow1, narrow2, narrow3, narrow4, narrow5, narrow6); */

   }
   if (vfo_a_b_op == 0 && mem_op == 1 ) {
      /*  Gotta snag the memory number and its data */
      data_return_param = 1;
      stat_upd(fdSer);
      data_return_param = 4;
      memory_number = data_array[1] + 1;
      stat_upd(fdSer);
 /*     find_mode(data_array[16]); */
       freq = (data_array[3]*65536 +  data_array[4]*256 + data_array[5]);
/*
 *      freq_MHz = freq/100000;
 *      freq_kHz = freq/100 - freq_MHz*1000; 
 *      freq_htHz =  freq - freq_MHz*100000 - freq_kHz*100;
 */
      freq_fl = freq;
      freq_fl = freq_fl/100000; 
      find_mode(data_array[16], data_array[18]);
      printf("\nThe current memory frequency displayed is %.5f MHz, operating in %c%c%c%c%c%c%c%c%c%c%c.\n", freq_fl, mode1, mode2, mode3, white_space, narrow1, narrow2, narrow3, narrow4, narrow5, narrow6); 
/*      printf("\nThe current memory frequency displayed is %d.%d%d MHz, operating in %c%c%c%c%c%c%c%c%c%c.\n", freq_MHz, freq_kHz, freq_htHz, mode1, mode2, mode3, white_space, narrow1, narrow2, narrow3, narrow4, narrow5, narrow6); */
   }
}

find_mode(data_array_n, data_array_w) {
      int am_mode, cw_mode, three;
      
       am_mode = (data_array_w >> 6) & 0x01;
       cw_mode = (data_array_w >> 7) & 0x01;
       if (am_mode == 1 || cw_mode == 1) {
          if (data_array_n == 2 || data_array_n == 3) {
             narrow1 = 'N';
             narrow2 = 'A';
             narrow3 = 'R';
             narrow4 = 'R';
             narrow5 = 'O';
             narrow6 = 'W';
             white_space = ' ';
          }
      } else {
         narrow1 = 0; 
         narrow2 = narrow1;
         narrow3 = narrow2;
         narrow4 = narrow3;
         narrow5 = narrow4;
         narrow6 = narrow5;
         white_space = 0;
     }

     switch(data_array_n) {
       case 0:
       mode1 = 'L';
       mode2 = 'S';
       mode3 = 'B';
       break;

       case 1:
       mode1 = 'U';
       mode2 = 'S';
       mode3 = 'B';
       break;

       case 2:
       mode1 = 'C';
       mode2 = 'W';
       mode3 = 0;
       break; 

       case 3:
       mode1 = 'A';
       mode2 = 'M';
       mode3 = 0;
       break;

       case 4:
       mode1 = 'F';
       mode2 = 'M';
       mode3 = 0;
       break;

      default:
      printf("Severe program error!!!\n");
     }
}
