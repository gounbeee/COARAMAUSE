set(srcs "main.c"
	"ili9340.c"
	"fontx.c"
	"decode_png.c"
	"pngle.c"
	"pngSlide.c"
	"uart_slave_lcd.c"
	"i2sSound.c"
	"wavType.c"
	)

# tjpgd library does not exist in ESP32-S2 ROM.
if(IDF_TARGET STREQUAL "esp32")
	list(APPEND srcs "decode_jpeg.c")
endif()

if(IDF_TARGET STREQUAL "esp32c3")
	list(APPEND srcs "decode_jpeg.c")
endif()

idf_component_register(SRCS ${srcs}
					INCLUDE_DIRS ".")
