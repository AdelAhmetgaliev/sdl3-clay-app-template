#include <SDL3/SDL_log.h>
#include "SDL3_ttf/SDL_ttf.h"

#include "clay.h"
#include "fontids.h"

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

#define PATH_TO_FONT "resources/fonts/basis33.ttf"

[[maybe_unused]]
static bool SDL_LoadFonts(TTF_Font **fonts) {
    TTF_Font *fontNormal24 = TTF_OpenFont(PATH_TO_FONT, 24);
    if (!fontNormal24) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to load font: %s", SDL_GetError());
        return false;
    }
    fonts[fontIdNormal24] = fontNormal24;

    TTF_Font *fontNormal32 = TTF_OpenFont(PATH_TO_FONT, 32);
    if (!fontNormal32) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to load font: %s", SDL_GetError());
        return false;
    }
    fonts[fontIdNormal32] = fontNormal32;

    TTF_Font *fontNormal42 = TTF_OpenFont(PATH_TO_FONT, 42);
    if (!fontNormal42) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to load font: %s", SDL_GetError());
        return false;
    }
    fonts[fontIdNormal42] = fontNormal42;

    return true;
}
