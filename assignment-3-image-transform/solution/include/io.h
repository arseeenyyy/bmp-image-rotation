#ifndef IO_H
#define IO_H
#include "image.h"

#include <stdio.h>

enum read_status  {
  READ_OK = 0,
  READ_INVALID_SIGNATURE = 1,
  READ_INVALID_BITS = 2,
  READ_INVALID_HEADER = 3,
  };
struct bmp_header create_header(uint32_t padding, uint64_t width, uint64_t height);

enum read_status from_bmp( FILE* in, struct image** img );

enum  write_status  {
  WRITE_OK = 0,
  WRITE_ERROR = 1
};

enum write_status to_bmp( FILE* out, struct image const* img );
#endif
