#include <SDL3/SDL_log.h>
#include "SDL3_ttf/SDL_ttf.h"

#include "clay.h"

[[maybe_unused]]
static inline Clay_Dimensions SDL_MeasureText(
        Clay_StringSlice text, Clay_TextElementConfig *config, void *userData) {
    TTF_Font **fonts = userData;
    TTF_Font *font = fonts[config->fontId];
    int width, height;

    if (!TTF_GetStringSize(font, text.chars, text.length, &width, &height)) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to measure text: %s", SDL_GetError());
    }

    return (Clay_Dimensions) { .width = (float)width, .height = (float)height };
}
