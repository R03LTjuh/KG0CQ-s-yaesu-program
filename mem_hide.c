extern main();
extern outport();

mem_hide(int fdSer) {
    int opcode, memory_number, hide_byte;
    char hide_char;
    
    printf("Enter memory channel modify [31=p1, 32=p2] -> ");
    scanf("%d", &memory_number);

    if (memory_number <= 0 || memory_number >= 33) {
       printf("Invalid value!!!\n");
       return; 
    }  
    printf("Hide or unhide channel? [h=hide, u=unhide] -> ");
    scanf("%s", &hide_char);
    if (hide_char == 'h' || hide_char == 'u') { 
       opcode = 0x03;
       if (hide_char == 'h') {
          hide_byte = 0x01;
          } else {
            hide_byte = 0x02;
          }
       } else {
       printf("Invalid value!!!\n");
       opcode = 0x00;     /* invalid, opcode must do nothing */
    }
    outport(fdSer, opcode, opcode, hide_byte, memory_number, opcode);
}
