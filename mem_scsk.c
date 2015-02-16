extern main();

mem_scsk(int fdSer) {
    int opcode, memory_channel, scanning_include;
 
    opcode = 0x8d;
    printf("Enter memory channel to include or not to include in scanning [p1=31, p2=32]\n -> ");
    scanf("%d", &memory_channel);
    if (memory_channel < 1 || memory_channel > 32) {
       printf("Invalid value!!!\n");
       return;
    }

    printf("Enter 1 to skip or 0 to include -> ");
    scanf("%x", &scanning_include);
    if (scanning_include !=0 && scanning_include !=1) {
       printf("Invalid value!!!\n");
       return;
    }
    outport(fdSer, scanning_include, scanning_include, scanning_include, memory_channel, opcode);
}
