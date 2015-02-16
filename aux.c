extern main();
extern freq_read();
extern aux_comeback;

aux(int fdSer) {
   int selector;
   printf("\n1)  status_output    - Read frequency.\n");
   printf("2)  wwv_find         - Find strongest WWV station and set frequency.\n");
   printf("3)  memory skip      - Set channel to be skipped (or not to) during scan mode.\n");
   printf("4)  hide memory      - Hide or unhide memory channel.\n");
   printf("5)  memory save      - Save all memory contents into external file.\n");
   printf("100) Return to previous menu.\n");
   printf("\nEnter selection -> ");
   scanf("%d", &selector);
   switch(selector) {
      case 1:
      stat_out(fdSer, 1);
      break;

      case 2:
      wwv_find(fdSer);
      break;

      case 3:
      mem_scsk(fdSer);
      break;

      case 4:
      mem_hide(fdSer);
      break;
 
      case 5:
      printf("This function not implemented yet.\n");
       mem_save(fdSer);
      break;

      case 100:
      aux_comeback = 1;
      return;
      break;
 
      default:
      printf("Invalid value!!!\n");
   }
   return;
}
    
