// 1. Level 1 Command
#define	ILI9341_NOP					0x00 //No Operation 89
#define ILI9341_SWRESET				0x01 //Software Reset 90
#define ILI9341_RDDIDIF				0x04 //Read Display Identificatin Information 91
#define ILI9341_RDDST				0x09 //Read Display Status 92
#define ILI9341_RDDPM				0x0A //Read Display Power Mode 94
#define ILI9341_RDDMADCTL			0x0B //Read Display MADCTL 95
#define ILI9341_RDDCOLMOD			0x0C //Read Display Pixel Format 96
#define ILI9341_RDDIM				0x0D //Read Display Image Format 97
#define ILI9341_RDDSM				0x0E //Read Display Signal Mode 98
#define ILI9341_RDDSDR				0x0F //Read Display SELF-Diagnostic Result 99
#define ILI9341_SPLIN				0x10 //Enter Sleep Mode 100
#define ILI9341_SLPOUT				0x11 //Sleep Out 101
#define ILI9341_PTLON				0x12 //Partial Mode ON 103
#define ILI9341_NORON				0x13 //Normal Display Mode ON 104
#define ILI9341_DINVOFF				0x20 //Display Inversion OFF 105
#define ILI9341_DINVON				0x21 //Display Inversion ON 106
#define ILI9341_GAMSET				0x26 //Gamma Set 107
#define ILI9341_DISPOFF				0x28 //Display OFF 108
#define ILI9341_DISPON				0x29 //Display ON 109
#define ILI9341_CASET				0x2A //Column Address Set 110
#define ILI9341_PASET				0x2B //Page (row) Address Set 112
#define ILI9341_RAMWR				0x2C //Memory Write 114
#define ILI9341_RGBSET				0x2D //Color Set 115
#define ILI9341_RAMRD				0x2E //Memory Read 116
#define ILI9341_PLTAR				0x30 //Partial Area 118
#define ILI9341_VSCRDEF				0x33 //Vertical Scrolling Definition 120
#define ILI9341_TEOFF				0x34 //Tearing Effect Line OFF 124
#define ILI9341_TEON				0x35 //Tearing Effect Line ON 125
#define ILI9341_MADCTL				0x36 //Memory Access Control 127
#define ILI9341_VSCRSADD			0x37 //Vertical Scrolling Start Address 129
#define ILI9341_IDMOFF				0x38 //Idle Mode OFF 131
#define ILI9341_IDMON				0x39 //Idle Mode ON 132
#define ILI9341_PIXSET				0x3A //COLMOD: Pixel Format Set 134
#define ILI9341_WRITEMEMCONTINUE	0x3C //Write Memory Continue 135
#define ILI9341_READMEMCONTINUE		0x3E //Read Memory Continue 137
#define ILI9341_SETSCANLINE			0x44 //Set Tear Scanline 139
#define ILI9341_GETSCANLINE			0x45 //Get Scanline 140
#define ILI9341_WRDISBV				0x51 //Write Display Brightness 141
#define ILI9341_RDDISBV				0x52 //Read Display Brightness 142
#define ILI9341_WRCTRLD				0x53 //Write CTRL Display 143
#define ILI9341_RDCTRLD				0x54 //Read CTRL Display 145
#define ILI9341_WRCABC				0x55 //Write Content Adaptive Brightness Control 147
#define ILI9341_RDCABC				0x56 //Read Content Adaptive Brightness Control 148
#define ILI9341_WRITECABCMIN		0x5E //Write CABC Minimum Brightness 149
#define ILI9341_READCABCMIN			0x5F //Read CABC Minimum Brightness 150
#define ILI9341_RDID1               0xDA //Read ID1 151
#define ILI9341_RDID2               0xDB //Read ID2 152
#define ILI9341_RDID3               0xDC //Read ID3 153

// 2. Level 2 Command
#define ILI9341_IFMODE				0xB0 //RGB  Interface Signal Control 154
#define ILI9341_FRMCTR1				0xB1 //Frame Rate Control (In Normal Mode/Full Colors) 155
#define ILI9341_FRMCTR2				0xB2 //Frame Rate Control (In Idle Mode/8 Colors) 157
#define ILI9341_FRMCTR3				0xB3 //Frame Rate Control (In Partial Mode/Full Colors) 159
#define ILI9341_INVTR				0xB4 //Display Inversion Control 161
#define ILI9341_PRCTR				0xB5 //Blanking Porch Control 162
#define ILI9341_DISCTRL				0xB6 //Display Function Control 164
#define ILI9341_ETMOD				0xB7 //Entry Mode Set 168
#define ILI9341_BACKLIGHTCONTROL1	0xB8 //Backlight Control 1 169
#define ILI9341_BACKLIGHTCONTROL2	0xB9 //Backlight Control 2 170
#define ILI9341_BACKLIGHTCONTROL3	0xBA //Backlight Control 3 172
#define ILI9341_BACKLIGHTCONTROL4	0xBB //Backlight Control 4 173
#define ILI9341_BACKLIGHTCONTROL5	0xBC //Backlight Control 5 175
#define ILI9341_BACKLIGHTCONTROL7	0xBE //Backlight Control 7 176
#define ILI9341_BACKLIGHTCONTROL8	0xBF //Backlight Control 8 177
#define ILI9341_PWCTRL1				0xC0 //Power Control 1 178
#define ILI9341_PWCTRL2				0xC1 //Power Control 2 179
#define ILI9341_VMCTRL1				0xC5 //VCOM Control 1 180
#define ILI9341_VMCTRL2				0xC7 //VCOM Control 2 182
#define ILI9341_NVMWR				0xD0 //NV Memory Write 184
#define ILI9341_NVMPKEY				0xD1 //NV Memory Protection Key 185
#define ILI9341_RDNVM				0xD2 //NV Memory Status Read 186
#define ILI9341_RDID4				0xD3 //Read ID4 187
#define ILI9341_PGAMCTRL			0xE0 //Positive Gamma Correction 188
#define ILI9341_NGAMCTRL			0xE1 //Negative Gamma Correction 189
#define ILI9341_DGAMCTRL1			0xE2 //Digital Gamma Control 1 190
#define ILI9341_DGAMCTRL2			0xE3 //Digital Gamma Control 2 191
#define ILI9341_IFCTL				0xF6 //Interface Control 192

//3. EXTEND register control
#define ILI9341_PCA                 0xCB //Power Control A 195
#define ILI9341_PCB					0xCF //Power Control B 196
#define ILI9341_DTCA_ic        		0xE8 //Driver Timming Control A - for internal clock  197
#define ILI9341_DTCA_ec         	0xE9 //Driver Timming Control A - for external clock 198
#define ILI9341_DTCB            	0xEA //Driver Timming Control B 199
#define ILI9341_POSC            	0xED //Power On Sequence Control 200
#define ILI9341_E3G             	0xF2 //Enable 3G 201
#define ILI9341_PRC					0xF7 //Pump Ratio Control 202

