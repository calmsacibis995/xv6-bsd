struct buf {
  long b_flags;
  struct buf *b_forw, *b_back;	/* hash chain (2 way street) */
  int valid;   // has data been read from disk?
  int disk;    // does disk "own" buf?
  uint dev;
  uint blockno;
  struct sleeplock lock;
  uint refcnt;
  struct buf *prev; // LRU cache list
  struct buf *next;
  uchar data[BSIZE];
};

#define	BUFHSZ	512
#define	BQUEUES		4		/* number of free buffer queues */

/*
 * These flags are kept in b_flags.
 */

#define	B_BUSY		0x000008	/* not on av_forw/back list */
#define	B_INVAL		0x010000	/* does not contain valid info  */

/*
 * Bufhd structures used at the head of the hashed buffer queues.
 * We only need three words for these, so this abbreviated
 * definition saves some space.
 */
struct bufhd {
	long	b_flags;		/* see defines below */
	struct	buf *b_forw, *b_back;	/* fwd/bkwd pointer in chain */
};

extern struct buf *buf;		/* the buffer pool itself */
extern int nbuf;			/* number of buffer headers */
extern struct buf bfreelist[BQUEUES];	/* heads of available lists */
extern struct bufhd bufhash[BUFHSZ];	/* heads of hash lists */
