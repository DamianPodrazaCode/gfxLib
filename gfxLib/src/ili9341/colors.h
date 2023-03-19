#ifndef COLORS_H_
#define COLORS_H_

//format BGR
//#define	COLOR_BLACK                         (uint16_t)(0x0000)
//#define	COLOR_BLUE                          (uint16_t)(0x001F)
//#define	COLOR_RED                           (uint16_t)(0xF800)
//#define	COLOR_GREEN                         (uint16_t)(0x07E0)
//#define COLOR_CYAN                          (uint16_t)(0x07FF)
//#define COLOR_MAGENTA                       (uint16_t)(0xF81F)
//#define COLOR_YELLOW                        (uint16_t)(0xFFE0)
//#define COLOR_WHITE                         (uint16_t)(0xFFFF)
//
//#define COLOR_NAVY							(uint16_t)(0x000F)
//#define COLOR_DARKGREEN   					(uint16_t)(0x03E0)
//#define COLOR_DARKCYAN						(uint16_t)(0x03EF)
//#define COLOR_MAROON						(uint16_t)(0x7800)
//#define COLOR_PURPLE						(uint16_t)(0x780F)
//#define COLOR_OLIVE							(uint16_t)(0x7BE0)
//#define COLOR_LIGHTGREY						(uint16_t)(0xC618)
//#define COLOR_DARKGREY						(uint16_t)(0x7BEF)
//#define COLOR_ORANGE						(uint16_t)(0xFD20)
//#define COLOR_GREENYELLOW					(uint16_t)(0xAFE5)
//
////Grayscale
//#define COLOR_GRAY_15                       (uint16_t)(0x0861)    //  15  15  15
//#define COLOR_GRAY_30                       (uint16_t)(0x18E3)    //  30  30  30
//#define COLOR_GRAY_50                       (uint16_t)(0x3186)    //  50  50  50
//#define COLOR_GRAY_80                       (uint16_t)(0x528A)    //  80  80  80
//#define COLOR_GRAY_128                      (uint16_t)(0x8410)    // 128 128 128
//#define COLOR_GRAY_200                      (uint16_t)(0xCE59)    // 200 200 200
//#define COLOR_GRAY_225                      (uint16_t)(0xE71C)    // 225 225 225

enum COLOR { // 25 kolorów
	//format BGR
	COLOR_BLACK = (uint16_t)(0x0000),
	COLOR_BLUE = (uint16_t)(0x001F),
	COLOR_RED = (uint16_t)(0xF800),
	COLOR_GREEN =(uint16_t)(0x07E0),
	COLOR_CYAN =(uint16_t)(0x07FF),
	COLOR_MAGENTA =(uint16_t)(0xF81F),
	COLOR_YELLOW =(uint16_t)(0xFFE0),
	COLOR_WHITE =(uint16_t)(0xFFFF),

	COLOR_NAVY= (uint16_t)(0x000F),
	COLOR_DARKGREEN =(uint16_t)(0x03E0),
	COLOR_DARKCYAN =(uint16_t)(0x03EF),
	COLOR_MAROON =(uint16_t)(0x7800),
	COLOR_PURPLE= (uint16_t)(0x780F),
	COLOR_OLIVE =(uint16_t)(0x7BE0),
	COLOR_LIGHTGREY= (uint16_t)(0xC618),
	COLOR_DARKGREY= (uint16_t)(0x7BEF),
	COLOR_ORANGE =(uint16_t)(0xFD20),
	COLOR_GREENYELLOW= (uint16_t)(0xAFE5),

	COLOR_GRAY_15 =(uint16_t)(0x0861),    //  15  15  15
	COLOR_GRAY_30 =(uint16_t)(0x18E3),//  30  30  30
	COLOR_GRAY_50 =(uint16_t)(0x3186),//  50  50  50
	COLOR_GRAY_80 =(uint16_t)(0x528A),//  80  80  80
	COLOR_GRAY_128 =(uint16_t)(0x8410),// 128 128 128
	COLOR_GRAY_200 =(uint16_t)(0xCE59),// 200 200 200
	COLOR_GRAY_225 =(uint16_t)(0xE71C)// 225 225 225

};

#endif /* COLORS_H_ */
