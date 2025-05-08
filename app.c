#define SDL_MAIN_USE_CALLBACKS
#include <SDL3/SDL_main.h>
#include <SDL3/SDL.h>
#include "SDL3_ttf/SDL_ttf.h"

#define CLAY_IMPLEMENTATION
#include "clay.h"

#include "config.h"
#include "colors.h"
#include "fontids.h"
#include "clay_error_handler.c"
#include "clay_renderer_SDL3.c"
#include "clay_ui.c"
#include "utilities.c"

typedef struct _AppState {
    SDL_Window *window;
    Clay_SDL3RendererData rendererData;
} AppState;

SDL_AppResult SDL_AppInit(void **appState, int argc, char *argv[]) {
    (void) argc; (void) argv;

    SDL_SetAppMetadata(appName, appVersion, appIdentifier);

    if (!TTF_Init()) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to initialize TTF: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    AppState *state = SDL_calloc(1, sizeof(AppState));
    if (!state) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to allocate memory to AppState: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!SDL_CreateWindowAndRenderer(
                appName, appWidth, appHeight, 0, &state->window, &state->rendererData.renderer)) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to create window and renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }
    SDL_SetRenderVSync(state->rendererData.renderer, 1);

    state->rendererData.textEngine = TTF_CreateRendererTextEngine(state->rendererData.renderer);
    if (!state->rendererData.textEngine) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to create text engine from renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    state->rendererData.fonts = SDL_calloc(FONT_COUNT, sizeof(TTF_Font *));
    if (!state->rendererData.fonts) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Failed to allocate memory for the font array: %s", SDL_GetError());
    }
 
    if (!SDL_LoadFonts(state->rendererData.fonts)) {
        return SDL_APP_FAILURE;
    }

    uint64_t totalMemoryUse = Clay_MinMemorySize();
    Clay_Arena clayMemory = (Clay_Arena) {
        .memory = SDL_malloc(totalMemoryUse),
        .capacity = totalMemoryUse
    };

    Clay_Initialize(
            clayMemory, 
            (Clay_Dimensions) {
                .width = (float)appWidth,
                .height = (float)appHeight
            },
            (Clay_ErrorHandler) { HandleClayErrors, NULL }
    );
    Clay_SetMeasureTextFunction(SDL_MeasureText, state->rendererData.fonts);

    *appState = state;
    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appState, SDL_Event *event) {
    (void) appState;

    SDL_AppResult returnValue = SDL_APP_CONTINUE;

    switch (event->type) {
        case SDL_EVENT_QUIT:
            returnValue = SDL_APP_SUCCESS;
            break;
        case SDL_EVENT_WINDOW_RESIZED:
            Clay_SetLayoutDimensions(
                    (Clay_Dimensions) {
                        (float) event->window.data1,
                        (float) event->window.data2
                    }
            );
            break;
        case SDL_EVENT_MOUSE_MOTION:
            Clay_SetPointerState(
                    (Clay_Vector2) {
                        event->motion.x,
                        event->motion.y
                    },
                    event->motion.state & SDL_BUTTON_LMASK
            );
            break;
        case SDL_EVENT_MOUSE_BUTTON_DOWN:
            Clay_SetPointerState(
                    (Clay_Vector2) {
                        event->button.x,
                        event->button.y
                    },
                    event->button.button == SDL_BUTTON_LEFT
            );
            break;
        case SDL_EVENT_MOUSE_BUTTON_UP:
            if (Clay_PointerOver(Clay_GetElementId(CLAY_STRING("ExitButton")))) {
                returnValue = SDL_APP_SUCCESS;
            }
            break;
        case SDL_EVENT_MOUSE_WHEEL:
            Clay_UpdateScrollContainers(
                    true,
                    (Clay_Vector2) {
                        event->wheel.x,
                        event->wheel.y
                    },
                    0.01f
            );
            break;
        default:
            break;
    };

    return returnValue;
}

SDL_AppResult SDL_AppIterate(void *appState) {
    AppState *state = appState;

    Clay_BeginLayout();
    CLAY({
            .id = CLAY_ID("OuterContainer"),
            .backgroundColor = CLAY_COLOR_GREY,
            .layout = {
                .layoutDirection = CLAY_TOP_TO_BOTTOM,
                .sizing = {
                    .width = CLAY_SIZING_GROW(0),
                    .height = CLAY_SIZING_GROW(0)
                },
                .padding = CLAY_PADDING_ALL(16),
                .childGap = 16
            }
    }) {
        RenderTopBar();
    }
    Clay_RenderCommandArray renderCommands = Clay_EndLayout();

    SDL_SetRenderDrawColor(state->rendererData.renderer, 0, 0, 0, 255);
    SDL_RenderClear(state->rendererData.renderer);

    SDL_Clay_RenderClayCommands(&state->rendererData, &renderCommands);

    SDL_RenderPresent(state->rendererData.renderer);

    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appState, SDL_AppResult result) {
    if (result != SDL_APP_SUCCESS) {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Application failed to run");
    }

    AppState *state = appState;
    if (state) {
        if (state->rendererData.renderer) {
            SDL_DestroyRenderer(state->rendererData.renderer);
        }

        if (state->window) {
            SDL_DestroyWindow(state->window);
        }

        if (state->rendererData.fonts) {
            for (size_t i = 0; i < FONT_COUNT; ++i) {
                TTF_CloseFont(state->rendererData.fonts[i]);
            }
            SDL_free(state->rendererData.fonts);
        }

        if (state->rendererData.textEngine) {
            TTF_DestroyRendererTextEngine(state->rendererData.textEngine);
        }

        SDL_free(state);
    }
    TTF_Quit();
    SDL_Quit();
}
