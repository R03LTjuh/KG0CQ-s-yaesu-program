# KG0CQ-s-yaesu-program
Emarit Ranu - KG0CQ: I no longer maintain it so I  would encourage you to release your own updated version.

-----------------------
Copying:

Previously this program had some restrictions, however the following policy
supercedes any previously published now under:
GNU GENERAL PUBLIC LICENSE
Version 3, 29 June 2007
readable below
http://www.gnu.org/copyleft/gpl.html

-----------------------

KG0CQ's 'yaesu' program.  v.14 README file.

on january 2015
nl13729 R. Adema updated some code readable in CHANGELOG2015
So it would support 64bit architecture
and could support other architectures
understanding architecture makefile support

------------------------
Overview:

This is my program to control a Yaesu FT-890 HF transceiver via its CAT port
and an RS-232C (com port) on your computer.  Please see the bugs list, 
disclaimer and copying section below.  I wrote it to learn some C and hoped
someone would use it to build a GUI since it is function based.  The code is
probably dirty, but it works!  Functionality is broad, but the user interface
is lacking.
I can envision using this program, or some derivation thereof, to remotely
control a transceiver with streaming audio for a remote base and/or cross band
repeater of some sort (within the rules governing the amateur service).

-------------------------

usage support below
> ~/git/yaesu$ make < wait till make is done
> ~/git/yaesu$ sudo ln ./yaesu /usr/local/bin/yaesu
if already exist becouse of other yaesu program name it

:~/git/yaesu$ sudo rm /dev/ttyS0 < if already exist and not in use or use other tty order like 1 , 2 to 100
below
:~/git/yaesu$ sudo ln -s /dev/ttyUSB0 /dev/ttyS0 
:~/git/yaesu$ sudo chmod 666 /dev/ttyS0 

:~/git/yaesu$ ./yaesu 
> usage:  yaesu [port #]

and you should be able to work it on USB cable to
~/git/yaesu$ ./yaesu 0
> To terminate the program, enter 100. 
>   1)  SPLIT         - Toggle split. 
>   2)  FREQ          - Change frequency. 
>   3)  RPT/T         - Switch FM on to change repeater offset or to FM 
> simplex. 
>   4)  METER         - Take meter reading. 
>   5)  MODE          - Change transceiver modes. 
>   6)  brightness    - Set display brightness. 
>   7)  PTT           - Toggle PTT. 
>   8)  recall memory - Recall memory channel to current VFO. 
>   9)  VFO->M        - Copy VFO to memory channel. 
>  10)  LOCK          - Toggle tuner lock. 
>  11)  VFO A/B       - Toggle current VFO. 
>  12)  M->VFO        - Copy memory channel to current or last used VFO. 
>  13)  tuner on/off  - Switch tuner on/off. 
>  14)  start tuner   - Start antenna tuner. 
>  15)  STEP          - Step current display up or down 100 kHz or 1 MHz. 
>  16)  CLAR          - Toggler/adjust clarifier. 
>  17)  HAM/GEN       - Toggle HAM/GEN stepping function. 
>  18)  A=B           - Copy current VFO contents to other VFO. 
>  19)  rptr offset   - Switch FM on to set FM repeater offset. 
>  20)  CTCSS freq    - Switch to FM and set CTCSS [PL] frequency. 
>  21)  Auxiliary Functions. 
> 
> Please input your selection -> 

On 28-Jul-04 Mr. Donn Washburn, N5XWB, provided me with some updates to the
code to work on recent Linux machines.

Updated 20-Sep-98 to include new copying policy and other minor documentation
modifications.

-----------------------
Please read TODO list for further work
-----------------------
Installation and Usage:

First you need to get a level converter so that your computer's RS-232C signals
can be read by your 890's TTL circuit.  You have one of many options to pursue
in order to achieve this, I will mention two.  
	One:  Purchase Yaesu's ~$100 FIF-232C box (not recommended for the
              money conscious).  
	Two:  Make one.  You can look in the February 1993 QST, page 37.
	      Here you will find a VERY simple one to build for less than
	      $10.
I use option two, it is cheap and I can always appreciate a circuit that I
built myself (especially if it works too!).  Once you have the box, connect it
as per the instructions included (some com port to the 6-pin mini din on the
transceiver's rear).  You HAVE to know what com port your box is on, be sure
to make a note of it.  Off to usage...

Using my program is very simple, to execute it you must provide the com port
as an argument to the command line.  Remember, com1 is /dev/ttyS0 and com2 
is /dev/ttyS1, etc.  As an example, my box is on com4 (/dev/tty3), so I must
type in the following...

		'yaesu 3'

where 3 represents com4.  Once you have gotten this far with the correct port,
the program's menu should guide you along.  Please see the bug list, disclaimer
and copying section below.

If you would like to recompile the binary, just type 'make'.

Enjoy my program, this is why it was written.  Hope to catch you on the air!!
73´s
