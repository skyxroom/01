/* ******************************************************************************
 *
 *
 * This program and the accompanying materials are made available under the
 * terms of the Apache License, Version 2.0 which is available at
 * https://www.apache.org/licenses/LICENSE-2.0.
 *
 *  See the NOTICE file distributed with this work for additional
 *  information regarding copyright ownership.
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 * License for the specific language governing permissions and limitations
 * under the License.
 *
 * SPDX-License-Identifier: Apache-2.0
 ******************************************************************************/

// mmap for win32 platform using win32 api
//
// https://code.google.com/p/mman-win32/
//

#ifndef _SYS_MMAN_H_
#define _SYS_MMAN_H_
#include <errno.h>
#include <io.h>
#include <windows.h>

#ifndef FILE_MAP_EXECUTE
#define FILE_MAP_EXECUTE 0x0020
#endif /* FILE_MAP_EXECUTE */

#ifndef _WIN32_WINNT         // Allow use of features specific to Windows XP or later.
#define _WIN32_WINNT 0x0501  // Change this to the appropriate value to target other versions of Windows.
#endif

/* All the headers include this file. */
#ifndef _MSC_VER
#include <_mingw.h>
#endif

/* Determine offset type */
#include <stdint.h>
#if defined(_WIN64)
typedef int64_t OffsetType;
#else
typedef uint32_t OffsetType;
#endif
#include <sys/types.h>

#ifdef __cplusplus
extern "C" {
#endif

#define PROT_NONE 0
#define PROT_READ 1
#define PROT_WRITE 2
#define PROT_EXEC 4

#define MAP_FILE 0
#define MAP_SHARED 1
#define MAP_PRIVATE 2
#define MAP_TYPE 0xf
#define MAP_FIXED 0x10
#define MAP_ANONYMOUS 0x20
#define MAP_ANON MAP_ANONYMOUS

#define MAP_FAILED ((void *)-1)

/* Flags for msync. */
#define MS_ASYNC 1
#define MS_SYNC 2
#define MS_INVALIDATE 4

void _mmap(sd::LongType *result, size_t length, const char *fileName);
void *mmap(void *addr, size_t len, int prot, int flags, int fildes, OffsetType off);
int munmap(void *addr, size_t len);
int _mprotect(void *addr, size_t len, int prot);
int msync(void *addr, size_t len, int flags);
int mlock(const void *addr, size_t len);
int munlock(const void *addr, size_t len);

#ifdef __cplusplus
}
#endif

static int __map_mman_error(const DWORD err, const int deferr) {
  if (err == 0) return 0;
  // TODO: implement
  return err;
}

static DWORD __map_mmap_prot_page(const int prot) {
  DWORD protect = 0;

  if (prot == PROT_NONE) return protect;

  if ((prot & PROT_EXEC) != 0) {
    protect = ((prot & PROT_WRITE) != 0) ? PAGE_EXECUTE_READWRITE : PAGE_EXECUTE_READ;
  } else {
    protect = ((prot & PROT_WRITE) != 0) ? PAGE_READWRITE : PAGE_READONLY;
  }

  return protect;
}

static DWORD __map_mmap_prot_file(const int prot) {
  DWORD desiredAccess = 0;

  if (prot == PROT_NONE) return desiredAccess;

  if ((prot & PROT_READ) != 0) desiredAccess |= FILE_MAP_READ;
  if ((prot & PROT_WRITE) != 0) desiredAccess |= FILE_MAP_WRITE;
  if ((prot & PROT_EXEC) != 0) desiredAccess |= FILE_MAP_EXECUTE;

  return desiredAccess;
}

void _mmap(sd::LongType *result, size_t length, const char *fileName) {
  HANDLE fm, h;

  void *map = MAP_FAILED;
  OffsetType off = 0;
  int prot = PROT_READ | PROT_WRITE;

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4293)
#endif

  const DWORD dwFileOffsetLow = (sizeof(OffsetType) <= sizeof(DWORD)) ? (DWORD)off : (DWORD)(off & 0xFFFFFFFFL);
  const DWORD dwFileOffsetHigh = (sizeof(OffsetType) <= sizeof(DWORD)) ? (DWORD)0 : (DWORD)((off >> 32) & 0xFFFFFFFFL);
  const DWORD protect = __map_mmap_prot_page(prot);
  const DWORD desiredAccess = __map_mmap_prot_file(prot);

  const OffsetType maxSize = off + (OffsetType)length;

  const DWORD dwMaxSizeLow = (sizeof(OffsetType) <= sizeof(DWORD)) ? (DWORD)maxSize : (DWORD)(maxSize & 0xFFFFFFFFL);
  const DWORD dwMaxSizeHigh = (sizeof(OffsetType) <= sizeof(DWORD)) ? (DWORD)0 : (DWORD)((maxSize >> 32) & 0xFFFFFFFFL);

#ifdef _MSC_VER
#pragma warning(pop)
#endif

  h = CreateFileA(fileName, GENERIC_READ | GENERIC_WRITE, FILE_SHARE_WRITE | FILE_SHARE_READ, nullptr, OPEN_EXISTING,
                  FILE_ATTRIBUTE_NORMAL, nullptr);

  if (h == INVALID_HANDLE_VALUE) {
    errno = __map_mman_error(GetLastError(), EPERM);
    sd_printf("Error code: %i\n", (int)errno);
    THROW_EXCEPTION("CreateFile failed");
  }

  fm = CreateFileMapping(h, NULL, protect, dwMaxSizeHigh, dwMaxSizeLow, NULL);

  if (fm == NULL) {
    errno = __map_mman_error(GetLastError(), EPERM);
    THROW_EXCEPTION("CreateFileMapping failed");
  }

  map = MapViewOfFile(fm, desiredAccess, dwFileOffsetHigh, dwFileOffsetLow, length);

  CloseHandle(fm);

  if (map == NULL) {
    errno = __map_mman_error(GetLastError(), EPERM);
    THROW_EXCEPTION("MapViewOfFile failed");
  }

  result[0] = reinterpret_cast<sd::LongType>(map);
  result[1] = reinterpret_cast<sd::LongType>(h);
}

void *mmap(void *addr, size_t len, int prot, int flags, int files, OffsetType off) {
  HANDLE fm, h;

  void *map = MAP_FAILED;

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4293)
#endif

  const DWORD dwFileOffsetLow = (sizeof(OffsetType) <= sizeof(DWORD)) ? (DWORD)off : (DWORD)(off & 0xFFFFFFFFL);
  const DWORD dwFileOffsetHigh = (sizeof(OffsetType) <= sizeof(DWORD)) ? (DWORD)0 : (DWORD)((off >> 32) & 0xFFFFFFFFL);
  const DWORD protect = __map_mmap_prot_page(prot);
  const DWORD desiredAccess = __map_mmap_prot_file(prot);

  const OffsetType maxSize = off + (OffsetType)len;

  const DWORD dwMaxSizeLow = (sizeof(OffsetType) <= sizeof(DWORD)) ? (DWORD)maxSize : (DWORD)(maxSize & 0xFFFFFFFFL);
  const DWORD dwMaxSizeHigh = (sizeof(OffsetType) <= sizeof(DWORD)) ? (DWORD)0 : (DWORD)((maxSize >> 32) & 0xFFFFFFFFL);

#ifdef _MSC_VER
#pragma warning(pop)
#endif

  errno = 0;

  if (len == 0
      /* Unsupported flag combinations */
      || (flags & MAP_FIXED) != 0
      /* Usupported protection combinations */
      || prot == PROT_EXEC) {
    errno = EINVAL;
    return MAP_FAILED;
  }

  h = ((flags & MAP_ANONYMOUS) == 0) ? (HANDLE)_get_osfhandle(files) : INVALID_HANDLE_VALUE;

  if ((flags & MAP_ANONYMOUS) == 0 && h == INVALID_HANDLE_VALUE) {
    errno = EBADF;
    return MAP_FAILED;
  }

  fm = CreateFileMapping(h, NULL, protect, dwMaxSizeHigh, dwMaxSizeLow, NULL);

  if (fm == NULL) {
    errno = __map_mman_error(GetLastError(), EPERM);
    return MAP_FAILED;
  }

  map = MapViewOfFile(fm, desiredAccess, dwFileOffsetHigh, dwFileOffsetLow, len);

  CloseHandle(fm);

  if (map == NULL) {
    errno = __map_mman_error(GetLastError(), EPERM);
    return MAP_FAILED;
  }

  return map;
}

int munmap(void *addr, size_t len) {
  if (UnmapViewOfFile(addr)) return 0;

  errno = __map_mman_error(GetLastError(), EPERM);

  return -1;
}

int _mprotect(void *addr, size_t len, int prot) {
  DWORD newProtect = __map_mmap_prot_page(prot);
  DWORD oldProtect = 0;

  if (VirtualProtect(addr, len, newProtect, &oldProtect)) return 0;

  errno = __map_mman_error(GetLastError(), EPERM);

  return -1;
}

int msync(void *addr, size_t len, int flags)

{
  if (FlushViewOfFile(addr, len)) return 0;

  errno = __map_mman_error(GetLastError(), EPERM);

  return -1;
}

int mlock(const void *addr, size_t len) {
  if (VirtualLock((LPVOID)addr, len)) return 0;

  errno = __map_mman_error(GetLastError(), EPERM);

  return -1;
}

int munlock(const void *addr, size_t len) {
  if (VirtualUnlock((LPVOID)addr, len)) return 0;

  errno = __map_mman_error(GetLastError(), EPERM);

  return -1;
}

#endif  // PROJECT_MMAN_H
