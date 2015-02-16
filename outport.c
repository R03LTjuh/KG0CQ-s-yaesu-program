extern main();

outport(int fdSer, int one, int two, int three, int four, int opcode) {
    
    write(fdSer,&one,1);
    write(fdSer,&two,1);
    write(fdSer,&three,1);
    write(fdSer,&four,1);
    write(fdSer,&opcode,1);
}
