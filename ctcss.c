extern main();
extern flag_data_return[];
extern outport();

ctcss(int fdSer) {
    int opcode, n, tx_mode;
    float ctcss_user_value;
    float ctcss_freq[34] = {67, 71.9, 77.0, 82.5, 88.5, 94.8, 100, 103.5, 107.2, 110.9, 114.8, 118.8, 123, 127.3, 131.8, 136.5, 141.3, 146.2, 151.4, 156.7, 162.2, 167.9, 173.8, 179.9, 186.2, 192.8, 203.5, 210.7, 218.1, 225.7, 233.6, 241.8, 250.3, 9}; 
    int ctcss_byte[34] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f, 0x20, 0x31};
    rd_flags(fdSer);
    tx_mode = (flag_data_return[3] >> 7) && 0x01;
    if (tx_mode == 1) {
       printf("Cannot change CTCSS tone while transmitting!!!\n");
       return;
    }
    opcode = 0x90;
    n = 0;
    printf("Enter in Hz, the CTCSS [PL] tone -> ");
    scanf("%f",&ctcss_user_value);
    while (ctcss_user_value != ctcss_freq[n]) {
          n = n+1;
    }

/*
 *  The only way I could figure out how to do this is to have the user
 *  input the number, read it in as float and traverse an array until
 *  the numbers match.  The corresponding value in ctcss_byte is the
 *  byte the radio will understand as a valid CTCSS frequency.  I put
 *  an extra, "bogus" number on the end so that any time n = 34 or 33
 *  (the 34th or 33rd value in ctcss_freq) that means that the while 
 *  statement failed to match the value in the array, thus the value is
 *  invalid.  When the if statement finds n = 34 or n = 33, the function
 *  returns, indicating a failure.
 *  Other methods did not work, this one does so it shall be this way.
 */

    if (n == 34 || n == 33) {
       printf("Invalid value!!!\n");
       return;
    }
    outport(fdSer, ctcss_byte[n], ctcss_byte[n], ctcss_byte[n], ctcss_byte[n], opcode);
    printf("n = %d.\n", n);
}
