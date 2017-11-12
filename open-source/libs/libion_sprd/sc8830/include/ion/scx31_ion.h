/**
 * DOC: ION_IOC_INVALIDATE - invalidate a shared file descriptors
 *
 * Deprecated in favor of using the dma_buf api's correctly (syncing
 * will happend automatically when the buffer is mapped to a device).
 * If necessary should be used after touching a cached buffer from the cpu,
 * this will make the buffer in memory coherent.
 */
#define ION_IOC_INVALIDATE _IOWR(ION_IOC_MAGIC, 8, struct ion_fd_data)
