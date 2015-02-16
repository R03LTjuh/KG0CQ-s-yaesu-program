extern main();
extern flag_data_return[];
extern outport();

int meter_rd(int fdSer) {
  int opcode, tx_status, n;
  char meter_value[5];
 
   opcode = 250;
   rd_flags(fdSer);
   tx_status = flag_data_return[3];
   tx_status = (tx_status >> 7) & 0x01;
 
   if (tx_status != 1 && tx_status != 0) {
      printf("The tx_status bit value is incorrect.  Serious program error!!!\n");
      return;
   } else {
     opcode = 0x0f7; 
   }
   
   if (tx_status == 1) {
      printf("The transmitter is on!!!  The meter_value shows relative power output.\n");
   }



  opcode = 0x0F7; 
  outport(fdSer, opcode, opcode, opcode, opcode, opcode);
  
  n = 1; 
  while (n !=6) {
    read(fdSer,&meter_value[n],1);
    n = n +1;
  } 
  if (meter_value[5] != 0x0f7) {
     printf("The dummy byte returned to the meter_rd function is incorrect, possible serial port noise?\n");
     } else {
     printf("\nCurrent meter value is [33m[01m%x. [00mRange is 0..0ffh.\n", meter_value[3]);
  }
  return(meter_value[3]);
}
