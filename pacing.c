extern main();
extern outport();

#include <config.h>

/*  Make sure pacing is set for the most speed */
pacing(int fdSer) {
    int opcode;

    opcode = 14;
    outport(fdSer, PACE, PACE, PACE, PACE, opcode);
}
