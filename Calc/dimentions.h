#pragma once

#define g_i_BUTTON_SIZE			 80
#define g_i_INTERVAL			 2
#define g_i_BUTTON_DOUBLE_SIZE   g_i_BUTTON_SIZE*2+g_i_INTERVAL
#define g_i_DISPLAY_WIDTH		 g_i_BUTTON_SIZE*5 + g_i_INTERVAL*4
#define g_i_DISPLAY_HEIGHT		 g_i_BUTTON_SIZE
#define g_i_START_X				 10
#define g_i_START_Y				 10
#define g_i_BUTTON_START_X		 g_i_START_X
#define g_i_BUTTON_START_Y		 g_i_START_Y + g_i_DISPLAY_HEIGHT + g_i_INTERVAL

#define BUTTON_SHIFT_X(n)		 g_i_BUTTON_START_X + (g_i_BUTTON_SIZE + g_i_INTERVAL)*n
#define BUTTON_SHIFT_Y(n)		 g_i_BUTTON_START_Y + (g_i_BUTTON_SIZE + g_i_INTERVAL)*(n)

#define g_i_WINDOW_WIDTH		 g_i_DISPLAY_WIDTH + g_i_START_X * 2 + 16
#define g_i_WINDOW_HEIGHT		 g_i_DISPLAY_HEIGHT + g_i_START_Y * 2 + (g_i_BUTTON_SIZE + g_i_INTERVAL) * 4 + 38


#define g_i_FONT_HEIGHT          (g_i_DISPLAY_HEIGHT - 2)
#define g_i_FONT_WIDTH			 (g_i_FONT_HEIGHT / 2)