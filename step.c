extern main();
extern flag_data_return[];
extern outport();

step(int fdSer) {
    int opcode, stepper, param_byte, up_down, tx_mode;
    char step_decide;

    rd_flags(fdSer);
    tx_mode = flag_data_return[3];
    tx_mode = (tx_mode >> 7) && 0x01;
    if (tx_mode == 1) {
       printf("Cannot change frequency while transmission in progress!!!\n");
       return;
    }
    param_byte = 0;
    printf("Step up or down? [u=up, d=down] -> ");
    scanf("%s", &step_decide);
    if (step_decide == 'u' || step_decide == 'd') {
       if (step_decide == 'u') {
           opcode = 0x07;
           } else {
           opcode = 0x08;
        }
        printf("Step in an increment of? [k=100kHz, M=1MHz] -> ");
        scanf("%s", &step_decide);
        if (step_decide == 'k' || step_decide == 'M') {
           if (step_decide == 'k') {
              stepper = 0;
              } else {
             stepper = 1;
            }
        } else {
          printf("Invalid value!!!\n");
          return;
        }
      } else {
        printf("Invalid value!!!\n");
        opcode = 0x00;
      }
    outport(fdSer, stepper, stepper, stepper, param_byte, opcode);
}
