extern main();
extern opcode();

bright(int fdSer) {
  int opcode, bright_level;
  opcode = 0x0f8;
  printf("Enter brightness level: 0..7 [brightest] -> ");
  scanf("%d", &bright_level);
  if (bright_level > -1 && bright_level < 8) {
     outport(fdSer, bright_level, bright_level, bright_level, bright_level, opcode);
  } else {
  printf("Invalid value!!!\n");
  }
  printf("\n");
}
