/*
 *  This is the port the interface will be on.
 *  Remember, ttyS0 is DOS' com1, ttyS1 is com2 and so on.
 *  This will be configurable at runtime via a config file.
 */

/* #define PORT "/dev/ttyS3"  */

/*
 *  This should never have to be changed, it is the pacing byte.
 */

#define PACE 0

/*
 *  This is the file to output all of the memory contents.
 */

#define memory_file "/root/working/yaesu/memory.dat"
