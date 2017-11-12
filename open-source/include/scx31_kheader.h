/*
 * LIB GRALLOC (SCX30GV2)
 */
/* set values immediately (or vbl) but no screen update*/
#define FB_ACTIVATE_NODISP	4

#define ION_HEAP_ID_SYSTEM	1
#define ION_HEAP_ID_MM		2
#define ION_HEAP_ID_OVERLAY	3
#define ION_HEAP_ID_MASK_SYSTEM (1<<ION_HEAP_ID_SYSTEM)
#define ION_HEAP_ID_MASK_MM	(1<<ION_HEAP_ID_MM)
#define ION_HEAP_ID_MASK_OVERLAY (1<<ION_HEAP_ID_OVERLAY)

/**
 * LIBION
 * DOC: ION_IOC_INVALIDATE - invalidate a shared file descriptors
 *
 * Deprecated in favor of using the dma_buf api's correctly (syncing
 * will happend automatically when the buffer is mapped to a device).
 * If necessary should be used after touching a cached buffer from the cpu,
 * this will make the buffer in memory coherent.
 */
#define ION_IOC_INVALIDATE _IOWR(ION_IOC_MAGIC, 8, struct ion_fd_data)
