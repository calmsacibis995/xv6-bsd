#ifndef _REBOOT_H
#define _REBOOT_H

/*
 * Arguments to reboot system call.
 * These are passed to boot program, and on to init.
 */

#define	RB_AUTOBOOT	0	/* flags for system auto-booting itself */

#define	RB_ASKNAME	0x01	/* ask for file name to reboot from */
#define	RB_SINGLE	0x02	/* reboot to single user only */
#define	RB_NOSYNC	0x04	/* dont sync before reboot */
#define	RB_HALT		0x08	/* don't reboot, just halt */
#define	RB_INITNAME	0x10	/* name given for /etc/init */
#define	RB_DFLTROOT	0x20	/* use compiled-in rootdev */

#define	RB_PANIC	0	/* reboot due to panic */
#define	RB_BOOT		1	/* reboot due to boot() */

extern void boot(int paniced, int arghowto);

#endif /* _REBOOT_H */
