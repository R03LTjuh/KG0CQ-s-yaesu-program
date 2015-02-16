extern main();
extern flag_data_return[];
extern outport();

rd_flags(int fdSer) {
   int opcode, split_byte, n;

   opcode = 250;
   outport(fdSer, opcode, opcode, opcode, opcode, opcode);
   n = 1;
   while (n != 6) {
     read(fdSer,&flag_data_return[n],1);
     n = n + 1 ;
   }

   split_byte = flag_data_return[1] & 0x04;

/*  The book says that the last byte returned from the 'Read Flags' command
 *  should be 0x41.  It seems it is always 0x50.  This byte can be found
 *  in flag_data_return[5] once the read() has completed.
 */

}
