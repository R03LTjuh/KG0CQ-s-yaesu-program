INCDIR = ./ -I/usr/lib -I/usr/X11R6/lib
CC = gcc
FLAGS = -march=athlon64 -m64 -funsigned-char
OBJS = aux.o bright.o clar.o ctcss.o freq_out.o ham_gen.o lock.o main.o mem_hide.o mem_2vfo.o mem_scsk.o meter_rd.o mode.o outport.o pacing.o ptt.o rd_flags.o mem_rec.o rptr_off.o save_mem.o splt_tog.o strt_tun.o stat_upd.o stat_out.o step.o tuner10.o vfo_ab.o vfo_2mem.o repeater.o vfo_a2b.o wwv_find.o yaesu.o
all:	program

program:: $(OBJS)
	$(CC) $(FLAGS) -I $(INCDIR) -Wall -o yaesu $(OBJS)

aux.o:: aux.c
	$(CC) $(FLAGS) -c -o aux.o aux.c
  
bright.o:: bright.c
	$(CC) $(FLAGS) -c -o bright.o bright.c

clar.o:: clar.c
	$(CC) $(FLAGS) -c -o clar.o clar.c

ctcss.o:: ctcss.c
	$(CC) $(FLAGS) -c -o ctcss.o ctcss.c
 
freq_out.o:: freq_out.c
	$(CC) $(FLAGS) -c -o freq_out.o freq_out.c

ham_gen.o: ham_gen.c
	$(CC) $(FLAGS) -c -o ham_gen.o ham_gen.c

lock.o: lock.c
	$(CC) $(FLAGS) -c -o lock.o lock.c

main.o: main.c
	$(CC) $(FLAGS) -c -I$(INCDIR) -o main.o main.c

mem_hide.o: mem_hide.c
	$(CC) $(FLAGS) -c -o mem_hide.o mem_hide.c

mem_2vfo.o: mem_2vfo.c
	$(CC) $(FLAGS) -c -o mem_2vfo.o mem_2vfo.c

mem_scsk.o: mem_scsk.c
	$(CC) $(FLAGS) -c -o mem_scsk.o mem_scsk.c
      
meter_rd.o: meter_rd.c
	$(CC) $(FLAGS) -c -o meter_rd.o meter_rd.c

mode.o: mode.c
	$(CC) $(FLAGS) -c -o mode.o mode.c

outport.o: outport.c
	$(CC) $(FLAGS) -c -o outport.o outport.c

pacing.o: pacing.c
	$(CC) $(FLAGS) -I./ -c -o pacing.o pacing.c

ptt.o: ptt.c
	$(CC) $(FLAGS) -c -o ptt.o ptt.c

rd_flags.o: rd_flags.c
	$(CC) $(FLAGS) -c -o rd_flags.o rd_flags.c

mem_rec.o: mem_rec.c
	$(CC) $(FLAGS) -c -o mem_rec.o mem_rec.c

save_mem.o: save_mem.c
	$(CC) $(FLAGS) -I./ -c -o save_mem.o save_mem.c

rptr_off.o: rptr_off.c
	$(CC) $(FLAGS) -c -o rptr_off.o rptr_off.c
     
splt_tog.o: splt_tog.c
	$(CC) $(FLAGS) -c -o splt_tog.o splt_tog.c

stat_out.o:: stat_out.c
	$(CC) $(FLAGS) -c -o stat_out.o stat_out.c

stat_upd.o: stat_upd.c
	$(CC) $(FLAGS) -c -o stat_upd.o stat_upd.c

step.o: step.c
	$(CC) $(FLAGS) -c -o step.o step.c

strt_tun.o: strt_tun.c
	$(CC) $(FLAGS) -c -o strt_tun.o strt_tun.c

tuner10.o: tuner10.c
	$(CC) $(FLAGS) -c -o tuner10.o tuner10.c

vfo_ab.o: vfo_ab.c
	$(CC) $(FLAGS) -c -o vfo_ab.o vfo_ab.c

vfo_2mem.o: vfo_2mem.c
	$(CC) $(FLAGS) -c -o vfo_2mem.o vfo_2mem.c

yaesu.o: yaesu.c
	$(CC) $(FLAGS) -c -o yaesu.o yaesu.c

repeater.o: repeater.c
	$(CC) $(FLAGS) -c -o repeater.o repeater.c
        
vfo_a2b.o: vfo_a2b.c
	$(CC) $(FLAGS) -c -o vfo_a2b.o vfo_a2b.c

wwv_find.o: wwv_find.c
	$(CC) $(FLAGS) -c -o wwv_find.o wwv_find.c

clean:
	rm -f yaesu core

nuke:   clean
	rm -f *.o
