#include <SDL3/SDL.h>
#include <SDL3/SDL_log.h>

#include "clay.h"

[[maybe_unused]]
static void HandleClayErrors(Clay_ErrorData errorData) {
    SDL_LogError(SDL_LOG_CATEGORY_ERROR, "%s", errorData.errorText.chars);
}
