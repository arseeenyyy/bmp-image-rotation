#include <stdint.h>
#include <stdlib.h>

#include "image.h"

void destroy_image(struct image* img) {
    if (img) {
        free(img -> data);
        free(img);
    }
}
struct image* create_image(uint64_t width, uint64_t height) {
    struct image* img = (struct image*) malloc(sizeof(struct image));
    if (!img) {
        return NULL;  
    }
    img->width = width;
    img->height = height;
    img->data = (struct pixel*) malloc(sizeof(struct pixel) * height * width);
    if (!img->data) {
        free(img); 
        return NULL;  
    }
    return img;
}

