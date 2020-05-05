#pragma once

#include	<string>

extern		std::string		winTitle;

extern		float			winWidth;
extern		float			winHeight;

extern		bool			winFullscreen;
extern		bool			winFps;

#define		R_PATH			"Ressources\\"
#define		R_SPRITE(NAME)	R_PATH  "Sprites\\" NAME
#define		R_FONT(NAME)	R_PATH  "Fonts\\" NAME
#define		R_SOUND(NAME)	R_PATH	"Sounds\\" NAME

#define		C_PATH			"Configs\\"
#define		C_CONFIG(NAME)	C_PATH NAME

#define		M_CURSOR_L		"> "
#define		M_CURSOR_R		" <"

#define		F_LIMIT			(15)

#define		D_SPEED_X		(0.05f)
#define		D_SPEED_Y		(0.05f)

#define		B_WIDTH_RATIO	(2)
#define		B_HEIGHT_RATIO	(2)

#define		D_TIME			(3)

#define		S_SPEED			(20)

enum mod
{
	menu = 0,
	connection,
	multiplayer,
	play,
	setting,
	over,
	restart,
	quit
};