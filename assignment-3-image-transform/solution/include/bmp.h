#ifndef BMP_HEADER
#define BMP_HEADER
#define HEADER_TYPE 0x4D42
#define HEADER_RESERVED 0
#define HEADER_SIZE 40
#define HEADER_PLANES 1 
#define HEADER_BITS_PER_PIXEL 24
#define HEADER_COMPRESSION 0
#define HEADER_PIXEL_PER_METER 2834
#define HEADER_CLR_USED 0 
#define HEADER_CLR_IMPR 0
#include <stdint.h>
struct __attribute__((packed)) bmp_header {
        uint16_t bfType;
        uint32_t  bfileSize;
        uint32_t bfReserved;
        uint32_t bOffBits;
        uint32_t biSize;
        uint32_t biWidth;
        uint32_t  biHeight;
        uint16_t  biPlanes;
        uint16_t biBitCount;
        uint32_t biCompression;
        uint32_t biSizeImage;
        uint32_t biXPelsPerMeter;
        uint32_t biYPelsPerMeter;
        uint32_t biClrUsed;
        uint32_t  biClrImportant;
};
#endif
