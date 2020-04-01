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
     $sincurve.c$ 
 2.  DESCRIPTION
     Draw sine curve
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

/*-------------------------------------------------------------------*
*    GLOBAL VARIABLES AND CONSTANTS                                  *
*--------------------------------------------------------------------*/
/* Control flags */

/* Global constants */

#define AXIS_SIZE 40    // total range for x and y axis
#define PII 3.14        // 2*PII is 360 degrees
#define AMPLITUDE 10    // amplitude for sin curve

#define CURVE_RESOLUTION 0.1  // how accurate sin curve is calculated 
                        // 1 = low accurate
                        // 0.1 = normal accurate
                        // 0.01 = high accurate


/*-------------------------------------------------------------------*
*    FUNCTION PROTOTYPES                                             *
*--------------------------------------------------------------------*/

void draw_axis(void);
void draw_line(void);
void draw_sin(void);
int scale_sin(float value);

/*********************************************************************
*    MAIN PROGRAM                                                    *
**********************************************************************/

int main (void)
{

    initscr ();	

    start_color ();
    init_pair (1, COLOR_WHITE, COLOR_BLUE);
    bkgd (COLOR_PAIR (1));
    curs_set(0);

    draw_axis();
    draw_sin();

    refresh();
    getch ();
    
    endwin ();

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

void draw_axis() {

    int i;

    for (i=0; i<AXIS_SIZE; i++) {

        move((AXIS_SIZE/2),i);
        printw("*");
        move(i, (AXIS_SIZE/2));
        printw("*");

    }

    move((AXIS_SIZE/2),i);
    printw("**>");
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

void draw_sin() {

    for(float curr_x = 0; curr_x <= AXIS_SIZE; curr_x += CURVE_RESOLUTION) {

        move(scale_sin(curr_x),curr_x+1);
        printw("O",curr_x);
       
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
  Used global constants: AXIS_SIZE, PII, AMPLITUDE
 REMARKS when using this function:
*********************************************************************/

int scale_sin(float value) {

    value = (value/AXIS_SIZE)*(2*PII)-PII;
    int result = (int)((-sin(value)*AMPLITUDE)+AXIS_SIZE/2);
    
    return result;
}
