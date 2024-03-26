/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 */

#include "types.h"
#include "param.h"
#include "memlayout.h"
#include "riscv.h"
#include "defs.h"
#include "kernel.h"
#include "spinlock.h"
#include "sleeplock.h"
#include "fs.h"
#include "buf.h"
#include "../bsd/include/reboot.h"

int	waittime = -1;
struct buf *buf;
int nbuf;
struct buf bfreelist[BQUEUES];	/* heads of available lists */

void
boot(int paniced, int arghowto)
{
    int howto;		/* how to boot */
    struct inode *ip = 0;

    howto = arghowto;
	if ((howto & RB_NOSYNC) == 0 && waittime < 0 && bfreelist[0].b_forw) {
		waittime = 0;
		printf("syncing disks... ");
		iupdate(ip);
		{
            register struct buf *bp;
            int iter, nbusy;
            
            for (iter = 0; iter < 20; iter++) {
                nbusy = 0;
                for (bp = &buf[nbuf]; --bp >= buf; )
				    if ((bp->b_flags & (B_BUSY|B_INVAL)) == B_BUSY)
					    nbusy++;
                if (nbusy == 0)
				    break;
			    printf("%d ", nbusy);
			    DELAY(40000 * iter);
            }
		}
		printf("done\n");
	}
	//splx(0x1f);			/* extreme priority */
	if (howto & RB_HALT) {
		printf("System halted\n");
		for (;;)
			;
	} else {
		if (paniced == RB_PANIC) {
			printf("Dump not implemented.\n");
		}
	}
	for (;;)
		asm("wfi"); /* Wait for an interrupt that will never come... */
	/*NOTREACHED*/
}
