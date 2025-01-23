import ctypes

lib = ctypes.CDLL('libs/libmylib.so')

# void cyclic_shift(int *arr, const size_t len, const size_t k);
_cyclic_shift = lib.cyclic_shift    
_cyclic_shift.argtypes = (ctypes.POINTER(ctypes.c_int), ctypes.c_size_t, ctypes.c_size_t)
_cyclic_shift.restype = None


# int filter(int *src, size_t src_len, int *dst, size_t *dst_len);
_filter = lib.filter    
_filter.argtypes = (ctypes.POINTER(ctypes.c_int), ctypes.c_size_t, ctypes.POINTER(ctypes.c_int), ctypes.POINTER(ctypes.c_size_t))
_filter.restype = ctypes.c_size_t

def cyclic_shift(nums, k):
    size_t_k = ctypes.c_size_t(k)
    src_len = len(nums)
    src = (ctypes.c_int * src_len)(*nums)
    _cyclic_shift(src, src_len, size_t_k)
    return list(src)


def filter(nums):
    src_len = len(nums)
    src = (ctypes.c_int * src_len)(*nums)
    dst_len = ctypes.c_size_t(0)

    rc = _filter(src, src_len, None, dst_len)
    if rc:
        dst = (ctypes.c_int * dst_len.value)()
        rc = _filter(src, src_len, dst, dst_len)
        return rc, list(dst)
    else:
        return rc, list()
  
#print(cyclic_shift([], 5))
