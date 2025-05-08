#include "clay.h"

#include "colors.h"
#include "fontids.h"

[[maybe_unused]]
static void RenderTopBar(void) {
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
        CLAY({
            .id = CLAY_ID("MenuButton"),
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
            .backgroundColor = Clay_Hovered() ? CLAY_COLOR_BUTTON_HOVER : CLAY_COLOR_BUTTON,
            .cornerRadius = CLAY_CORNER_RADIUS(10),
        }) {
            CLAY_TEXT(CLAY_STRING("Меню"), CLAY_TEXT_CONFIG({
                .fontId = fontIdNormal42,
                .fontSize = 42,
                .textColor = CLAY_COLOR_WHITE
            }));

            bool fileMenuVisible =
                Clay_PointerOver(Clay_GetElementId(CLAY_STRING("MenuButton"))) ||
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
                        CLAY({
                                .id = CLAY_ID("AuthorButton"),
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
                                .backgroundColor = Clay_Hovered() ? CLAY_COLOR_BUTTON_HOVER : CLAY_COLOR_BUTTON
                        }) {
                            CLAY_TEXT(
                                    CLAY_STRING("Об авторе"),
                                    CLAY_TEXT_CONFIG({
                                        .fontId = fontIdNormal42,
                                        .fontSize = 42,
                                        .textColor = CLAY_COLOR_WHITE
                                    })
                            );
                        }

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
                                .backgroundColor = Clay_Hovered() ? CLAY_COLOR_BUTTON_HOVER : CLAY_COLOR_BUTTON
                        }) {
                            CLAY_TEXT(
                                    CLAY_STRING("Выход"),
                                    CLAY_TEXT_CONFIG({
                                        .fontId = fontIdNormal42,
                                        .fontSize = 42,
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
