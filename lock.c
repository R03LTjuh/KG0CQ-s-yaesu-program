extern main();
extern flag_data_return[];
extern outport();

lock(int fdSer) {
    int opcode, lock_toggler;
    char locker;
    rd_flags(fdSer);
   
    lock_toggler = flag_data_return[1] & 0x01;
    lock_toggler = (lock_toggler + 1) & 0x01;
    opcode = 0x04;
    rd_flags(fdSer);
    if (lock_toggler != 0 && lock_toggler != 1) {
      printf("The lock flag bit value is incorrect.  Serious program error!!!\n");
      return;
    }
    outport(fdSer, lock_toggler, lock_toggler, lock_toggler, lock_toggler, opcode);
}
