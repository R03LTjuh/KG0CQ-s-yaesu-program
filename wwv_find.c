extern main();
extern float freq_to_change_to;
extern flag_data_return[];

wwv_find(int fdSer) {
    float new;
    int find, meter[5], tx_mode;

    rd_flags(fdSer);
    tx_mode = flag_data_return[3];
    tx_mode = (tx_mode >> 7) && 0x01;
    if (tx_mode == 1) {
       printf("Cannot search for WWV stations while transmission in progress!!!\n");
       return;
    }


    freq_to_change_to = 2.5;
    freq_out(fdSer, freq_to_change_to);
    sleep(1);
    meter[1] = meter_rd(fdSer);
    find = meter[1];
    new = freq_to_change_to;

    freq_to_change_to = 5; 
    freq_out(fdSer);
    sleep(1);
    meter[2] = meter_rd(fdSer);
    if (find < meter[2]) {
       find = meter[2];
       new = freq_to_change_to;
    }

    freq_to_change_to = 10; 
    freq_out(fdSer);
    sleep(1);
    meter[3] = meter_rd(fdSer);
    if (find < meter[3]) {
       find = meter[3];
       new = freq_to_change_to;
    }

    freq_to_change_to = 15; 
    freq_out(fdSer);
    sleep(1);
    meter[4] = meter_rd(fdSer);
    if (find < meter[4]) {
       find = meter[4];
       new = freq_to_change_to;
    }

    freq_to_change_to = 20; 
    freq_out(fdSer);
    sleep(1);
    meter[5] = meter_rd(fdSer);
    if (find < meter[5]) {
       find = meter[5];
       new = freq_to_change_to;
    }
    freq_to_change_to = new/100000;
    printf("The strongest WWV station is %.1f MHz.\n", freq_to_change_to);
    freq_out(fdSer);
}
