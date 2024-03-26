/*
 * Copyright (c) 1982, 1986 Regents of the University of California.
 * All rights reserved.  The Berkeley software License Agreement
 * specifies the terms and conditions for redistribution.
 */

#include <stdarg.h>

#include "include/reboot.h"

void printf(char*, ...);

/*
 * In case console is off,
 * panicstr contains argument to last
 * call to panic.
 */
char *panicstr;

/*
 * Panic is called on unresolvable fatal errors.
 * It prints "panic: mesg", and then reboots.
 * If we are called twice, then we avoid trying to
 * sync the disks as this often leads to recursive panics.
 */
void
bsd_panic(char *s, ...)
{
	int bootopt = RB_AUTOBOOT;

	if (panicstr)
		bootopt |= RB_NOSYNC;
	else {
		panicstr = s;
	}

	printf("Kernel panic on BSD component: %s\n", s);
	boot(RB_PANIC, bootopt);
}
