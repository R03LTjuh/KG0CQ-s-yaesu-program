extern main();
extern data_array[];
extern data_return_param;
extern memory_number;
extern outport();

stat_upd(int fdSer) {
  int opcode, data_return_size;
  int n;
/*
 *  This function can only be called from external functions
 *  because data_return_param must be the value desired.
 */

 /*  We need to determine how many bytes to read */
  switch (data_return_param)
  {
  case 0: 
  data_return_size = 649;
  break;
  case 1:
  data_return_size = 1;
  break;
  case 2:
  data_return_size = 19;
  break;
  case 3:
  data_return_size = 18;
  break;
  case 4:
  data_return_size = 19;
  break;
  default:
  printf("Severe program error!!!\n");
  data_return_size = 0;
  }
  opcode = 16;
  outport(fdSer, memory_number, data_return_param, data_return_param, data_return_param, opcode);

  n = 1;
  while(n != data_return_size+1) {  
     read(fdSer,&data_array[n],1);
     n = n + 1; 
  }  
}
