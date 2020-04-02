/***************************************************************************
 *   Copyright (C) $2020$ by $Samuli Riihikoski$   *
 *   $samuli.riihi@gmail.com$   *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
/*********************************************************************
 1.  NAME
     $readtemp.c$ 
 2.  DESCRIPTION
     Read temps from file and draw them into screen using ncurses library
 3.  VERSIONS
       Original:
         $31.3.2020$ / $Samuli Riihikoski$
       Version history:
        31.3.2020
**********************************************************************/

/*-------------------------------------------------------------------*
*    HEADER FILES                                                    *
*--------------------------------------------------------------------*/

#include <ncurses.h>
#include <unistd.h> /* needed for usleep delay*/
#include <math.h>   /* needed for sin */
#include <stdio.h>
#include "Databank.h"

/*-------------------------------------------------------------------*
*    GLOBAL VARIABLES AND CONSTANTS                                  *
*--------------------------------------------------------------------*/
/* Control flags */

/* Global constants */
#define ZERO_LEVEL 1
#define X_AXIS_SIZE 100         // x axis range
#define Y_AXIS_SIZE 32          // y axis range
#define X_AXIS_RESOLUTION 10    // total length is 10x10=100

/*-------------------------------------------------------------------*
*    FUNCTION PROTOTYPES                                             *
*--------------------------------------------------------------------*/

void draw_axis(Databank *TempData);
void draw_temps(Databank *TempData);
int calc_y_bar(int index, Databank *TempData);

/*********************************************************************
*    MAIN PROGRAM                                                    *
**********************************************************************/

int main (void)
{
    Databank TempData;
    
    ImportData(&TempData);
    
    // NCURSES STARTS
    
    initscr ();	

    start_color ();
    init_pair (1, COLOR_WHITE, COLOR_BLUE);
    init_pair (2, COLOR_RED, COLOR_RED);
    bkgd(COLOR_PAIR(1));
    
    curs_set(0);
    
    draw_axis(&TempData);
    draw_temps(&TempData);

    refresh();
    getch ();
    
    endwin ();

    // NCURSES ENDS

} /* end of main */

/*********************************************************************
*    FUNCTIONS                                                       *
**********************************************************************/
/*********************************************************************
	F U N C T I O N    D E S C R I P T I O N
---------------------------------------------------------------------
 
 NAME:draw_axis

 DESCRIPTION: draw basic xy axis
	Input:
	Output: 
  Used global variables:
  Used global constants: AXIS_SIZE
 REMARKS when using this function:
*********************************************************************/

void draw_axis(Databank *TempData) {

    int tempsRange = TempData->tempsRange;
    int min = TempData->min;

    // Y-AXIS
    
    float u = 15.5;
    for (int i=0; i<32; ++i) {

        move(i, 0);
        printw("%.1f",u);
        u -= 0.5;

    }

    // X-AXIS

    for (int i=0;i<X_AXIS_RESOLUTION;i++) {

        for (int u=0;u<X_AXIS_RESOLUTION;u++) {

            move(Y_AXIS_SIZE, ((i*10)+u)+5);
            printw("%i",u);

        }

        move(Y_AXIS_SIZE+1, (i*10)+5);
        printw("%i",i);
    }

   
}

/*********************************************************************
	F U N C T I O N    D E S C R I P T I O N
---------------------------------------------------------------------
 
 NAME:draw_sin

 DESCRIPTION: Draws sin curve
	Input: None
	Output: None
  Used global variables:
  Used global constants: AXIS_SIZE, RESOLUTION
 REMARKS when using this function:
*********************************************************************/

void draw_temps(Databank *TempData) {


    for(int curr_x = 0; curr_x < X_AXIS_SIZE; curr_x++) {
        
        int y_bar = calc_y_bar(curr_x, TempData);
        attron(COLOR_PAIR(2));

        for(int i=y_bar; i<Y_AXIS_SIZE; i++) {

            move(i,curr_x+5);
            printw("O");
        }
        
        attroff(COLOR_PAIR(2));
        usleep(0);

    }


}

/*********************************************************************
	F U N C T I O N    D E S C R I P T I O N
---------------------------------------------------------------------
 
 NAME:scale_sin

 DESCRIPTION: gives values for drawing sin curve
	Input: value = current x axes position
	Output: current y position 
  Used global variables:
  Used global constants: AXIS_SIZE, 
 REMARKS when using this function:
*********************************************************************/

int calc_y_bar(int value, Databank *TempData) {

    int min = TempData->min;
    int max = TempData->max;
    float curr_temp = TempData->temps[value] / 5;
    int range = TempData->tempsRange;
    
    float relative;

    float curr_relative_min = curr_temp - min;
    relative = (curr_relative_min / range) * max;
    return (Y_AXIS_SIZE - 1) - ((int)curr_temp);
}
