/* LIB GRALLOC (SCX30GV2) */
/* set values immediately (or vbl) but no screen update*/
#define FB_ACTIVATE_NODISP	4

#define ION_HEAP_ID_SYSTEM	1
#define ION_HEAP_ID_MM		2
#define ION_HEAP_ID_OVERLAY	3
#define ION_HEAP_ID_MASK_SYSTEM (1<<ION_HEAP_ID_SYSTEM)
#define ION_HEAP_ID_MASK_MM	(1<<ION_HEAP_ID_MM)
#define ION_HEAP_ID_MASK_OVERLAY (1<<ION_HEAP_ID_OVERLAY)

/* LIBION */
/*
 * DOC: ION_IOC_INVALIDATE - invalidate a shared file descriptors
 *
 * Deprecated in favor of using the dma_buf api's correctly (syncing
 * will happend automatically when the buffer is mapped to a device).
 * If necessary should be used after touching a cached buffer from the cpu,
 * this will make the buffer in memory coherent.
 */
#define ION_IOC_INVALIDATE _IOWR(ION_IOC_MAGIC, 8, struct ion_fd_data)

/* LIBMEMORYHEAPION */
typedef int ion_user_handle_t;

/**
 * struct ion_allocation_data - metadata passed from userspace for allocations
 * @len:		size of the allocation
 * @align:		required alignment of the allocation
 * @heap_id_mask:	mask of heap ids to allocate from
 * @flags:		flags passed to heap
 * @handle:		pointer that will be populated with a cookie to use to 
 *			refer to this allocation
 *
 * Provided by userspace as an argument to the ioctl
 */
struct ion_allocation_data {
	size_t len;
	size_t align;
	unsigned int heap_id_mask;
	unsigned int flags;
	ion_user_handle_t handle;
};

/**
 * struct ion_fd_data - metadata passed to/from userspace for a handle/fd pair
 * @handle:	a handle
 * @fd:		a file descriptor representing that handle
 *
 * For ION_IOC_SHARE or ION_IOC_MAP userspace populates the handle field with
 * the handle returned from ion alloc, and the kernel returns the file
 * descriptor to share or map in the fd field.  For ION_IOC_IMPORT, userspace
 * provides the file descriptor and the kernel returns the handle.
 */
struct ion_fd_data {
	ion_user_handle_t handle;
	int fd;
};

/**
 * struct ion_handle_data - a handle passed to/from the kernel
 * @handle:	a handle
 */
struct ion_handle_data {
	ion_user_handle_t handle;
};

/**
 * DOC: ION_IOC_ALLOC - allocate memory
 *
 * Takes an ion_allocation_data struct and returns it with the handle field
 * populated with the opaque handle for the allocation.
 */
#define ION_IOC_ALLOC		_IOWR(ION_IOC_MAGIC, 0, \
				      struct ion_allocation_data)
#define ION_IOC_MAGIC		'I'

/**
 * DOC: ION_IOC_SHARE - creates a file descriptor to use to share an allocation
 *
 * Takes an ion_fd_data struct with the handle field populated with a valid
 * opaque handle.  Returns the struct with the fd field set to a file
 * descriptor open in the current address space.  This file descriptor
 * can then be passed to another process.  The corresponding opaque handle can
 * be retrieved via ION_IOC_IMPORT.
 */
#define ION_IOC_SHARE		_IOWR(ION_IOC_MAGIC, 4, struct ion_fd_data)

/**
 * DOC: ION_IOC_FREE - free memory
 *
 * Takes an ion_handle_data struct and frees the handle.
 */
#define ION_IOC_FREE		_IOWR(ION_IOC_MAGIC, 1, struct ion_handle_data)

struct ion_phys_data {
	int fd_buffer;
	unsigned long phys;
	size_t size;
};

/**
 * struct ion_custom_data - metadata passed to/from userspace for a custom ioctl
 * @cmd:	the custom ioctl function to call
 * @arg:	additional data to pass to the custom ioctl, typically a user
 *		pointer to a predefined structure
 *
 * This works just like the regular cmd and arg fields of an ioctl.
 */
struct ion_custom_data {
	unsigned int cmd;
	unsigned long arg;
};

enum ION_MASTER_ID {
	ION_GSP = 0,
	ION_MM,
	/*for whale iommu*/
	ION_VSP,
	ION_DCAM,
	ION_DISPC,
	ION_GSP0,
	ION_GSP1,
	ION_VPP,
};

enum ION_SPRD_CUSTOM_CMD {
	ION_SPRD_CUSTOM_PHYS,
	ION_SPRD_CUSTOM_MSYNC,
	ION_SPRD_CUSTOM_GSP_MAP,
	ION_SPRD_CUSTOM_GSP_UNMAP,
	ION_SPRD_CUSTOM_MM_MAP,
	ION_SPRD_CUSTOM_MM_UNMAP,
	/*for new MemoryHeapIon*/
	ION_SPRD_CUSTOM_MAP,
	ION_SPRD_CUSTOM_UNMAP,
};

/**
 * DOC: ION_IOC_CUSTOM - call architecture specific ion ioctl
 *
 * Takes the argument of the architecture specific ioctl to call and
 * passes appropriate userdata for that ioctl
 */
#define ION_IOC_CUSTOM		_IOWR(ION_IOC_MAGIC, 6, struct ion_custom_data)

struct ion_msync_data {
	int fd_buffer;
	void *vaddr;
	void *paddr;
	size_t size;
};

struct ion_mmu_data {
	int master_id;
	int fd_buffer;
	unsigned long iova_addr;
	size_t iova_size;
};
