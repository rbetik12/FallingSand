#include "ImageLoader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

uint8_t * LoadImage(const char * imagePath) {
    stbi_set_flip_vertically_on_load(1);
    int width, height, channels;
    uint8_t * imageBuffer = stbi_load(imagePath, &width, &height, &channels, 0);
    if (imageBuffer == NULL) {
        fprintf(stderr, "Can't load image!\n");
        return NULL;
    }
    uint8_t * image = malloc(sizeof(uint8_t) * width * height * channels);
    memcpy(image, imageBuffer, sizeof(uint8_t) * width * height * channels);
    printf("Loaded image %s successfully!\nWidth: %d Height: %d Channels %d\n", imagePath, width, height, channels);
    FreeImage(imageBuffer);
    return image;
}

void FreeImage(uint8_t * imageBuffer) {
    stbi_image_free(imageBuffer);
}

