// 1. Level 1 Command
#define	SSD1963_NOP					0x00 //No Operation
#define SSD1963_SWRESET				0x01 //Software Reset
#define SSD1963_GPM					0x0A //Get Power Mode (Get the current power mode)
#define SSD1963_GAM					0x0B //Get Address Mode (Get the frame buffer to the display panel read order)
#define SSD1963_GPF					0x0C //Get Pixel Format (Get the current pixel format for the RGB image data)
#define SSD1963_GDM					0x0D //Get Display mode (The display module returns the Display Image Mode status)
#define SSD1963_GSM					0x0E //Get Signal Mode (Get the current display signal mode from the peripheral)
#define SSD1963_ESM					0x10 //Enter Sleep Mode (Turn off the panel)
#define SSD1963_SLPOUT				0x11 //Sleep Out 101
#define SSD1963_PTLON				0x12 //Partial Mode ON 103
#define SSD1963_NORON				0x13 //Normal Display Mode ON 104
#define SSD1963_DINVOFF				0x20 //Display Inversion OFF 105
#define SSD1963_DINVON				0x21 //Display Inversion ON 106
#define SSD1963_GAMSET				0x26 //Gamma Set 107
#define SSD1963_DISPOFF				0x28 //Display OFF 108
#define SSD1963_DISPON				0x29 //Display ON 109
#define SSD1963_CASET				0x2A //Column Address Set 110
#define SSD1963_PASET				0x2B //Page (row) Address Set 112
#define SSD1963_RAMWR				0x2C //Memory Write 114
#define SSD1963_RGBSET				0x2D //Color Set 115
#define SSD1963_RAMRD				0x2E //Memory Read 116
#define SSD1963_PLTAR				0x30 //Partial Area 118
#define SSD1963_VSCRDEF				0x33 //Vertical Scrolling Definition 120
#define SSD1963_TEOFF				0x34 //Tearing Effect Line OFF 124
#define SSD1963_TEON				0x35 //Tearing Effect Line ON 125
#define SSD1963_MADCTL				0x36 //Memory Access Control 127
#define SSD1963_VSCRSADD			0x37 //Vertical Scrolling Start Address 129
#define SSD1963_IDMOFF				0x38 //Idle Mode OFF 131
#define SSD1963_IDMON				0x39 //Idle Mode ON 132
#define SSD1963_PIXSET				0x3A //COLMOD: Pixel Format Set 134
#define SSD1963_WRITEMEMCONTINUE	0x3C //Write Memory Continue 135
#define SSD1963_READMEMCONTINUE		0x3E //Read Memory Continue 137
#define SSD1963_SETSCANLINE			0x44 //Set Tear Scanline 139
#define SSD1963_GETSCANLINE			0x45 //Get Scanline 140
#define SSD1963_WRDISBV				0x51 //Write Display Brightness 141
#define SSD1963_RDDISBV				0x52 //Read Display Brightness 142
#define SSD1963_WRCTRLD				0x53 //Write CTRL Display 143
#define SSD1963_RDCTRLD				0x54 //Read CTRL Display 145
#define SSD1963_WRCABC				0x55 //Write Content Adaptive Brightness Control 147
#define SSD1963_RDCABC				0x56 //Read Content Adaptive Brightness Control 148
#define SSD1963_WRITECABCMIN		0x5E //Write CABC Minimum Brightness 149
#define SSD1963_READCABCMIN			0x5F //Read CABC Minimum Brightness 150
#define SSD1963_RDID1               0xDA //Read ID1 151
#define SSD1963_RDID2               0xDB //Read ID2 152
#define SSD1963_RDID3               0xDC //Read ID3 153

// 2. Level 2 Command
#define SSD1963_IFMODE				0xB0 //RGB  Interface Signal Control 154
#define SSD1963_FRMCTR1				0xB1 //Frame Rate Control (In Normal Mode/Full Colors) 155
#define SSD1963_FRMCTR2				0xB2 //Frame Rate Control (In Idle Mode/8 Colors) 157
#define SSD1963_FRMCTR3				0xB3 //Frame Rate Control (In Partial Mode/Full Colors) 159
#define SSD1963_INVTR				0xB4 //Display Inversion Control 161
#define SSD1963_PRCTR				0xB5 //Blanking Porch Control 162
#define SSD1963_DISCTRL				0xB6 //Display Function Control 164
#define SSD1963_ETMOD				0xB7 //Entry Mode Set 168
#define SSD1963_BACKLIGHTCONTROL1	0xB8 //Backlight Control 1 169
#define SSD1963_BACKLIGHTCONTROL2	0xB9 //Backlight Control 2 170
#define SSD1963_BACKLIGHTCONTROL3	0xBA //Backlight Control 3 172
#define SSD1963_BACKLIGHTCONTROL4	0xBB //Backlight Control 4 173
#define SSD1963_BACKLIGHTCONTROL5	0xBC //Backlight Control 5 175
#define SSD1963_BACKLIGHTCONTROL7	0xBE //Backlight Control 7 176
#define SSD1963_BACKLIGHTCONTROL8	0xBF //Backlight Control 8 177
#define SSD1963_PWCTRL1				0xC0 //Power Control 1 178
#define SSD1963_PWCTRL2				0xC1 //Power Control 2 179
#define SSD1963_VMCTRL1				0xC5 //VCOM Control 1 180
#define SSD1963_VMCTRL2				0xC7 //VCOM Control 2 182
#define SSD1963_NVMWR				0xD0 //NV Memory Write 184
#define SSD1963_NVMPKEY				0xD1 //NV Memory Protection Key 185
#define SSD1963_RDNVM				0xD2 //NV Memory Status Read 186
#define SSD1963_RDID4				0xD3 //Read ID4 187
#define SSD1963_PGAMCTRL			0xE0 //Positive Gamma Correction 188
#define SSD1963_NGAMCTRL			0xE1 //Negative Gamma Correction 189
#define SSD1963_DGAMCTRL1			0xE2 //Digital Gamma Control 1 190
#define SSD1963_DGAMCTRL2			0xE3 //Digital Gamma Control 2 191
#define SSD1963_IFCTL				0xF6 //Interface Control 192

//3. EXTEND register control
#define SSD1963_PCA                 0xCB //Power Control A 195
#define SSD1963_PCB					0xCF //Power Control B 196
#define SSD1963_DTCA_ic        		0xE8 //Driver Timming Control A - for internal clock  197
#define SSD1963_DTCA_ec         	0xE9 //Driver Timming Control A - for external clock 198
#define SSD1963_DTCB            	0xEA //Driver Timming Control B 199
#define SSD1963_POSC            	0xED //Power On Sequence Control 200
#define SSD1963_E3G             	0xF2 //Enable 3G 201
#define SSD1963_PRC					0xF7 //Pump Ratio Control 202

