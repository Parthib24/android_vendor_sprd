/*
 * Copyright (C) 2008 The Android Open Source Project
 * Copyright (c) 2011, Code Aurora Forum. All rights reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef ANDROID_MEMORY_HEAP_ION_H
#define ANDROID_MEMORY_HEAP_ION_H

#include <stdlib.h>
#include <stdint.h>

#include <utils/SortedVector.h>
#include <utils/threads.h>


namespace android {

// ---------------------------------------------------------------------------

class MemoryHeapIon: public RefBase
{
public:
    enum {
        READ_ONLY = 0x00000001,
        // memory won't be mapped locally, but will be mapped in the remote
        // process.
        DONT_MAP_LOCALLY = 0x00000100,
        NO_CACHING = 0x00000200
    };

    MemoryHeapIon();
    MemoryHeapIon(const char*, size_t, uint32_t, long unsigned int);
    ~MemoryHeapIon();
    int         getHeapID() const;
    void*       getBase() const;

    static int Get_phy_addr_from_ion(int fd, unsigned long *phy_addr, size_t *size);/*fd is "fd of the corresponding ion hanlde"*/
    int get_phy_addr_from_ion(unsigned long *phy_addr, size_t *size);
    static int Flush_ion_buffer(int buffer_fd, void *v_addr,void *p_addr, size_t size);
    int flush_ion_buffer(void *v_addr, void *p_addr, size_t size);

    int get_gsp_iova(unsigned long *mmu_addr, size_t *size);
    int free_gsp_iova(unsigned long mmu_addr, size_t size);
    int get_mm_iova(unsigned long *mmu_addr, size_t *size);
    int free_mm_iova(unsigned long mmu_addr, size_t size);
    static int Get_gsp_iova(int buffer_fd, unsigned long *mmu_addr, size_t *size);
    static int Free_gsp_iova(int buffer_fd, unsigned long mmu_addr, size_t size);
    static int Get_mm_iova(int buffer_fd,unsigned long *mmu_addr, size_t *size);
    static int Free_mm_iova(int buffer_fd,unsigned long mmu_addr, size_t size);
    static bool Gsp_iommu_is_enabled(void);
    static bool Mm_iommu_is_enabled(void);

    int get_iova(int master_id, unsigned long *mmu_addr, size_t *size);
    int free_iova(int master_id, unsigned long mmu_addr, size_t size);
    static int Get_iova(int master_id, int buffer_fd,
        unsigned long *mmu_addr, size_t *size);
    static int Free_iova(int master_id, int buffer_fd,
        unsigned long mmu_addr, size_t size);
    static bool IOMMU_is_enabled(int master_id);

private:
    status_t mapIonFd(int fd, size_t size, unsigned long memory_type, int flags);

    int mIonDeviceFd;  /*fd we get from open("/dev/ion")*/
    int mIonHandle;  /*handle we get from ION_IOC_ALLOC*/ 
    int         mFD;
    size_t      mSize;
    void*       mBase;
};
// ---------------------------------------------------------------------------
}; // namespace android

#endif // ANDROID_MEMORY_HEAP_ION_H

#ifdef MIONONREALSCRIPT
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

#endif
