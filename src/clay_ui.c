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
                .padding = {
                    .left = 16,
                    .right = 16,
                    .top = 8,
                    .bottom = 8
                },
                .childGap = 8,
                .childAlignment = {
                    .x = CLAY_ALIGN_X_LEFT,
                    .y = CLAY_ALIGN_Y_CENTER
                }
            },
            .backgroundColor = CLAY_COLOR_DARK_GREY,
            .cornerRadius = CLAY_CORNER_RADIUS(10)
    }) {
        CLAY({
            .id = CLAY_ID("MenuButton"),
            .layout = {
                .padding = {
                    .left = 16,
                    .right = 16,
                    .top = 8,
                    .bottom = 8
                },
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
            .cornerRadius = CLAY_CORNER_RADIUS(10)
        }) {
            CLAY_TEXT(CLAY_STRING("Меню"), CLAY_TEXT_CONFIG({
                .fontId = fontIdNormal42,
                .fontSize = 42,
                .textColor = CLAY_COLOR_WHITE
            }));

            const bool isFileMenuVisible =
                Clay_PointerOver(Clay_GetElementId(CLAY_STRING("MenuButton"))) ||
                Clay_PointerOver(Clay_GetElementId(CLAY_STRING("FileMenu")));
            if (isFileMenuVisible) {
                CLAY({
                        .id = CLAY_ID("FileMenu"),
                        .floating = {
                            .attachTo = CLAY_ATTACH_TO_PARENT,
                            .attachPoints = {
                                .parent = CLAY_ATTACH_POINT_LEFT_BOTTOM
                            }
                        },
                        .layout = {
                            .padding = {
                                .left = 0,
                                .right = 0,
                                .top = 16,
                                .bottom = 16
                            }
                        }
                }) {
                    CLAY({
                            .id = CLAY_ID("FileDropDownMenu"),
                            .layout = {
                                .layoutDirection = CLAY_TOP_TO_BOTTOM,
                                .sizing = {
                                    .width = CLAY_SIZING_GROW( .min=300, .max=500 ),
                                    .height = CLAY_SIZING_GROW( .min=150, .max=500 )
                                },
                                .padding = {
                                    .left = 8,
                                    .right = 8,
                                    .top = 16,
                                    .bottom = 0
                                },
                                .childGap = 10
                            },
                            .backgroundColor = CLAY_COLOR_DARKER_GREY,
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
                                        .right = 0,
                                        .top = 0,
                                        .bottom = 0
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
                                        .left = 8,
                                        .right = 0,
                                        .top = 0,
                                        .bottom = 0
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

[[maybe_unused]]
static void RenderAboutAuthorPage(void) {
    CLAY({
            .id = CLAY_ID("AboutAuthorPage"),
            .floating = {
                .attachTo = CLAY_ATTACH_TO_ROOT,
                .attachPoints = {
                    .element = CLAY_ATTACH_POINT_CENTER_CENTER,
                    .parent = CLAY_ATTACH_POINT_CENTER_CENTER
                }
            },
            .layout = {
                .layoutDirection = CLAY_TOP_TO_BOTTOM,
                .sizing = {
                    .width = CLAY_SIZING_GROW( .min=560, .max=850 ),
                    .height = CLAY_SIZING_GROW( .min=400, .max=600 )
                }
            },
            .backgroundColor = CLAY_COLOR_DARK_GREY,
            .cornerRadius = CLAY_CORNER_RADIUS(12)
    }) {
        CLAY({
                .layout = {
                    .childAlignment = {
                        .x = CLAY_ALIGN_X_CENTER,
                        .y = CLAY_ALIGN_Y_CENTER
                    },
                    .sizing = {
                        .width = CLAY_SIZING_GROW(0),
                        .height = CLAY_SIZING_GROW( .min=100, .max=120 )
                    }
                }
        }) {
            CLAY_TEXT(
                    CLAY_STRING("ОБ АВТОРЕ"),
                    CLAY_TEXT_CONFIG({
                        .fontId = fontIdNormal42,
                        .fontSize = 42,
                        .textColor = CLAY_COLOR_WHITE
                    })
            );
        }

        CLAY({
                .layout = {
                    .sizing = {
                        .width = CLAY_SIZING_GROW(0),
                        .height = CLAY_SIZING_PERCENT(0.15)
                    }
                }
        }) {}

        CLAY({
                .layout = {
                    .childAlignment = {
                        .x = CLAY_ALIGN_X_LEFT,
                        .y = CLAY_ALIGN_Y_CENTER
                    },
                    .sizing = {
                        .width = CLAY_SIZING_GROW(0),
                        .height = CLAY_SIZING_GROW( .min=50, .max=60 )
                    },
                    .padding = {
                        .left = 16,
                        .right = 16,
                        .top = 16,
                        .bottom = 0
                    }
                }
        }) {
            CLAY_TEXT(
                    CLAY_STRING("Автор: Ахметгалиев Адель Маратович"),
                    CLAY_TEXT_CONFIG({
                        .fontId = fontIdNormal42,
                        .fontSize = 42,
                        .textColor = CLAY_COLOR_WHITE
                    })
            );
        }

        CLAY({
                .layout = {
                    .childAlignment = {
                        .x = CLAY_ALIGN_X_LEFT,
                        .y = CLAY_ALIGN_Y_CENTER
                    },
                    .sizing = {
                        .width = CLAY_SIZING_GROW(0),
                        .height = CLAY_SIZING_GROW( .min=50, .max=60 )
                    },
                    .padding = {
                        .left = 16,
                        .right = 16,
                        .top = 0,
                        .bottom = 0
                    }
                }
        }) {
            CLAY_TEXT(
                    CLAY_STRING("Почта: adel.ahmetgaliev@yandex.ru"),
                    CLAY_TEXT_CONFIG({
                        .fontId = fontIdNormal42,
                        .fontSize = 42,
                        .textColor = CLAY_COLOR_WHITE
                    })
            );
        }
        
        CLAY({
                .layout = {
                    .childAlignment = {
                        .x = CLAY_ALIGN_X_CENTER,
                        .y = CLAY_ALIGN_Y_BOTTOM
                    },
                    .sizing = {
                        .width = CLAY_SIZING_GROW(0),
                        .height = CLAY_SIZING_GROW(0)
                    },
                    .padding = {
                        .left = 8,
                        .right = 0,
                        .top = 0,
                        .bottom = 32
                    }
                }
        }) {
            CLAY({
                    .id = CLAY_ID("CloseAboutAuthorPageButton"),
                    .layout = {
                        .childAlignment = {
                            .x = CLAY_ALIGN_X_CENTER,
                            .y = CLAY_ALIGN_Y_CENTER
                        },
                        .sizing = {
                            .width = CLAY_SIZING_GROW( .min=150, .max=150 ),
                            .height = CLAY_SIZING_GROW( .min=70, .max=70 )
                        }
                    },
                    .backgroundColor = Clay_Hovered() ? CLAY_COLOR_BUTTON_HOVER : CLAY_COLOR_BUTTON,
                    .cornerRadius = CLAY_CORNER_RADIUS(10)
            }) {
                CLAY_TEXT(
                        CLAY_STRING("Закрыть"),
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
