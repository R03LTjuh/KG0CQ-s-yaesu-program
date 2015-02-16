extern main();
extern float freq_to_change_to;
extern int yaesu_return;
int aux_comeback;

void yaesu(int fdSer) {
    char decide;
    int decide_byte, bogus;
    freq_to_change_to = 0;
    aux_comeback = 0;
    printf("  1)  SPLIT         - Toggle split.\n");
    printf("  2)  FREQ          - Change frequency.\n");
    printf("  3)  RPT/T         - Switch FM on to change repeater offset or to FM simplex.\n");
    printf("  4)  METER         - Take meter reading.\n");
    printf("  5)  MODE          - Change transceiver modes.\n");
    printf("  6)  brightness    - Set display brightness.\n");
    printf("  7)  PTT           - Toggle PTT.\n");
    printf("  8)  recall memory - Recall memory channel to current VFO.\n");
    printf("  9)  VFO->M        - Copy VFO to memory channel.\n");
    printf(" 10)  LOCK          - Toggle tuner lock.\n");
    printf(" 11)  VFO A/B       - Toggle current VFO.\n");
    printf(" 12)  M->VFO        - Copy memory channel to current or last used VFO.\n");
    printf(" 13)  tuner on/off  - Switch tuner on/off.\n");
    printf(" 14)  start tuner   - Start antenna tuner.\n");
    printf(" 15)  STEP          - Step current display up or down 100 kHz or 1 MHz.\n");
    printf(" 16)  CLAR          - Toggler/adjust clarifier.\n");
    printf(" 17)  HAM/GEN       - Toggle HAM/GEN stepping function.\n");
    printf(" 18)  A=B           - Copy current VFO contents to other VFO.\n");
    printf(" 19)  rptr offset   - Switch FM on to set FM repeater offset.\n");
    printf(" 20)  CTCSS freq    - Switch to FM and set CTCSS [PL] frequency.\n");
    printf(" 21)  Auxiliary Functions.\n");
    printf("\nPlease input your selection -> ");
    scanf(" %d", &decide_byte); 
/*    decide_byte = atoi(&decide); */

    switch(decide_byte)
    {
    case 1:
    splt_tog(fdSer); 
    break;

    case 2:
    freq_out(fdSer);
    break;

    case 3:
    repeater_simplex(fdSer);
    break;

    case 4:
    meter_rd(fdSer);
    break;

    case 5:
    mode(fdSer);
    break;
 
    case 6:
    bright(fdSer);
    break;

    case 7:
    ptt(fdSer);
    break;

    case 8:
    mem_rec(fdSer);
    break;

    case 9:
    vfo_2mem(fdSer);
    break;
    
    case 10:
    lock(fdSer);
    break;

    case 11:
    vfo_ab(fdSer);
    break;
 
    case 12:
    mem_2vfo(fdSer);
    break;

    case 13:
    tuner10(fdSer);
    break;

    case 14:
    strt_tun(fdSer);
    break;

    case 15:
    step(fdSer);
    break;
   
    case 16:
    clar(fdSer);
    break;

    case 17:
    ham_gen(fdSer);
    break;

    case 18:
    vfo_a2b(fdSer);
    break;

    case 19:
    rptr_off(fdSer);
    break;

    case 20:
    ctcss(fdSer);
    break;

    case 21:
    system("/usr/bin/clear");
    while (aux_comeback != 1) {
    (void) aux(fdSer);
    }
    break;
   
    case 100:
    yaesu_return = 0;
    return; 
    break;

    default:
      printf("Invalid value!!!\n");
    }
}
