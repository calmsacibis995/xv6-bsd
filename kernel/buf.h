struct buf {
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

/*
 * Bufhd structures used at the head of the hashed buffer queues.
 * We only need three words for these, so this abbreviated
 * definition saves some space.
 */
struct bufhd {
	long	b_flags;		/* see defines below */
	struct	buf *b_forw, *b_back;	/* fwd/bkwd pointer in chain */
};

