#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "image.h"
#include "transformations.h"

const char* valid_transformations[] = {"none", "cw90", "ccw90", "fliph", "flipv"};
enum transformation_type parse_last_argument(const char* arg) {
    for (size_t i = 0; i < sizeof(valid_transformations) / sizeof(valid_transformations[0]); i ++) {
        if (strcmp(valid_transformations[i], arg) == 0) {
            return (enum transformation_type)i;
        }
    }
    return TRANSFORM_INVALID;
}

struct image* rotate_90cw(const struct image* source_img) {
    struct image* new_img = create_image(source_img->height, source_img->width);
    for (size_t i = 0; i < source_img->height; ++i) {
        for (size_t j = 0; j < source_img->width; ++j) {
            new_img->data[(source_img->width - 1 - j) * new_img->width + i] = source_img->data[i * source_img->width + j];
        }
    }
    return new_img;
}
struct image* rotate_90ccw(const struct image* source_img) {
    struct image* new_img = create_image(source_img -> height, source_img -> width);
    for (size_t i = 0; i < source_img -> height; ++ i) {
        for (size_t j = 0; j < source_img -> width; ++ j) {
            new_img -> data[(source_img -> height - 1 - i) + j * new_img -> width] = source_img -> data[i * source_img -> width + j];
        }
    } 
    return new_img;
}

struct image* fliph(const struct image* source_img) {
    struct image* new_img = create_image(source_img->width, source_img->height); 
    for (size_t i = 0; i < source_img->height; ++i) {
        for (size_t j = 0; j < source_img->width; ++j) {
            new_img->data[i * new_img->width + (new_img->width - 1 - j)] = source_img->data[i * source_img->width + j];
        }
    }
    return new_img;
}
struct image* flipv(const struct image* source_img) {
    struct image* new_img = create_image(source_img->width, source_img->height); 
    for (size_t i = 0; i < source_img->height; ++i) {
        for (size_t j = 0; j < source_img->width; ++j) {
            new_img->data[(source_img->height - 1 - i) * new_img->width + j] = source_img->data[i * source_img->width + j];
        }
    }
    return new_img;
}
struct image* none(const struct image* source_img) {
    struct image* new_img = create_image(source_img->width, source_img->height); 
    for (size_t i = 0; i < source_img->height; ++i) {
        for (size_t j = 0; j < source_img->width; ++j) {
            new_img->data[i * new_img->width + j] = source_img->data[i * source_img->width + j];
        }
    }
    return new_img;
}
struct image* transform(const struct image* img, enum transformation_type type) {
    struct image* transformed_img = NULL;
    switch (type) {
        case TRANSFORM_CW90:
            transformed_img = rotate_90cw(img);
            break;
        case TRANSFORM_CCW90:
            transformed_img = rotate_90ccw(img);
            break;
        case TRANSFORM_FLIPH:
            transformed_img = fliph(img);
            break;
        case TRANSFORM_FLIPV:
            transformed_img = flipv(img);
            break;
        case TRANSFORM_NONE:
            transformed_img = none(img);
            break;
        default:
            fprintf(stderr, "unknown transformation type");
            break;
    }
    return transformed_img;
}
