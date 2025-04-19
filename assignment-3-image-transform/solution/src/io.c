#include <stdint.h>
#include <stdio.h>

#include "bmp.h"
#include "image.h"
#include "io.h"

static uint32_t get_padding(const struct image* img) {
    return (4 - ((img -> width * sizeof(struct pixel)) % 4)) % 4;
}

struct bmp_header create_header(uint32_t padding, uint64_t width, uint64_t height) {
    struct bmp_header header = {
        .bfType = HEADER_TYPE,
        .bfileSize = sizeof(struct bmp_header) + (width * sizeof(struct pixel) + padding) * height,
        .bfReserved = HEADER_RESERVED,
        .bOffBits = sizeof(struct bmp_header),
        .biSize = HEADER_SIZE,
        .biWidth = width,
        .biHeight = height,
        .biPlanes = HEADER_PLANES,
        .biBitCount = HEADER_BITS_PER_PIXEL,
        .biCompression = HEADER_COMPRESSION,
        .biSizeImage = (width * sizeof(struct pixel) + padding) * height,
        .biXPelsPerMeter = HEADER_PIXEL_PER_METER,
        .biYPelsPerMeter = HEADER_PIXEL_PER_METER,
        .biClrUsed = HEADER_CLR_USED,
        .biClrImportant = HEADER_CLR_IMPR
    };
    return header;   
}

enum read_status from_bmp(FILE* in, struct image** img) {
    struct bmp_header header;
    if (fread(&header, sizeof(header), 1, in) != 1) {
        return READ_INVALID_HEADER;  
    }
    if (header.bfType != HEADER_TYPE) {
        return READ_INVALID_SIGNATURE;  
    }
    *img = create_image(header.biWidth, header.biHeight);
    if (!*img) {
        return READ_INVALID_BITS; 
    }
    uint32_t padding = get_padding(*img);
    for (uint32_t i = 0; i < header.biHeight; ++i) {
        size_t bts_read = fread(&((*img)->data[i * header.biWidth]), sizeof(struct pixel), header.biWidth, in);
        if (bts_read != header.biWidth) {
            destroy_image(*img);  
            return READ_INVALID_BITS;  
        }
        if (padding > 0) {
            if (fseek(in, padding, SEEK_CUR) != 0) {
                destroy_image(*img);  
                return READ_INVALID_BITS; 
            }
        }
    }
    return READ_OK;
}
enum write_status to_bmp(FILE* out, const struct image* img) {
    uint32_t padding = get_padding(img);
    struct bmp_header header = create_header(padding, img -> width, img -> height);
    if (fwrite(&header, sizeof(struct bmp_header), 1, out) != 1) {
        return WRITE_ERROR;
    }
    uint8_t padding_el[3] = {0, 0, 0};
    for (size_t i = 0; i < img->height; ++i) {
        if (fwrite(&img->data[img->width * i], sizeof(struct pixel), img->width, out) != img->width)
            return WRITE_ERROR;
        if (fwrite(padding_el, 1, padding, out) != padding)
            return WRITE_ERROR;
    }
    return WRITE_OK;
}
