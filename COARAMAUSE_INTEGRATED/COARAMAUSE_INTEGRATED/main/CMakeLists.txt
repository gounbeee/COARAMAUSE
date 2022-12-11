set(srcs "COARAMAUSE.c"
    "ili9340.c"
    "decode_png.c"
    "pngle.c"
    "pngSlide.c"
    "fontx.c"
    )


idf_component_register(SRCS ${srcs}
                    INCLUDE_DIRS ".")






# # tjpgd library does not exist in ESP32-S2 ROM.
# if(IDF_TARGET STREQUAL "esp32")
#     list(APPEND srcs "decode_jpeg.c")
# endif()
# 
# if(IDF_TARGET STREQUAL "esp32c3")
#     list(APPEND srcs "decode_jpeg.c")
# endif()


