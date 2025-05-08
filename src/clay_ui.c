#include "clay.h"

#include "colors.h"

[[maybe_unused]]
static void RenderTopBar() {
    CLAY({
            .id = CLAY_ID("TopBar"),
            .layout = {
                .sizing = {
                    .width = CLAY_SIZING_GROW(0),
                    .height = CLAY_SIZING_GROW( .min=50, .max=65 )
                },
                .padding = { 16, 16, 8, 8 },
                .childGap = 8,
                .childAlignment = {
                    .y = CLAY_ALIGN_Y_CENTER
                }
            },
            .backgroundColor = CLAY_COLOR_DARK_GREY,
            .cornerRadius = CLAY_CORNER_RADIUS(10)
    }) {
        const bool overFileButton = Clay_PointerOver(Clay_GetElementId(CLAY_STRING("FileButton")));
        const Clay_Color fileButtonBackColor =
            overFileButton ? CLAY_COLOR_BUTTON_OVER : CLAY_COLOR_BUTTON;

        CLAY({
            .id = CLAY_ID("FileButton"),
            .layout = {
                .padding = { 16, 16, 8, 8 },
                .sizing = {
                    .width = CLAY_SIZING_GROW( .min=100, .max=130 ),
                    .height = CLAY_SIZING_PERCENT(0.95)
                },
                .childAlignment = {
                    .x = CLAY_ALIGN_X_CENTER,
                    .y = CLAY_ALIGN_Y_CENTER
                }
            },
            .backgroundColor = fileButtonBackColor,
            .cornerRadius = CLAY_CORNER_RADIUS(10),
        }) {
            CLAY_TEXT(CLAY_STRING("Файл"), CLAY_TEXT_CONFIG({
                .fontId = 0,
                .fontSize = 42,
                .textColor = CLAY_COLOR_WHITE
            }));

            bool fileMenuVisible =
                Clay_PointerOver(Clay_GetElementId(CLAY_STRING("FileButton"))) ||
                Clay_PointerOver(Clay_GetElementId(CLAY_STRING("FileMenu")));
            if (fileMenuVisible) {
                CLAY({
                        .id = CLAY_ID("FileMenu"),
                        .floating = {
                            .attachTo = CLAY_ATTACH_TO_PARENT,
                            .attachPoints = {
                                .parent = CLAY_ATTACH_POINT_LEFT_BOTTOM
                            }
                        },
                        .layout = {
                            .padding = { 0, 0, 16, 16 }
                        }
                }) {
                    CLAY({
                            .id = CLAY_ID("FileDropDownMenu"),
                            .layout = {
                                .layoutDirection = CLAY_TOP_TO_BOTTOM,
                                .sizing = {
                                    .width = CLAY_SIZING_GROW( .min=300, .max=500 ),
                                    .height = CLAY_SIZING_GROW( .min=150, .max=500)
                                },
                                .padding = {
                                    .left = 8,
                                    .right = 8,
                                    .top = 16,
                                },
                                .childGap = 10
                            },
                            .backgroundColor = { 30, 30, 30, 255 },
                            .cornerRadius = CLAY_CORNER_RADIUS(10)
                    }) {
                        const bool overNewButton = Clay_PointerOver(Clay_GetElementId(CLAY_STRING("NewButton")));
                        const Clay_Color newButtonBackColor =
                            overNewButton ? CLAY_COLOR_BUTTON_OVER : CLAY_COLOR_BUTTON;

                        CLAY({
                                .id = CLAY_ID("NewButton"),
                                .layout = {
                                    .sizing = {
                                        .width = CLAY_SIZING_GROW(0),
                                        .height = CLAY_SIZING_PERCENT(0.45)
                                    },
                                    .childAlignment = {
                                        .x = CLAY_ALIGN_X_LEFT,
                                        .y = CLAY_ALIGN_Y_CENTER
                                    },
                                    .padding = {
                                        .left = 8,
                                    }
                                },
                                .backgroundColor = newButtonBackColor
                        }) {
                            CLAY_TEXT(
                                    CLAY_STRING("Новый"),
                                    CLAY_TEXT_CONFIG({
                                        .fontId = 0,
                                        .fontSize = 40,
                                        .textColor = CLAY_COLOR_WHITE
                                    })
                            );
                        }

                        const bool overExitButton = Clay_PointerOver(Clay_GetElementId(CLAY_STRING("ExitButton")));
                        const Clay_Color exitButtonBackColor =
                            overExitButton ? CLAY_COLOR_BUTTON_OVER : CLAY_COLOR_BUTTON;

                        CLAY({
                                .id = CLAY_ID("ExitButton"),
                                .layout = {
                                    .sizing = {
                                        .width = CLAY_SIZING_GROW(0),
                                        .height = CLAY_SIZING_PERCENT(0.45)
                                    },
                                    .childAlignment = {
                                        .x = CLAY_ALIGN_X_LEFT,
                                        .y = CLAY_ALIGN_Y_CENTER
                                    },
                                    .padding = {
                                        .left = 8
                                    }
                                },
                                .backgroundColor = exitButtonBackColor
                        }) {
                            CLAY_TEXT(
                                    CLAY_STRING("Выход"),
                                    CLAY_TEXT_CONFIG({
                                        .fontId = 0,
                                        .fontSize = 40,
                                        .textColor = CLAY_COLOR_WHITE
                                    })
                            );
                        }
                    }
                }
            }
        }
    }
}
