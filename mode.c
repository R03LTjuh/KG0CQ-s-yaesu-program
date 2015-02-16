extern main();
extern flag_data_return[];
extern outport();

mode (int fdSer) {
   int opcode, mode, mode_num, tx_mode, bogus;
   char cw_width, am_width;

    rd_flags(fdSer);
    tx_mode = flag_data_return[3];
    tx_mode = (tx_mode >> 7) && 0x01;
    if (tx_mode == 1) {
       printf("Cannot change mode while transmission in progress!!!\n");
       return;
    }
   printf("Input mode (single letter) -> ");
   scanf(" %s", &mode);
   mode = tolower(mode);
   switch(mode)
   {
   case 'l':
     mode_num = 0;
     break;
   case 'u':
     mode_num = 1;
     break;
   case 'c':
     printf("[w]ide or [n]arrow? -> ");
     scanf("%s", &cw_width);
     cw_width = tolower(cw_width);
     switch(cw_width) {
       case 'w':
          mode_num = 2;
          break;
       case 'n':
          mode_num = 3;
          break;
       default: 
          printf("Invalid value, wide assumed!!!\n");
          mode_num = 2;
      }
     break;

   case 'a':
     printf("[w]ide or [n]arrow? -> ");
     scanf("%s", &am_width);
     am_width = tolower(am_width);
     switch(am_width) {
       case 'w':
          mode_num = 4;
          break;
       case 'n':
          mode_num = 5;
          break;
       default: 
          printf("Invalid value, wide assumed!!!\n");
          mode_num = 4;
     }
     break;
  
    case 'f':
      mode_num = 6;
      break;
   
    default:
     printf("Invalid value!!!\n");
    }

   opcode = 0x0c; 
   outport(fdSer, mode_num, mode_num, mode_num, mode_num, opcode);
}
