#include <unistd.h>
#include <sys/time.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <termios.h>
#include <signal.h>
#include<sys/io.h>
#include <config.h>
float freq_to_change_to;
char flag_data_return[5];
char data_array[650];
int data_return_param;
int memory_number;
int yaesu_return;
char mode1, mode2, mode3;
char narrow1, narrow2, narrow3, narrow4, narrow5, narrow6;
char white_space;

int main(int argc, char* argv[]) {
    static char version[] = "yaesu v .11lx.  May 19th, 1995.  Author: Emarit Ranu, KG0CQ.";
    int fdSer; 				/* serial file descriptor integer */
    int zero_port_byte;
    char flag_data_return[5];
    struct termios termattribs;
    struct termios *defaults_serial;
    extern splt_tog();
    extern freq_out();
    extern mem_rec();
    extern vfo_2mem();
    extern mem_hide();
    extern mem_2vfo();
    extern step();
    extern lock();
    extern vfo_ab();
    extern clar();
    extern ham_gen();
    extern ptt();
    extern tuner10();
    extern stat_up();
    extern bright();
    extern mode();
    extern strt_tun();
    extern meter_rd();
    extern rd_flags();
    extern rptr_off();
    extern reptear();
    extern ctcss();
    extern stat_out();
    extern aux();
    extern wwv_find();
    extern outport();
    void yaesu(); 
    void cleanup();
    signal(SIGINT, cleanup);
    yaesu_return = 1;

    fdSer = port_open(argc, argv);   /* grab the port fd */
    if (fdSer == -1) {
        exit(3);
    }
    tcgetattr(fdSer,defaults_serial);      /* save current serial settings */

    termattribs.c_iflag = IGNBRK | IGNPAR | IMAXBEL | IXOFF;
    termattribs.c_oflag = 0;  
    termattribs.c_cflag = CS8 | CSTOPB | CREAD | CLOCAL;
    termattribs.c_lflag = 0;		    /* Set some term flags */
    
    /*  The ensure there are no read timeouts (possibly writes?) */
    termattribs.c_cc[VMIN] = 1; 
    termattribs.c_cc[VTIME] = 0;
        
    cfsetispeed(&termattribs,B4800);	    /* Set input speed */
    cfsetospeed(&termattribs,B4800);	    /* Set output speed */
    tcsetattr(fdSer,TCSANOW,&termattribs);  /* Set the serial port */

    zero_port_byte = 0x00;
/*    system("/usr/bin/clear"); */

    /*  flush data on port  */
    write(fdSer,&zero_port_byte,1);
    write(fdSer,&zero_port_byte,1);
    write(fdSer,&zero_port_byte,1);
    write(fdSer,&zero_port_byte,1);
    write(fdSer,&zero_port_byte,1);
    pacing(fdSer);
    printf("To terminate the program, enter 100.\n");
    while (yaesu_return == 1) {
       yaesu(fdSer);
    }
    bye_msg();
}

/*
 *  This function returns the fd for the serial port.
 */
port_open(int argc, char* argv[]) {
    int fdSer;

    if (argc == 2) {
       switch(argv[1][0]) {
             case '0':
             if ((fdSer = open("/dev/ttyS0", O_RDWR )) < 0) {
                perror("open of /dev/ttyS0 failed!!!\n");
                exit(3);
             }
             break;

             case '1':
             if ((fdSer = open("/dev/ttyS1", O_RDWR )) < 0) {
                perror("open of /dev/ttyS1 failed!!!\n");
                exit(3);
             }
             break;

             case '2':
             if ((fdSer = open("/dev/ttyS2", O_RDWR )) < 0) {
                perror("open of /dev/ttyS2 failed");
                exit(3);
             }
             break;

             case '3':
             if ((fdSer = open("/dev/ttyS3", O_RDWR )) < 0) {
                perror("open of /dev/ttyS3 failed");
                exit(3);
             }
             break;
             default:
             printf("Invalid serial port number!!!\n  Remember:  com1 is 0, com2 is 1, etc.\n");
             return(-1);
       }
    } else {
       printf("usage:  yaesu [port #]\n");
       exit(3);
    }
    return(fdSer);
}

bye_msg() {

printf("\n Thank you for using KG0CQ's 'yaesu' program, this is version .1lx.  You may use this program for as long as you like, it will always be free to use, no matter what version.  You may distribute this program freely so long as it distributed in and with the original zipfile or tar file.  Please do not distribute modifed versions.  A nice Windows version, DOS console version, Linux console, and Linux X version should be on their way in the coming months.  If you wish to support the author's efforts just say thanks via email or packet!  email:   drranu@holly.ColoState.EDU or packet:  KG0CQ@KF0UW.#NECO.USA.NOAM Having fun hamming, hope to catch you on the air!!!\n\n");

}

void
cleanup(int fdSer, struct termios *defaults_serial)
{
  tcsetattr(fdSer, TCSANOW, defaults_serial); 
  close(fdSer);
  bye_msg();
  printf("Killed by signal 2!\n"); 
  exit(3);
}
