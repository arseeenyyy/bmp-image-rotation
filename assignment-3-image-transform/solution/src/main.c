#include "io.h"
#include "image.h"
#include "transformations.h"
#include <errno.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage:%s <source-file> <target-file> <transformation>", argv[0]);
        return EPERM;
    }
    FILE *in = fopen(argv[1], "rb");
    if (!in) {
        fprintf(stderr, "unable to open source file <%s>", argv[1]);
        return ENOENT;
    }
    struct image* img = NULL; 
    enum read_status rstatus = from_bmp(in, &img);
    fclose(in);
    if (rstatus != READ_OK) {
        fprintf(stderr, "Error reading source file <%s>", argv[1]);
        return ENOMEM;
    }
    enum transformation_type type = parse_last_argument(argv[3]);
    struct image* transformed_img = transform(img, type);
    destroy_image(img);
    if (!transformed_img) {
        fprintf(stderr, "Transformation <%s> failed", argv[3]);
        destroy_image(transformed_img);
        return ENOMEM;
    }
    FILE* out = fopen(argv[2], "wb"); 
    if (!out) {
        fprintf(stderr, "Unable to open target file <%s>", argv[2]);
        destroy_image(transformed_img);
        return ENOENT;
    }
    enum write_status wstatus = to_bmp(out, transformed_img);
    if (wstatus != WRITE_OK) {
        fprintf(stderr, "Unable to write to bmp format");
        destroy_image(transformed_img);
        fclose(out);
        return wstatus;
    }
    fclose(out);
    destroy_image(transformed_img);
    fprintf(stdout, "Successfully transformed image");
    return 0;
}
