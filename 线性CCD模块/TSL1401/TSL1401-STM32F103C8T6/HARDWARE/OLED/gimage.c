#include "bank.h"
//图库中的前两个字节依次为图片的宽度和高度
unsigned char gImage_hebust_40x39[3122] = { /* 0X10,0X10,0X00,0X28,0X00,0X27,0X01,0X1B, */0x28,0x27,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XDF,
0XF7,0XBE,0XD6,0X9B,0XDE,0XBC,0XFF,0XDF,0XFF,0XFF,0XE7,0X3D,0XCE,0X3A,0XF7,0X9E,
0XFF,0XDF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF7,0XBF,0XDE,0XDC,0XD6,0XBC,0XE7,0X1C,
0XE7,0X1C,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XEF,0X7D,
0XDE,0XFC,0XD6,0XBC,0XD6,0X7A,0XF7,0X9E,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XF7,0XBE,0XCE,0X5A,0XD6,0X9B,0XFF,0XDF,0XC6,0X39,0XA4,0XF7,
0XE7,0X3D,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X9C,0XB6,
0XB5,0X78,0XFF,0XFF,0XFF,0XFF,0XDE,0XFC,0XC6,0X3A,0XF7,0X9E,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XD6,0XBB,0XD6,0XBB,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X8C,0X96,0XBD,0XF9,
0XDE,0XDC,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XD6,0X9B,0XA4,0XF6,
0X83,0XF4,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XE7,0X1D,0XCE,0X5A,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XC6,0X3A,0XF7,0XBF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XB5,0XB8,0XEF,0X5D,
0XFF,0XFF,0XFF,0XFF,0XEF,0X7E,0XEF,0X7E,0XEF,0X7D,0XF7,0X9E,0XCE,0X7A,0XF7,0XBD,
0XEF,0X3D,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XC6,0X19,
0XF7,0XBF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF7,0XBE,0XD6,0X7B,
0XEF,0X7E,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XD6,0XDB,0X9D,0X58,
0X5B,0XD6,0X3B,0X14,0X22,0X51,0X22,0X12,0X19,0XF1,0X19,0X90,0X3A,0X32,0X52,0XF3,
0XA5,0X17,0XEF,0X5D,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XF7,0XBE,
0XD6,0XBC,0XE7,0X3D,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XDF,0XCE,0X7B,0XFF,0XFF,
0X63,0X53,0XB5,0X98,0XFF,0XFF,0XFF,0XFF,0XE7,0X5D,0X7C,0XB7,0X3B,0X55,0X3B,0X75,
0X43,0X96,0X43,0XB6,0X43,0X96,0X43,0X55,0X3B,0X14,0X3A,0XB3,0X32,0X52,0X31,0XF1,
0X21,0X4F,0X21,0X2F,0X6B,0X53,0XE7,0X3D,0XFF,0XFF,0XC6,0X19,0XB5,0XB8,0X8C,0X34,
0XFF,0XFF,0XE6,0XFC,0XEF,0X5D,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XCE,0X5A,0XFF,0XFF,0XFF,0XFF,
0X63,0X54,0XB5,0XB8,0XFF,0XFF,0X9D,0X58,0X33,0X14,0X3B,0X96,0X4C,0X17,0X4C,0X17,
0X54,0X37,0X4C,0X17,0X4B,0XF6,0X43,0XB6,0X3B,0X75,0X3B,0X34,0X3A,0XB3,0X32,0X52,
0X32,0X11,0X31,0XB0,0X29,0X2F,0X29,0X0E,0X94,0X96,0XFF,0XFF,0XC6,0X19,0XF7,0XBE,
0XFF,0XFF,0XFF,0XFF,0XD6,0X7A,0XF7,0X9E,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XCE,0X5B,0XFF,0XDF,0XFF,0XFF,0XFF,0XFF,
0XCE,0X9C,0XFF,0XFF,0X6C,0X15,0X33,0X14,0X43,0XD6,0X54,0X37,0X54,0X57,0X54,0X58,
0X54,0X78,0X54,0X58,0X54,0X58,0X4C,0X17,0X4B,0XD6,0X43,0X75,0X3A,0XF4,0X32,0X92,
0X32,0X32,0X31,0XF1,0X31,0XB0,0X31,0X8F,0X20,0XCD,0X62,0XF2,0XFF,0XFF,0XFF,0XDF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XC6,0X1A,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XEF,0X5D,0XDE,0XFC,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0X5B,0XD5,0X2A,0XF4,0X4B,0XD6,0X4C,0X37,0X54,0X58,0X5C,0X98,0X5C,0XD9,
0X5C,0XD9,0X5C,0XB9,0X5C,0X98,0X54,0X58,0X4C,0X17,0X43,0XD6,0X3B,0X55,0X3A,0XD3,
0X32,0X52,0X32,0X11,0X31,0XB0,0X31,0X8F,0X39,0X8F,0X28,0XCE,0X5A,0X92,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XDF,0XD6,0X7B,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XC5,0XF9,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0X74,0X14,0X2A,0X93,0X43,0X96,0X4B,0XF7,0X54,0X58,0X5C,0X98,0X5C,0XD9,0X65,0X1A,
0X65,0X19,0X65,0X1A,0X5C,0XD9,0X5C,0X78,0X54,0X37,0X4B,0XF6,0X43,0X75,0X3A,0XF4,
0X32,0X72,0X32,0X11,0X31,0XD0,0X31,0X8F,0X39,0X8F,0X39,0X6F,0X28,0XCE,0X6B,0X32,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XDE,0XFC,0XF7,0X9E,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XE7,0X3D,0XDE,0XFC,0XD6,0X7B,0XFF,0XFF,0XFF,0XFF,0XBE,0X1A,
0X22,0X11,0X3B,0X34,0X43,0XB6,0X4C,0X17,0X54,0X58,0X5C,0XD9,0X64,0XF9,0X6D,0X5A,
0X6D,0X5A,0X6D,0X5A,0X5C,0XF9,0X5C,0XB9,0X54,0X58,0X4C,0X17,0X43,0X96,0X3B,0X14,
0X32,0X72,0X32,0X31,0X31,0XD0,0X31,0X8F,0X39,0X8F,0X39,0X6F,0X39,0X6F,0X20,0XAE,
0XBD,0XB9,0XFF,0XFF,0XAD,0X36,0XE7,0X1C,0XD6,0X9A,0XDE,0XFC,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XD6,0XBB,0XFF,0XFF,0X4A,0X2F,0XC5,0XFA,0XCE,0X5A,0X3A,0X72,
0X32,0X72,0X3B,0X34,0X43,0XB6,0X4C,0X17,0X54,0X78,0X5C,0XD9,0X65,0X19,0X6D,0X5A,
0X75,0X7B,0X6D,0X5A,0X64,0XF9,0X5C,0XB9,0X54,0X58,0X4C,0X17,0X43,0X96,0X3B,0X14,
0X32,0X92,0X32,0X31,0X31,0XD0,0X31,0X90,0X39,0X8F,0X39,0X6F,0X39,0X6F,0X31,0X2F,
0X39,0X4F,0XEF,0X9E,0XBD,0XD9,0XB5,0X77,0X73,0X93,0XCE,0X5A,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XF7,0XBF,0XD6,0XBB,0XD6,0X9B,0XAD,0X77,0XFF,0XFE,0XA5,0X37,0X21,0X90,
0X32,0X93,0X3B,0X14,0X43,0XB6,0X4C,0X17,0X54,0X58,0X5C,0XB9,0X5C,0XF9,0X65,0X3A,
0X6D,0X3A,0X65,0X39,0X5C,0XD9,0X5C,0X98,0X54,0X38,0X4B,0XF7,0X43,0X75,0X3A,0XF4,
0X32,0X52,0X32,0X11,0X31,0XD0,0X31,0X8F,0X39,0X8F,0X39,0X6F,0X39,0X6F,0X31,0X4F,
0X28,0XCE,0X8C,0X15,0XCE,0X5B,0XFF,0XFF,0XDE,0XBC,0XC5,0XF9,0XEF,0X5E,0XFF,0XFF,
0XFF,0XFF,0XEF,0X3D,0XF7,0X9E,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X4A,0X71,0X29,0XF1,
0X32,0X72,0X3A,0XF4,0X43,0X75,0X4B,0XF6,0X54,0X37,0X54,0X78,0X5C,0XB9,0X5C,0XF9,
0X5C,0XF9,0X5C,0XD9,0X5C,0XB9,0X54,0X78,0X54,0X37,0X4B,0XD6,0X43,0X75,0X4B,0X75,
0X42,0XF4,0X32,0X31,0X31,0XB0,0X31,0X8F,0X31,0X8F,0X39,0X6F,0X39,0X6F,0X31,0X4F,
0X31,0X0F,0X49,0XF0,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XD6,0X9B,0XFF,0XFF,
0XFF,0XFF,0XD6,0X7B,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XE7,0X5D,0X21,0X2E,0X31,0XF1,
0X32,0X52,0X3A,0XB3,0X3B,0X34,0X43,0XB6,0X4C,0X17,0X54,0X58,0X5C,0X78,0X5C,0X98,
0X5C,0X98,0X5C,0X98,0X54,0X78,0X54,0X37,0X4B,0XF7,0X3B,0X75,0X74,0X97,0XC5,0XF7,
0XB5,0XB6,0X9D,0X58,0X29,0X90,0X31,0X8F,0X31,0X6F,0X39,0X6F,0X39,0X4F,0X31,0X4F,
0X31,0X4F,0X20,0XAD,0XE7,0X1D,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XCE,0X3A,0XFF,0XFF,
0XFF,0XFF,0XDE,0XBC,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XAD,0X57,0X21,0X0F,0X31,0XF1,
0X32,0X31,0X32,0X92,0X3A,0XF4,0X3B,0X55,0X43,0XB6,0X4B,0XF7,0X54,0X37,0X54,0X58,
0X54,0X58,0X54,0X58,0X4C,0X37,0X4B,0XF6,0X43,0XB6,0X33,0X14,0X6C,0X35,0XCD,0XF6,
0XCE,0X17,0XCE,0X9A,0X29,0XB0,0X31,0X6F,0X31,0X6F,0X39,0X6F,0X39,0X4F,0X31,0X4F,
0X39,0X4F,0X20,0XCE,0XA5,0X37,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XEF,0X3D,0XFF,0XFF,
0XFF,0XFF,0XC6,0X19,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X94,0X97,0X29,0X2F,0X31,0XD0,
0X31,0XF1,0X32,0X32,0X32,0X93,0X3A,0XF4,0X3B,0X55,0X43,0X96,0X43,0XD6,0X4B,0XF6,
0X4B,0XF6,0X4B,0XD6,0X43,0XB6,0X43,0X96,0X3B,0X54,0X2A,0XB3,0X7C,0X96,0XE6,0XDA,
0XEF,0X5D,0XF7,0XBE,0X32,0X11,0X31,0X6F,0X39,0X6F,0X39,0X6F,0X39,0X4F,0X31,0X4F,
0X39,0X4F,0X28,0XEE,0X8C,0X56,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XCE,0X7A,0XF7,0X9E,
0XFF,0XFF,0XDE,0XDC,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X62,0XD1,0X29,0X4F,0X31,0XB0,
0X31,0XD1,0X32,0X11,0X32,0X52,0X32,0X93,0X3A,0XD3,0X3B,0X14,0X3B,0X55,0X43,0X75,
0X43,0X75,0X43,0X75,0X3B,0X35,0X3B,0X14,0X3A,0XD3,0X32,0X73,0X6B,0XD1,0XBD,0XD7,
0XFF,0XFF,0XFF,0XFF,0X52,0XF3,0X31,0X2E,0X39,0X6F,0X39,0X4F,0X31,0X4F,0X39,0X4F,
0X31,0X4F,0X31,0X2F,0X5A,0XB1,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XDE,0XFC,0XF7,0XBF,
0XFF,0XFF,0XE6,0XFC,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0X5A,0XB2,0X20,0XEE,0X29,0X2E,
0X29,0X4F,0X29,0X8F,0X31,0XD0,0X32,0X11,0X32,0X72,0X32,0X93,0X3A,0XD3,0X3A,0XD3,
0X3A,0XF4,0X3A,0XD3,0X3A,0XB3,0X32,0X93,0X32,0X52,0X32,0X93,0X7B,0XCF,0X94,0XB2,
0XFF,0XFF,0XFF,0XFF,0X84,0X97,0X28,0XEE,0X39,0X6F,0X39,0X4F,0X39,0X4F,0X31,0X4F,
0X31,0X6F,0X29,0X2F,0X5A,0XD2,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XE7,0X3D,0XFF,0XDF,
0XFF,0XFF,0XD6,0X9B,0XFF,0XDF,0XDE,0XDC,0XFF,0XFF,0X8C,0X55,0X73,0XF5,0X94,0XD7,
0X94,0XD8,0X7C,0X36,0X4A,0XF3,0X29,0XF1,0X21,0XB0,0X2A,0X11,0X32,0X52,0X32,0X52,
0X32,0X72,0X32,0X72,0X32,0X52,0X32,0X32,0X29,0XD1,0X5B,0X96,0X6B,0X2B,0X6B,0X4D,
0XFF,0XDE,0XF7,0X7D,0XC6,0X5B,0X28,0XEE,0X39,0X4F,0X31,0X4F,0X31,0X4F,0X39,0X2F,
0X31,0X4F,0X29,0X0F,0X63,0X12,0XFF,0XFF,0XEF,0X7E,0XFF,0XFF,0XCE,0X7B,0XF7,0X9E,
0XFF,0XFF,0XC6,0X1A,0XFF,0XFF,0X8C,0X34,0XF7,0X9E,0XDE,0XDA,0XBD,0XB4,0XE6,0XFA,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XE7,0X5D,0X9D,0X59,0X42,0XD3,0X21,0X90,0X31,0XF1,
0X32,0X11,0X32,0X11,0X31,0XF1,0X31,0XF0,0X29,0X90,0X84,0X96,0X6B,0X2B,0X52,0XAA,
0XCE,0X18,0XDE,0XBA,0XDE,0XDA,0X41,0XF1,0X31,0X2E,0X31,0X4F,0X31,0X0E,0X31,0X2F,
0X52,0XF4,0X5B,0X32,0XB5,0XD9,0XFF,0XFF,0XAD,0X58,0XF7,0XBE,0XDE,0XFC,0XF7,0XBF,
0XFF,0XFF,0XE7,0X3D,0XF7,0XBE,0XBD,0XD9,0XDE,0XDB,0XE7,0X1D,0X7B,0XD4,0X84,0X56,
0XA5,0X79,0XDF,0X3E,0XFF,0XFF,0XFF,0XDE,0XEF,0X3C,0XDE,0XBA,0X94,0XF7,0X3A,0X52,
0X29,0X70,0X31,0XB0,0X31,0XB0,0X31,0X6F,0X4A,0XB3,0X94,0XB2,0X73,0X6D,0X6B,0X2C,
0XBD,0XD7,0XB5,0X95,0XB5,0X95,0X8C,0X56,0X28,0XEE,0X31,0X0E,0X42,0X11,0X8C,0X95,
0X6B,0X2C,0X41,0XC6,0XBD,0XD6,0XD6,0XBB,0XAD,0X56,0XDE,0XDB,0XDE,0XFC,0XFF,0XFF,
0XFF,0XFF,0XD6,0XBB,0XFF,0XFF,0XA5,0X17,0XB5,0XB8,0XFF,0XFF,0X20,0XAD,0X28,0XEE,
0X28,0XEE,0X29,0X4F,0X5A,0XF3,0XB5,0XDA,0XE7,0X3B,0XCE,0X17,0XB5,0X74,0XAD,0X75,
0X63,0X74,0X29,0X4F,0X31,0X6F,0X29,0X6F,0X94,0XD6,0X8C,0X30,0X7B,0XAE,0X84,0X54,
0X7C,0X16,0XAD,0X33,0XA4,0XD2,0XAD,0X35,0X39,0X90,0X5A,0XB3,0X9C,0XD3,0X62,0XCA,
0X73,0X6D,0X6B,0XD3,0XFF,0XFF,0XB5,0X97,0XAD,0X78,0XFF,0XFF,0XD6,0X9B,0XFF,0XFF,
0XFF,0XFF,0XEF,0X7E,0XEF,0X7D,0XD6,0X7B,0X9C,0XF6,0XFF,0XFF,0X6B,0X13,0X28,0XEE,
0X39,0X4F,0X39,0X4F,0X31,0X2E,0X29,0X0E,0X5A,0XF3,0XBD,0XF9,0XB5,0X74,0X9C,0XB2,
0X9C,0XB2,0X7C,0X36,0X21,0X0F,0X7C,0X36,0XAD,0X33,0X94,0X70,0X9C,0XD4,0X41,0XF1,
0X31,0X70,0XA5,0X15,0X8C,0X30,0X8C,0X30,0X9D,0X18,0XA5,0X35,0X83,0XCE,0X8C,0X71,
0X63,0XB5,0X5B,0X34,0XFF,0XFF,0XDE,0XDC,0XBD,0XD8,0XFF,0XFF,0XD6,0XBB,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XD6,0XBB,0XEF,0X7D,0XAD,0X77,0XDE,0XDB,0XD6,0X9C,0X18,0X6D,
0X31,0X2F,0X39,0X4F,0X39,0X4F,0X39,0X6F,0X31,0X0E,0X31,0X70,0X94,0XD7,0XA4,0XF2,
0X84,0X0F,0X7B,0XCE,0XBD,0XFA,0XCE,0X17,0XAD,0X53,0XA5,0X56,0X41,0XF1,0X31,0X0E,
0X30,0XEE,0X6B,0X35,0X8C,0X50,0X73,0X6D,0X7B,0XCE,0XA5,0X13,0X9C,0XB1,0X6B,0XF7,
0X10,0XCE,0XCE,0X7B,0XDE,0XFB,0X9C,0XB6,0XEF,0X7D,0XE7,0X1C,0XF7,0X9E,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XD6,0XBB,0XFF,0XDF,0XF7,0XBE,0XFF,0XFF,0XFF,0XFF,0X7B,0XD4,
0X39,0XB0,0X31,0X0F,0X31,0X0E,0X31,0X2F,0X31,0X2F,0X31,0X0F,0X20,0XAD,0X7B,0XF6,
0X8C,0X50,0X73,0X4D,0X6B,0X0B,0XBD,0XD6,0XA5,0X19,0X29,0X2F,0X31,0X0E,0X39,0X4F,
0X31,0X4F,0X28,0XEE,0X7B,0XD5,0X63,0X0B,0X5A,0XAA,0X62,0XEB,0XB5,0XFA,0X21,0X91,
0X53,0X13,0XFF,0XFF,0XB5,0X98,0XA5,0X16,0XFF,0XFF,0XCE,0X5A,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XF7,0XBF,0XD6,0X9B,0XFF,0XFF,0X9C,0XF5,0XDE,0XDB,0XFF,0XFF,
0X83,0XF0,0X7B,0XD3,0X62,0XF4,0X41,0XB1,0X39,0X4F,0X41,0XD1,0X6B,0X54,0XC6,0X1B,
0XFF,0XFF,0X83,0XEF,0X5A,0XCA,0X52,0X8A,0X7B,0XF2,0X52,0X52,0X28,0XEE,0X39,0X2F,
0X39,0X4F,0X20,0XCE,0X7C,0X36,0XEF,0X5C,0X7B,0X8D,0X52,0X68,0X4A,0X27,0X6B,0XB0,
0XF7,0XDF,0XE7,0X1C,0XA4,0XF7,0XEF,0X9E,0XF7,0X9E,0XDE,0XFC,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XDE,0XBC,0XFF,0XFF,0XD6,0X9B,0X7B,0XD2,0XFF,0XFF,
0XD6,0XBA,0X5A,0XCA,0X63,0X2B,0X7B,0XCF,0X94,0X94,0XD6,0XBA,0XEF,0X5D,0XCE,0X7C,
0X84,0X16,0X6B,0X54,0X84,0X51,0X52,0X68,0X4A,0X48,0X73,0X8E,0X73,0XD5,0X39,0X90,
0X20,0XEE,0X7C,0X16,0XFF,0XFF,0XFF,0XFF,0XC6,0X5C,0X6B,0XF4,0X63,0XB1,0XC6,0X17,
0XFF,0XFF,0XAD,0X37,0XBD,0XD8,0XFF,0XFF,0XC6,0X3A,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XE7,0X3D,0XFF,0XFF,0XBD,0XD9,0XBD,0XB8,
0XFF,0XFF,0XBE,0X1A,0X31,0XD0,0X4A,0X71,0X4A,0X51,0X4A,0X31,0X39,0X8F,0X28,0XEE,
0X28,0XEE,0X28,0XEE,0X4A,0X32,0X84,0X54,0X63,0X0B,0X42,0X06,0X52,0XA9,0X73,0XB0,
0X9D,0X17,0XFF,0XFF,0XEF,0X9E,0X74,0X36,0X29,0XD1,0X11,0X0F,0XA5,0X79,0XFF,0XFF,
0XAD,0X57,0XBD,0XD8,0XFF,0XFF,0XDE,0XDC,0XF7,0X9E,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XDF,0XEF,0X7E,0XFF,0XFF,0X9C,0XD6,
0XAD,0X37,0XFF,0XFF,0XC6,0X1A,0X29,0X0E,0X29,0X0E,0X31,0X4F,0X31,0X4F,0X31,0X6F,
0X31,0X6F,0X31,0X6F,0X31,0X4F,0X29,0X4F,0X52,0XF4,0X7C,0X55,0X63,0X8F,0X7C,0X53,
0X6B,0XF4,0X53,0X34,0X29,0XD0,0X21,0X70,0X21,0XB0,0XBE,0X1A,0XFF,0XFF,0X9C,0XD6,
0X9C,0XB6,0XF7,0X9E,0XF7,0XBE,0XD6,0X9B,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XDF,0XF7,0X9E,0XFF,0XFF,
0XA5,0X16,0X9C,0XB6,0XF7,0XBE,0XF7,0XBE,0X63,0X33,0X21,0X0F,0X29,0X6F,0X31,0XB0,
0X31,0XB0,0X31,0XB0,0X31,0XB0,0X31,0XB0,0X31,0X90,0X29,0X90,0X31,0XD1,0X29,0XB1,
0X29,0XB0,0X21,0X90,0X21,0X70,0X63,0X74,0XF7,0XBE,0XEF,0X7D,0XFF,0XDF,0XDE,0XFC,
0XFF,0XDF,0XFF,0XDE,0XD6,0X7B,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XDE,0XDC,0XE7,0X3D,
0XEF,0X9D,0XC5,0XFA,0X9C,0XD6,0XC6,0X19,0XFF,0XFF,0XCE,0X7B,0X63,0X33,0X29,0X90,
0X19,0X4F,0X21,0X90,0X29,0X90,0X29,0XB0,0X29,0XB0,0X29,0XB0,0X21,0XB0,0X21,0X70,
0X29,0XD0,0X63,0X74,0XC6,0X3A,0XFF,0XFF,0XC6,0X19,0X94,0X95,0XB5,0XB8,0XFF,0XFF,
0XF7,0XBE,0XC6,0X3A,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XDE,0XBB,
0XDE,0XDC,0XFF,0XFF,0XD6,0X9B,0XC6,0X19,0XB5,0X78,0XCE,0X5A,0XFF,0XFF,0XF7,0XBE,
0XC6,0X5B,0X8C,0X77,0X6B,0XD5,0X52,0XF3,0X52,0XF3,0X73,0XD5,0X8C,0X97,0XC6,0X5B,
0XF7,0XBE,0XFF,0XFF,0XFF,0XFF,0XA5,0X17,0X84,0X13,0XBD,0XD9,0XFF,0XFF,0XE7,0X3D,
0XCE,0X7B,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XF7,0X9E,0XBD,0XF9,0XFF,0XFF,0XFF,0XFF,0XEF,0X5D,0XC6,0X3A,0XFF,0XDF,0XAD,0X57,
0XBD,0XD9,0XFF,0XFF,0XF7,0XBE,0XF7,0XBE,0XEF,0X5D,0XEF,0X7D,0XE7,0X3C,0XD6,0XBB,
0XC6,0X39,0XA4,0XF7,0XFF,0XFF,0XCE,0X5A,0XF7,0XBE,0XFF,0XFF,0XD6,0X9B,0XDE,0XDC,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XCE,0X5A,0XDE,0XBB,0XFF,0XDF,0XFF,0XFF,0XEF,0X7D,0XAD,0X37,
0XB5,0X78,0XFF,0XFF,0XAD,0X57,0XA5,0X17,0XDE,0XDB,0X7B,0XD2,0XD6,0X7B,0X7B,0XF4,
0XC6,0X3A,0XC6,0X39,0XFF,0XFF,0XFF,0XFF,0XE7,0X1C,0XCE,0X5A,0XFF,0XDF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XBF,0XCE,0X7B,0XCE,0X7B,0XE7,0X3D,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XE7,0X3D,0XE7,0X5D,0XDE,0XDC,0XDE,0XFC,0XEF,0X7E,0XFF,0XFF,
0XFF,0XFF,0XF7,0X9E,0XD6,0X9B,0XCE,0X5A,0XEF,0X7E,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XEF,0X5D,0XCE,0X7B,
0XE6,0XFD,0XBD,0XF9,0XEF,0X5E,0XFF,0XFF,0XFF,0XFF,0XFF,0XDF,0XC6,0X3A,0XDE,0XDD,
0XCE,0X5A,0XEF,0X5D,0XFF,0XBF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,0XFF,
};

unsigned char c_chBmp_40x16[98] =  //SUN
{
	0x28,0x10,
	0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3F,0xF1,0x81,0x8F,0xFC,0x3F,
	0xF1,0x81,0x8F,0xFC,0x30,0x31,0x81,0x8C,0x0C,0x30,0x01,0x81,0x8C,0x0C,0x30,0x01,
	0x81,0x8C,0x0C,0x3F,0xF1,0x81,0x8C,0x0C,0x3F,0xF1,0x81,0x8C,0x0C,0x00,0x31,0x81,
	0x8C,0x0C,0x00,0x31,0x81,0x8C,0x0C,0x30,0x31,0x81,0x8C,0x0C,0x3F,0xF1,0xFF,0x8C,
	0x0C,0x3F,0xF1,0xFF,0x8C,0x0C,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};

unsigned char c_chSingal_8x16[18] = //mobie singal
{
	0x10,0x08,
	0xFE,0x02,0x92,0x0A,0x54,0x2A,0x38,0xAA,0x12,0xAA,0x12,0xAA,0x12,0xAA,0x12,0xAA
};

unsigned char c_chMsg_8x16[18] =  //message
{
	0x10,0x08,
	0x1F,0xF8,0x10,0x08,0x18,0x18,0x14,0x28,0x13,0xC8,0x10,0x08,0x10,0x08,0x1F,0xF8
};

unsigned char c_chBat_8x16[18] = //batery
{
	0x10,0x08,
	0x0F,0xFE,0x30,0x02,0x26,0xDA,0x26,0xDA,0x26,0xDA,0x26,0xDA,0x30,0x02,0x0F,0xFE
};

unsigned char c_chBluetooth_8x8[10] = // bluetooth
{
	0x08,0x08,
	0x18,0x54,0x32,0x1C,0x1C,0x32,0x54,0x18
};

unsigned char c_chGPRS_8x8[10] = //GPRS
{
	0x08,0x08,
	0xC3,0x99,0x24,0x20,0x2C,0x24,0x99,0xC3
};
unsigned char c_chAlarm_8x8[10] = //alram
{
	0x08,0x08,
	0xC3,0xBD,0x42,0x52,0x4E,0x42,0x3C,0xC3
};






