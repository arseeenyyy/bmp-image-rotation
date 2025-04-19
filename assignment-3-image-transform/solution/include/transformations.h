#ifndef TRANSFORMATIONS_H
#define TRANSFORMATIONS_H
#include <string.h>

#include "image.h"
extern const char* valid_transformations[];
enum transformation_type {
    TRANSFORM_NONE = 0, //nothing 
    TRANSFORM_CW90, //90 clockwise 
    TRANSFORM_CCW90, //90 counter clockwise
    TRANSFORM_FLIPH, //flip horizontal
    TRANSFORM_FLIPV, //flip vertical
    TRANSFORM_INVALID //invalid transformation
};
enum transformation_type parse_last_argument(const char* arg);

struct image* rotate_90cw(const struct image* source_img);
struct image* rotate_90ccw(const struct image* source_img);
struct image* flipv(const struct image* source_img);
struct image* fliph(const struct image* source_img);
struct image* none(const struct image* source_img);
struct image* transform(const struct image* source_img, enum transformation_type type);

#endif
