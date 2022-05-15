///////////////////////////////////////
/// 640x480 version! 16-bit color
/// This code will segfault the original
/// DE1 computer
/// compile with
/// gcc graphics_video_16bit.c -o gr -O2 -lm
///
///////////////////////////////////////
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <sys/mman.h>
#include <sys/time.h> 
#include <math.h>
//#include <conio.h>
// #include <iostream>
//#include "address_map_arm_brl4.h"

// video display
#define SDRAM_BASE            0xC0000000
#define SDRAM_END             0xC3FFFFFF
#define SDRAM_SPAN			  0x04000000
// characters
#define FPGA_CHAR_BASE        0xC9000000 
#define FPGA_CHAR_END         0xC9001FFF
#define FPGA_CHAR_SPAN        0x00002000
/* Cyclone V FPGA devices */
#define HW_REGS_BASE          0xff200000
//#define HW_REGS_SPAN        0x00200000 
#define HW_REGS_SPAN          0x00005000 


// lw bus; PIO
#define FPGA_LW_BASE 	0xff200000
#define FPGA_LW_SPAN	0x00001000

//arrow keys

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 7

// graphics primitives
void VGA_text (int, int, char *);
void VGA_text_clear();
void VGA_box (int, int, int, int, short);
void VGA_rect (int, int, int, int, short);
void VGA_line(int, int, int, int, short) ;
void VGA_Vline(int, int, int, short) ;
void VGA_Hline(int, int, int, short) ;
void VGA_disc (int, int, int, short);
void VGA_circle (int, int, int, int);
// 16-bit primary colors
#define red  (0+(0<<5)+(31<<11))
#define dark_red (0+(0<<5)+(15<<11))
#define green (0+(63<<5)+(0<<11))
#define dark_green (0+(31<<5)+(0<<11))
#define blue (31+(0<<5)+(0<<11))
#define dark_blue (15+(0<<5)+(0<<11))
#define yellow (0+(63<<5)+(31<<11))
#define cyan (31+(63<<5)+(0<<11))
#define magenta (31+(0<<5)+(31<<11))
#define black (0x0000)
#define gray (15+(31<<5)+(51<<11))
#define white (0xffff)
int colors[] = {red, dark_red, green, dark_green, blue, dark_blue, 
		yellow, cyan, magenta, gray, black, white};
int speedColorList[] = {cyan,green,yellow,red,gray,white};



// pixel macro
#define VGA_PIXEL(x,y,color) do{\
	int  *pixel_ptr ;\
	pixel_ptr = (int*)((char *)vga_pixel_ptr + (((y)*640+(x))<<1)) ; \
	*(short *)pixel_ptr = (color);\
} while(0)

// the light weight buss base
void *h2p_lw_virtual_base;

// pixel buffer
volatile unsigned int * vga_pixel_ptr = NULL ;
void *vga_pixel_virtual_base;

// character buffer
volatile unsigned int * vga_char_ptr = NULL ;
void *vga_char_virtual_base;

// /dev/mem file id
int fd;

// measure time
struct timeval t1, t2;
double elapsedTime;

double shift17 =  0;
double shift_m_17 = 0;


double shift5 =  0;
double shift_m_22 = 0;

void *h2p_lw_virtual_base;

// HPS_to_FPGA FIFO status address = 0
// generate pointers to memory addresses correspoding to PIO ports made in Qsys 


volatile signed int * hw__sdram_ptr = NULL;

void *vga_char_virtual_base;
// pixel buffer
void *vga_pixel_virtual_base;

//pio for lj
#define NUMOFSOLVERS 10

// //solver 0
// volatile signed int * lw__pio_write_ptr_i_x[NUMOFSOLVERS] = {NULL};
// volatile signed int * lw__pio_write_ptr_i_y[NUMOFSOLVERS] = {NULL};
// volatile signed int * lw__pio_write_ptr_j_x[NUMOFSOLVERS] = {NULL};
// volatile signed int * lw__pio_write_ptr_j_y[NUMOFSOLVERS] = {NULL};
// volatile signed int * lw__pio_write_ptr_fx[NUMOFSOLVERS] = {NULL};
// volatile signed int * lw__pio_write_ptr_fy[NUMOFSOLVERS] = {NULL};


//solver1
volatile signed int * lw__pio_write_ptr_i_y = NULL;
volatile signed int * lw__pio_write_ptr_j_x = NULL;
volatile signed int * lw__pio_write_ptr_i_x = NULL;
volatile signed int * lw__pio_write_ptr_j_y = NULL;
volatile signed int * lw__pio_write_ptr_fx = NULL;
volatile signed int * lw__pio_write_ptr_fy = NULL;


#define FPGA_PIO_OFFSET_I_X	0x130
#define FPGA_PIO_OFFSET_I_Y	0x140
#define FPGA_PIO_OFFSET_J_X	0x150
#define FPGA_PIO_OFFSET_J_Y	0x160
#define FPGA_PIO_OFFSET_FX	0x170
#define FPGA_PIO_OFFSET_FY	0x180


//solver1
volatile signed int * lw__pio_write_ptr_i_x_1 = NULL;
volatile signed int * lw__pio_write_ptr_i_y_1 = NULL;
volatile signed int * lw__pio_write_ptr_j_x_1 = NULL;
volatile signed int * lw__pio_write_ptr_j_y_1 = NULL;
volatile signed int * lw__pio_write_ptr_fx_1 = NULL;
volatile signed int * lw__pio_write_ptr_fy_1 = NULL;


#define FPGA_PIO_OFFSET_I_X_1	0x190
#define FPGA_PIO_OFFSET_I_Y_1	0x200
#define FPGA_PIO_OFFSET_J_X_1	0x210
#define FPGA_PIO_OFFSET_J_Y_1	0x220
#define FPGA_PIO_OFFSET_FX_1	0x230
#define FPGA_PIO_OFFSET_FY_1	0x240


//solver2
volatile signed int * lw__pio_write_ptr_i_x_2 = NULL;
volatile signed int * lw__pio_write_ptr_i_y_2 = NULL;
volatile signed int * lw__pio_write_ptr_j_x_2 = NULL;
volatile signed int * lw__pio_write_ptr_j_y_2 = NULL;
volatile signed int * lw__pio_write_ptr_fx_2 = NULL;
volatile signed int * lw__pio_write_ptr_fy_2 = NULL;


#define FPGA_PIO_OFFSET_I_X_2	0x250
#define FPGA_PIO_OFFSET_I_Y_2	0x260
#define FPGA_PIO_OFFSET_J_X_2	0x270
#define FPGA_PIO_OFFSET_J_Y_2	0x280
#define FPGA_PIO_OFFSET_FX_2	0x290
#define FPGA_PIO_OFFSET_FY_2	0x300


//solver3
volatile signed int * lw__pio_write_ptr_i_x_3 = NULL;
volatile signed int * lw__pio_write_ptr_i_y_3 = NULL;
volatile signed int * lw__pio_write_ptr_j_x_3 = NULL;
volatile signed int * lw__pio_write_ptr_j_y_3 = NULL;
volatile signed int * lw__pio_write_ptr_fx_3 = NULL;
volatile signed int * lw__pio_write_ptr_fy_3 = NULL;


#define FPGA_PIO_OFFSET_I_X_3	0x310
#define FPGA_PIO_OFFSET_I_Y_3	0x320
#define FPGA_PIO_OFFSET_J_X_3	0x330
#define FPGA_PIO_OFFSET_J_Y_3	0x340
#define FPGA_PIO_OFFSET_FX_3	0x350
#define FPGA_PIO_OFFSET_FY_3	0x360


//solver4
volatile signed int * lw__pio_write_ptr_i_x_4 = NULL;
volatile signed int * lw__pio_write_ptr_i_y_4 = NULL;
volatile signed int * lw__pio_write_ptr_j_x_4 = NULL;
volatile signed int * lw__pio_write_ptr_j_y_4 = NULL;
volatile signed int * lw__pio_write_ptr_fx_4 = NULL;
volatile signed int * lw__pio_write_ptr_fy_4 = NULL;


#define FPGA_PIO_OFFSET_I_X_4	0x370
#define FPGA_PIO_OFFSET_I_Y_4	0x380
#define FPGA_PIO_OFFSET_J_X_4	0x390
#define FPGA_PIO_OFFSET_J_Y_4	0x400
#define FPGA_PIO_OFFSET_FX_4	0x410
#define FPGA_PIO_OFFSET_FY_4	0x420



//solver5
volatile signed int * lw__pio_write_ptr_i_x_5 = NULL;
volatile signed int * lw__pio_write_ptr_i_y_5 = NULL;
volatile signed int * lw__pio_write_ptr_j_x_5 = NULL;
volatile signed int * lw__pio_write_ptr_j_y_5 = NULL;
volatile signed int * lw__pio_write_ptr_fx_5 = NULL;
volatile signed int * lw__pio_write_ptr_fy_5 = NULL;


#define FPGA_PIO_OFFSET_I_X_5	0x430
#define FPGA_PIO_OFFSET_I_Y_5	0x440
#define FPGA_PIO_OFFSET_J_X_5	0x450
#define FPGA_PIO_OFFSET_J_Y_5	0x460
#define FPGA_PIO_OFFSET_FX_5	0x470
#define FPGA_PIO_OFFSET_FY_5	0x480


//solver6
volatile signed int * lw__pio_write_ptr_i_x_6 = NULL;
volatile signed int * lw__pio_write_ptr_i_y_6 = NULL;
volatile signed int * lw__pio_write_ptr_j_x_6 = NULL;
volatile signed int * lw__pio_write_ptr_j_y_6 = NULL;
volatile signed int * lw__pio_write_ptr_fx_6 = NULL;
volatile signed int * lw__pio_write_ptr_fy_6 = NULL;


#define FPGA_PIO_OFFSET_I_X_6	0x490
#define FPGA_PIO_OFFSET_I_Y_6	0x500
#define FPGA_PIO_OFFSET_J_X_6	0x510
#define FPGA_PIO_OFFSET_J_Y_6	0x520
#define FPGA_PIO_OFFSET_FX_6	0x530
#define FPGA_PIO_OFFSET_FY_6	0x540


//solver7
volatile signed int * lw__pio_write_ptr_i_x_7 = NULL;
volatile signed int * lw__pio_write_ptr_i_y_7 = NULL;
volatile signed int * lw__pio_write_ptr_j_x_7 = NULL;
volatile signed int * lw__pio_write_ptr_j_y_7 = NULL;
volatile signed int * lw__pio_write_ptr_fx_7 = NULL;
volatile signed int * lw__pio_write_ptr_fy_7 = NULL;


#define FPGA_PIO_OFFSET_I_X_7	0x550
#define FPGA_PIO_OFFSET_I_Y_7	0x560
#define FPGA_PIO_OFFSET_J_X_7	0x570
#define FPGA_PIO_OFFSET_J_Y_7	0x580
#define FPGA_PIO_OFFSET_FX_7	0x590
#define FPGA_PIO_OFFSET_FY_7	0x600


//solver8
volatile signed int * lw__pio_write_ptr_i_x_8 = NULL;
volatile signed int * lw__pio_write_ptr_i_y_8 = NULL;
volatile signed int * lw__pio_write_ptr_j_x_8 = NULL;
volatile signed int * lw__pio_write_ptr_j_y_8 = NULL;
volatile signed int * lw__pio_write_ptr_fx_8 = NULL;
volatile signed int * lw__pio_write_ptr_fy_8 = NULL;


#define FPGA_PIO_OFFSET_I_X_8	0x610
#define FPGA_PIO_OFFSET_I_Y_8	0x620
#define FPGA_PIO_OFFSET_J_X_8	0x630
#define FPGA_PIO_OFFSET_J_Y_8	0x640
#define FPGA_PIO_OFFSET_FX_8	0x650
#define FPGA_PIO_OFFSET_FY_8	0x660



//solver7
volatile signed int * lw__pio_write_ptr_i_x_9 = NULL;
volatile signed int * lw__pio_write_ptr_i_y_9 = NULL;
volatile signed int * lw__pio_write_ptr_j_x_9 = NULL;
volatile signed int * lw__pio_write_ptr_j_y_9 = NULL;
volatile signed int * lw__pio_write_ptr_fx_9 = NULL;
volatile signed int * lw__pio_write_ptr_fy_9 = NULL;


#define FPGA_PIO_OFFSET_I_X_9	0x670
#define FPGA_PIO_OFFSET_I_Y_9	0x680
#define FPGA_PIO_OFFSET_J_X_9	0x690
#define FPGA_PIO_OFFSET_J_Y_9	0x700
#define FPGA_PIO_OFFSET_FX_9	0x710
#define FPGA_PIO_OFFSET_FY_9	0x720
int fd;	


#define numOfPart 500
#define maxBonds 2000
int partMass = 1;
float accGrav = -10;

// particle 
// 0 => X ; 1 => Y

int x = 0;
int y = 1;

double part_pos[numOfPart][2] = {};
double part_pos_prev[numOfPart][2] = {};
double part_vel[numOfPart][2] = {};
double part_acc[numOfPart][2] = {};
int part_color[numOfPart] = {};

int bondList[maxBonds*2] = {};

int neighbourIndex[numOfPart] = {};


double xBetweenParticles[numOfPart][numOfPart];
double yBetweenParticles[numOfPart][numOfPart];

double xBetweenParticles_2[numOfPart][numOfPart];
double yBetweenParticles_2[numOfPart][numOfPart];

int NumOfPartOnScreen = 0;

int sigma,epsilon;
float timeStep = 0.01;
float numOfStepsPerFrame = 1;
int timeDelay = 10000;

float energyLossCeoff = 0.25;

int cutoffRadius_2 = 256;

int sizeOfPartOnScreen = 2	;
double radiusOfPart_m = 0.25;

double sizeOfPixel_m = 1;

int boxWidth = 290;
int boxHeight = 250;
int wallBorderX = 50;
int wallBorderY = 10;




int bondCount = 0;

void updateVelocity(int partIndex, int coord){

	float new_vel;
	new_vel= part_acc[partIndex][coord] * timeStep + part_vel[partIndex][coord];
	part_vel[partIndex][coord] = new_vel;
	
}

void updateColor(int partIndex){
	float speedLimit = 25;	
	int speed = sqrt(part_vel[partIndex][x]*part_vel[partIndex][x] + part_vel[partIndex][y]*part_vel[partIndex][y]);

	if (speed > speedLimit) {
		part_color[partIndex] = speedColorList[6-1];
	} else {
		part_color[partIndex] = speedColorList[(int)(speed*6/speedLimit)];
	}

}

void drawParticles(int partIndex){
	updateColor(partIndex);
 	VGA_disc((int)part_pos_prev[partIndex][x],(int)part_pos_prev[partIndex][y],sizeOfPartOnScreen,0x00);
    VGA_disc((int)part_pos[partIndex][x],(int)part_pos[partIndex][y],sizeOfPartOnScreen,part_color[partIndex]);
}




void computeAccelerations(){
	double dx, dy, dx2, dy2, r, rSquared, rSquaredInv, attract, repel, fOverR;
	double fx, fy,fx_1, fy_1,fx_2, fy_2,fx_3, fy_3;
	double fx_4, fy_4,fx_5, fy_5,fx_6, fy_6,fx_7, fy_7;
	double fx_8, fy_8,fx_9, fy_9;
	double forceCutoff = 15.0;						// distance beyond which we set force=0
	double forceCutoff2 = forceCutoff*forceCutoff;
	double pEatCutoff = 4 * (pow(forceCutoff,-12) - pow(forceCutoff,-6));
	//double g = Number(getGravity());
	double wallStiffness = 200;						// spring constant for bouncing off walls
	double wallForce = 0.0;
	double potentialE = 0.0;


	// int boxWidth = 290;
	// int boxHeight = 250; 
        // first check for bounces off walls:
	int i;
	
	for (i=0; i<NumOfPartOnScreen; i++) {
		if (part_pos[i][x] < wallBorderX) {
			part_acc[i][x] = wallStiffness * (wallBorderX - part_pos[i][x]);
			wallForce += part_acc[i][x];
			potentialE += wallBorderX * wallStiffness * (wallBorderX-part_pos[i][x]) * (wallBorderX-part_pos[i][x]);
		} else{
			if (part_pos[i][x] > (boxWidth - wallBorderX)) {
				part_acc[i][x] = wallStiffness * (boxWidth - wallBorderX - part_pos[i][x]);
				wallForce -= part_acc[i][x];
				potentialE += wallBorderX * wallStiffness * (boxWidth-wallBorderX-part_pos[i][x]) * (boxWidth-wallBorderX-part_pos[i][x]);
			} else{
				part_acc[i][x] = 0.0;
			}	
		}
		
		if (part_pos[i][y] < wallBorderY) {
			part_acc[i][y] = (wallStiffness * (wallBorderY - part_pos[i][y]));

			wallForce += part_acc[i][y];
			potentialE += wallBorderY * wallStiffness * (wallBorderY-part_pos[i][y]) * (wallBorderY-part_pos[i][y]);
		} else{
			if (part_pos[i][y] > (boxHeight - wallBorderY)) {
				part_acc[i][y] = (wallStiffness * (boxHeight - wallBorderY - part_pos[i][y]));
				
				wallForce -= part_acc[i][y];
				potentialE += wallBorderY * wallStiffness * (boxHeight-wallBorderY-part_pos[i][y]) * (boxHeight-wallBorderY-part_pos[i][y]);
			} else{
				part_acc[i][y] = 0;
				
			}
		}

		part_acc[i][y] -= accGrav;				// add gravity if any

	}

	for ( i=0; i<NumOfPartOnScreen; i++) {	
		int j;		// simple double-loop over atoms for small system
		for (j=0; j<i; j=j+NUMOFSOLVERS) {


            *(lw__pio_write_ptr_i_x) = (signed int) (part_pos[i][x] * shift17);
            *(lw__pio_write_ptr_i_y) = (signed int) (part_pos[i][y] * shift17);
            *(lw__pio_write_ptr_j_x) = (signed int) (part_pos[j][x] * shift17);
            *(lw__pio_write_ptr_j_y) = (signed int) (part_pos[j][y] * shift17);

			




            signed int fx_int = *(lw__pio_write_ptr_fx) ;
            signed int fy_int = *(lw__pio_write_ptr_fy) ;



			fx = ((float)fx_int) *  shift_m_17;
			fy = ((float)fy_int) *  shift_m_17;


            part_acc[i][x] += fx; // add this force on to i's acceleration (m = 1)
            part_acc[i][y] += fy;
            part_acc[j][x] -= fx;  // Newton's 3rd law
            part_acc[j][y] -= fy;


			int j1 = j+1;

			if(j1<i){


				*(lw__pio_write_ptr_i_x_1) = (signed int) (part_pos[i][x] * shift17);
				*(lw__pio_write_ptr_i_y_1) = (signed int) (part_pos[i][y] * shift17);
				*(lw__pio_write_ptr_j_x_1) = (signed int) (part_pos[j1][x] * shift17);
				*(lw__pio_write_ptr_j_y_1) = (signed int) (part_pos[j1][y] * shift17);

				signed int fx_int_1 = *(lw__pio_write_ptr_fx_1) ;
				signed int fy_int_1 = *(lw__pio_write_ptr_fy_1) ;

				fx_1 = ((float)fx_int_1) *  shift_m_17;
				fy_1 = ((float)fy_int_1) *  shift_m_17;

				part_acc[i][x] += fx_1; // add this force on to i's acceleration (m = 1)
            	part_acc[i][y] += fy_1;
            	part_acc[j1][x] -= fx_1;  // Newton's 3rd law
            	part_acc[j1][y] -= fy_1;



			}

			int j2 = j+2;

			if(j2<i){

				*(lw__pio_write_ptr_i_x_2) = (signed int) (part_pos[i][x] * shift17);
				*(lw__pio_write_ptr_i_y_2) = (signed int) (part_pos[i][y] * shift17);
				*(lw__pio_write_ptr_j_x_2) = (signed int) (part_pos[j2][x] * shift17);
				*(lw__pio_write_ptr_j_y_2) = (signed int) (part_pos[j2][y] * shift17);

				signed int fx_int_2 = *(lw__pio_write_ptr_fx_2) ;
				signed int fy_int_2 = *(lw__pio_write_ptr_fy_2) ;

				fx_2 = ((float)fx_int_2) *  shift_m_17;
				fy_2 = ((float)fy_int_2) *  shift_m_17;

				part_acc[i][x] += fx_2; // add this force on to i's acceleration (m = 1)
            	part_acc[i][y] += fy_2;
            	part_acc[j2][x] -= fx_2;  // Newton's 3rd law
            	part_acc[j2][y] -= fy_2;



			}


			int j3 = j+3;

			if(j3<i){


				*(lw__pio_write_ptr_i_x_3) = (signed int) (part_pos[i][x] * shift17);
				*(lw__pio_write_ptr_i_y_3) = (signed int) (part_pos[i][y] * shift17);
				*(lw__pio_write_ptr_j_x_3) = (signed int) (part_pos[j3][x] * shift17);
				*(lw__pio_write_ptr_j_y_3) = (signed int) (part_pos[j3][y] * shift17);

				signed int fx_int_3 = *(lw__pio_write_ptr_fx_3) ;
				signed int fy_int_3 = *(lw__pio_write_ptr_fy_3) ;

				fx_3 = ((float)fx_int_3) *  shift_m_17;
				fy_3 = ((float)fy_int_3) *  shift_m_17;

				part_acc[i][x] += fx_3; // add this force on to i's acceleration (m = 1)
            	part_acc[i][y] += fy_3;
            	part_acc[j3][x] -= fx_3;  // Newton's 3rd law
            	part_acc[j3][y] -= fy_3;



			}



			int j4 = j+4;

			if(j4<i){

				*(lw__pio_write_ptr_i_x_4) = (signed int) (part_pos[i][x] * shift17);
				*(lw__pio_write_ptr_i_y_4) = (signed int) (part_pos[i][y] * shift17);
				*(lw__pio_write_ptr_j_x_4) = (signed int) (part_pos[j4][x] * shift17);
				*(lw__pio_write_ptr_j_y_4) = (signed int) (part_pos[j4][y] * shift17);

				signed int fx_int_4 = *(lw__pio_write_ptr_fx_4) ;
				signed int fy_int_4 = *(lw__pio_write_ptr_fy_4) ;

				fx_4 = ((float)fx_int_4) *  shift_m_17;
				fy_4 = ((float)fy_int_4) *  shift_m_17;

				part_acc[i][x] += fx_4; // add this force on to i's acceleration (m = 1)
            	part_acc[i][y] += fy_4;
            	part_acc[j4][x] -= fx_4;  // Newton's 4rd law
            	part_acc[j4][y] -= fy_4;



			}



			int j5 = j+5;

			if(j5<i){

				*(lw__pio_write_ptr_i_x_5) = (signed int) (part_pos[i][x] * shift17);
				*(lw__pio_write_ptr_i_y_5) = (signed int) (part_pos[i][y] * shift17);
				*(lw__pio_write_ptr_j_x_5) = (signed int) (part_pos[j5][x] * shift17);
				*(lw__pio_write_ptr_j_y_5) = (signed int) (part_pos[j5][y] * shift17);

				signed int fx_int_5 = *(lw__pio_write_ptr_fx_5) ;
				signed int fy_int_5 = *(lw__pio_write_ptr_fy_5) ;

				fx_5 = ((float)fx_int_5) *  shift_m_17;
				fy_5 = ((float)fy_int_5) *  shift_m_17;

				part_acc[i][x] += fx_5; // add this force on to i's acceleration (m = 1)
            	part_acc[i][y] += fy_5;
            	part_acc[j5][x] -= fx_5;  // Newton's 5rd law
            	part_acc[j5][y] -= fy_5;



			}


			int j6 = j+6;

			if(j6<i){

				*(lw__pio_write_ptr_i_x_6) = (signed int) (part_pos[i][x] * shift17);
				*(lw__pio_write_ptr_i_y_6) = (signed int) (part_pos[i][y] * shift17);
				*(lw__pio_write_ptr_j_x_6) = (signed int) (part_pos[j6][x] * shift17);
				*(lw__pio_write_ptr_j_y_6) = (signed int) (part_pos[j6][y] * shift17);

				signed int fx_int_6 = *(lw__pio_write_ptr_fx_6) ;
				signed int fy_int_6 = *(lw__pio_write_ptr_fy_6) ;

				fx_6 = ((float)fx_int_6) *  shift_m_17;
				fy_6 = ((float)fy_int_6) *  shift_m_17;

				part_acc[i][x] += fx_6; // add this force on to i's acceleration (m = 1)
            	part_acc[i][y] += fy_6;
            	part_acc[j6][x] -= fx_6;  // Newton's 6rd law
            	part_acc[j6][y] -= fy_6;



			}
			int j7 = j+7;

			if(j7<i){



				*(lw__pio_write_ptr_i_x_7) = (signed int) (part_pos[i][x] * shift17);
				*(lw__pio_write_ptr_i_y_7) = (signed int) (part_pos[i][y] * shift17);
				*(lw__pio_write_ptr_j_x_7) = (signed int) (part_pos[j7][x] * shift17);
				*(lw__pio_write_ptr_j_y_7) = (signed int) (part_pos[j7][y] * shift17);

				signed int fx_int_7 = *(lw__pio_write_ptr_fx_7) ;
				signed int fy_int_7 = *(lw__pio_write_ptr_fy_7) ;

				fx_7 = ((float)fx_int_7) *  shift_m_17;
				fy_7 = ((float)fy_int_7) *  shift_m_17;

				part_acc[i][x] += fx_7; // add this force on to i's acceleration (m = 1)
            	part_acc[i][y] += fy_7;
            	part_acc[j7][x] -= fx_7;  // Newton's 7rd law
            	part_acc[j7][y] -= fy_7;



			}
			int j8 = j+8;

			if(j8<i){



				*(lw__pio_write_ptr_i_x_8) = (signed int) (part_pos[i][x] * shift17);
				*(lw__pio_write_ptr_i_y_8) = (signed int) (part_pos[i][y] * shift17);
				*(lw__pio_write_ptr_j_x_8) = (signed int) (part_pos[j8][x] * shift17);
				*(lw__pio_write_ptr_j_y_8) = (signed int) (part_pos[j8][y] * shift17);

				signed int fx_int_8 = *(lw__pio_write_ptr_fx_8) ;
				signed int fy_int_8 = *(lw__pio_write_ptr_fy_8) ;

				fx_8 = ((float)fx_int_8) *  shift_m_17;
				fy_8 = ((float)fy_int_8) *  shift_m_17;

				part_acc[i][x] += fx_8; // add this force on to i's acceleration (m = 1)
            	part_acc[i][y] += fy_8;
            	part_acc[j8][x] -= fx_8;  // Newton's 8rd law
            	part_acc[j8][y] -= fy_8;



			}
			int j9 = j+9;

			if(j9<i){


				*(lw__pio_write_ptr_i_x_9) = (signed int) (part_pos[i][x] * shift17);
				*(lw__pio_write_ptr_i_y_9) = (signed int) (part_pos[i][y] * shift17);
				*(lw__pio_write_ptr_j_x_9) = (signed int) (part_pos[j9][x] * shift17);
				*(lw__pio_write_ptr_j_y_9) = (signed int) (part_pos[j9][y] * shift17);

				signed int fx_int_9 = *(lw__pio_write_ptr_fx_9) ;
				signed int fy_int_9 = *(lw__pio_write_ptr_fy_9) ;

				fx_9 = ((float)fx_int_9) *  shift_m_17;
				fy_9 = ((float)fy_int_9) *  shift_m_17;

				part_acc[i][x] += fx_9; // add this force on to i's acceleration (m = 1)
            	part_acc[i][y] += fy_9;
            	part_acc[j9][x] -= fx_9;  // Newton's 9rd law
            	part_acc[j9][y] -= fy_9;



			}

			



			

			// int solverNum;
			// for(solverNum=0;solverNum<NUMOFSOLVERS;solverNum++){
			// 	int j_idx = j+solverNum;

			// 	if(j_idx<i){

			// 		// dx = part_pos[i][x] - part_pos[j_idx][x];
			// 		// dy = part_pos[i][y] - part_pos[j_idx][y];

			// 		// double fx_elas = 64 * dx;
			// 		// double fy_elas = 64 * dy;

			// 		// if (pow(dx,2)+pow(dy,2) < 25) {

			// 		// 	part_acc[i][x] -= fx_elas;  
			// 		// 	part_acc[i][y] -= fy_elas;
			// 		// 	part_acc[j_idx][x] += fx_elas;  
			// 		// 	part_acc[j_idx][y] += fy_elas;

			// 		// }


			// 		*(lw__pio_write_ptr_i_x[solverNum]) = (signed int) (part_pos[i][x] * shift17);
			// 		*(lw__pio_write_ptr_i_y[solverNum]) = (signed int) (part_pos[i][y] * shift17);
			// 		*(lw__pio_write_ptr_j_x[solverNum]) = (signed int) (part_pos[j_idx][x] * shift17);
			// 		*(lw__pio_write_ptr_j_y[solverNum]) = (signed int) (part_pos[j_idx][y] * shift17);




			// 		signed int fx_int = *(lw__pio_write_ptr_fx[solverNum]) ;
			// 		signed int fy_int = *(lw__pio_write_ptr_fy[solverNum]) ;



			// 		fx = ((float)fx_int) *  shift_m_17;
			// 		fy = ((float)fy_int) *  shift_m_17;

					
			// 		part_acc[i][x] += fx; // add this force on to i's acceleration (m = 1)
			// 		part_acc[i][y] += fy;
			// 		part_acc[j_idx][x] -= fx;  // Newton's 3rd law
			// 		part_acc[j_idx][y] -= fy;
			// 	}
			// }


		}
	}

}

void doStep(int currStep){
	//createOrReleaseBond();
	float dt = timeStep;
	float halfdt = 0.5 * dt;
	float halfdtsquared = halfdt*dt;
	int i;
	for ( i=0; i<NumOfPartOnScreen; i++) {
		if(currStep==0){
			part_pos_prev[i][x] = part_pos[i][x];
			part_pos_prev[i][y] = part_pos[i][y];
		}
		part_pos[i][x] += part_vel[i][x]*dt + part_acc[i][x]*halfdtsquared;
		part_pos[i][y] += part_vel[i][y]*dt + part_acc[i][y]*halfdtsquared;
		part_vel[i][x] += part_acc[i][x]*halfdt;
		part_pos[i][y] += part_acc[i][y]*halfdt;
	}
	computeAccelerations();
	for (i=0; i<NumOfPartOnScreen; i++) {
		part_vel[i][x] += part_acc[i][x]*halfdt;
		part_vel[i][y] += part_acc[i][y]*halfdt;
	}

}
void simulate(){
	
	VGA_rect(wallBorderX-10,wallBorderY-10,boxWidth-(wallBorderX-10),boxHeight-(wallBorderY-10),white);

	int i;
	for ( i = 0; i<numOfStepsPerFrame; i++){
		doStep(i);
	}
	//TODO: draw particles to screen
	for ( i = 0; i<NumOfPartOnScreen; i++){
		drawParticles(i);
	}
	

}

void draw_txt(){
	char numstring[50];

	VGA_text_clear();
	//double time = ((double)cycle_count/freq) *1000;//ms
	sprintf(numstring, "         Num of particles = %d   ", NumOfPartOnScreen);
	VGA_text (1, 56, numstring);
}

void* simulate_thread(void* p)
{   
    while(1){
		simulate();


		//usleep(((numOfPart)-NumOfPartOnScreen)*5);
	}
}



void changevelocity(int factor, int sign){
	int i;
	for ( i=0; i<NumOfPartOnScreen; i++) {

		if (sign == 1) {

			if (part_vel[i][x] >= 0) {
				part_vel[i][x] = part_vel[i][x] + (rand() % factor);
			} else {
				part_vel[i][x] = part_vel[i][x] - (rand() % factor);
			}

			if (part_vel[i][y] >= 0) {
				part_vel[i][y] = part_vel[i][y] + (rand() % factor);
			} else {
				part_vel[i][y] = part_vel[i][y] - (rand() % factor);
			}




		} else {

			if (part_vel[i][x] >= 0) {
				part_vel[i][x] = part_vel[i][x] - (rand() %  factor);
			} else {
				part_vel[i][x] = part_vel[i][x] + (rand() %  factor);
			}

			if (part_vel[i][y] >= 0) {
				part_vel[i][y] = part_vel[i][y] - (rand() %  factor);
			} else {
				part_vel[i][y] = part_vel[i][y] + (rand() %  factor);
			}

			
			// part_vel[i][x] = part_vel[i][x] + (part_vel[i][x]*(rand() % factor));
			// part_vel[i][y] = part_vel[i][y] + (part_vel[i][y]*(rand() % factor));

		}
		
	}
}

void scaleBox(int change){
	//VGA_rect(wallBorderX-10,wallBorderY-10,boxWidth-(wallBorderX-10),boxHeight-(wallBorderY-10),black);
	if(boxHeight+change <= 250){
		boxWidth = boxWidth+(int)((double)change*1.16);
		boxHeight = boxHeight+change;
		wallBorderX = 50;
		wallBorderY = 10;

		int i;
		for ( i=0; i<NumOfPartOnScreen; i++) {
			part_pos[i][x] = part_pos[i][x]+(int)((double)change*1.16);
			part_pos[i][y] = part_pos[i][y]+change;
		}
	}
}

void toggleGrav() {
	if (accGrav == -10) {
		accGrav = 0;
	} else {
		accGrav = -10;
	}
}


void* ux(void* p)
{   
    while(1){
		char in;
		scanf("%c", &in);
	

		if(in=='w'){ ///speed up
			changevelocity(20,1);
		}
		else if(in=='s'){//slow down
			changevelocity(20,-1);
		}
		else if(in=='a'){//decrease box
			scaleBox(-10);
			VGA_box (0, 0, 639, 479, black);
		}
		else if(in=='d'){//increase box
			scaleBox(10);
			VGA_box (0, 0, 639, 479, black);
		}
		else if(in=='c'){//clear screen
			VGA_box (0, 0, 639, 479, black);
		}
		else if(in=='g'){//clear screen
			toggleGrav();
		}
	}

}
	
int main(void)
{
  	shift17 =  pow(2,17);
    shift_m_17 = pow(2,-17);

	shift5 =  pow(2,5);
    shift_m_22 = pow(2,-22);
	// === need to mmap: =======================
	// FPGA_CHAR_BASE
	// FPGA_ONCHIP_BASE      
	// HW_REGS_BASE        
  
	// === get FPGA addresses ==================
    // Open /dev/mem
	if( ( fd = open( "/dev/mem", ( O_RDWR | O_SYNC ) ) ) == -1 ) 	{
		printf( "ERROR: could not open \"/dev/mem\"...\n" );
		return( 1 );
	}
    
    // get virtual addr that maps to physical
	h2p_lw_virtual_base = mmap( NULL, HW_REGS_SPAN, ( PROT_READ | PROT_WRITE ), MAP_SHARED, fd, HW_REGS_BASE );	
	if( h2p_lw_virtual_base == MAP_FAILED ) {
		printf( "ERROR: mmap1() failed...\n" );
		close( fd );
		return(1);
	}
    

	// === get VGA char addr =====================
	// get virtual addr that maps to physical
	vga_char_virtual_base = mmap( NULL, FPGA_CHAR_SPAN, ( 	PROT_READ | PROT_WRITE ), MAP_SHARED, fd, FPGA_CHAR_BASE );	
	if( vga_char_virtual_base == MAP_FAILED ) {
		printf( "ERROR: mmap2() failed...\n" );
		close( fd );
		return(1);
	}
    
    // Get the address that maps to the FPGA LED control 
	vga_char_ptr =(unsigned int *)(vga_char_virtual_base);

	// === get VGA pixel addr ====================
	// get virtual addr that maps to physical
	vga_pixel_virtual_base = mmap( NULL, SDRAM_SPAN, ( PROT_READ | PROT_WRITE ), MAP_SHARED, fd, SDRAM_BASE);	
	if( vga_pixel_virtual_base == MAP_FAILED ) {
		printf( "ERROR: mmap3() failed...\n" );
		close( fd );
		return(1);
	}
    
    // Get the address that maps to the FPGA pixel buffer
	vga_pixel_ptr =(unsigned int *)(vga_pixel_virtual_base);

    
	///PIO for lj

	// printf("here");
	// int solverNum;
	// for(solverNum=0;solverNum<NUMOFSOLVERS;solverNum++){
	// 	printf("%d",FPGA_PIO_OFFSET_I_X + 0x60*solverNum);
	// 	lw__pio_write_ptr_i_x[solverNum] = (signed int *)(h2p_lw_virtual_base + FPGA_PIO_OFFSET_I_X + 0x60*solverNum);
	// 	lw__pio_write_ptr_i_x[solverNum] = (signed int *)(h2p_lw_virtual_base + FPGA_PIO_OFFSET_I_X + 0x60*solverNum);
	// 	lw__pio_write_ptr_i_y[solverNum] = (signed int *)(h2p_lw_virtual_base + FPGA_PIO_OFFSET_I_Y + 0x60*solverNum);
	// 	lw__pio_write_ptr_j_x[solverNum] = (signed int *)(h2p_lw_virtual_base + FPGA_PIO_OFFSET_J_X + 0x60*solverNum);
	// 	lw__pio_write_ptr_j_y[solverNum] = (signed int *)(h2p_lw_virtual_base + FPGA_PIO_OFFSET_J_Y + 0x60*solverNum);
	// 	lw__pio_write_ptr_fx[solverNum] = (signed int *)(h2p_lw_virtual_base + FPGA_PIO_OFFSET_FX + 0x60*solverNum);
	// 	lw__pio_write_ptr_fy[solverNum] = (signed int *)(h2p_lw_virtual_base + FPGA_PIO_OFFSET_FY + 0x60*solverNum);
	// }

	lw__pio_write_ptr_i_x = (signed int *)(h2p_lw_virtual_base + FPGA_PIO_OFFSET_I_X);
	lw__pio_write_ptr_i_y = (signed int *)(h2p_lw_virtual_base + FPGA_PIO_OFFSET_I_Y);
	lw__pio_write_ptr_j_x = (signed int *)(h2p_lw_virtual_base + FPGA_PIO_OFFSET_J_X);
	lw__pio_write_ptr_j_y = (signed int *)(h2p_lw_virtual_base + FPGA_PIO_OFFSET_J_Y);
	lw__pio_write_ptr_fx = (signed int *)(h2p_lw_virtual_base + FPGA_PIO_OFFSET_FX);
	lw__pio_write_ptr_fy = (signed int *)(h2p_lw_virtual_base + FPGA_PIO_OFFSET_FY);


	lw__pio_write_ptr_i_x_1 = (signed int *)(h2p_lw_virtual_base + FPGA_PIO_OFFSET_I_X_1);
	lw__pio_write_ptr_i_y_1 = (signed int *)(h2p_lw_virtual_base + FPGA_PIO_OFFSET_I_Y_1);
	lw__pio_write_ptr_j_x_1 = (signed int *)(h2p_lw_virtual_base + FPGA_PIO_OFFSET_J_X_1);
	lw__pio_write_ptr_j_y_1 = (signed int *)(h2p_lw_virtual_base + FPGA_PIO_OFFSET_J_Y_1);
	lw__pio_write_ptr_fx_1 = (signed int *)(h2p_lw_virtual_base + FPGA_PIO_OFFSET_FX_1);
	lw__pio_write_ptr_fy_1 = (signed int *)(h2p_lw_virtual_base + FPGA_PIO_OFFSET_FY_1);

	lw__pio_write_ptr_i_x_2 = (signed int *)(h2p_lw_virtual_base + FPGA_PIO_OFFSET_I_X_2);
	lw__pio_write_ptr_i_y_2 = (signed int *)(h2p_lw_virtual_base + FPGA_PIO_OFFSET_I_Y_2);
	lw__pio_write_ptr_j_x_2 = (signed int *)(h2p_lw_virtual_base + FPGA_PIO_OFFSET_J_X_2);
	lw__pio_write_ptr_j_y_2 = (signed int *)(h2p_lw_virtual_base + FPGA_PIO_OFFSET_J_Y_2);
	lw__pio_write_ptr_fx_2 = (signed int *)(h2p_lw_virtual_base + FPGA_PIO_OFFSET_FX_2);
	lw__pio_write_ptr_fy_2 = (signed int *)(h2p_lw_virtual_base + FPGA_PIO_OFFSET_FY_2);


	lw__pio_write_ptr_i_x_3 = (signed int *)(h2p_lw_virtual_base + FPGA_PIO_OFFSET_I_X_3);
	lw__pio_write_ptr_i_y_3 = (signed int *)(h2p_lw_virtual_base + FPGA_PIO_OFFSET_I_Y_3);
	lw__pio_write_ptr_j_x_3 = (signed int *)(h2p_lw_virtual_base + FPGA_PIO_OFFSET_J_X_3);
	lw__pio_write_ptr_j_y_3 = (signed int *)(h2p_lw_virtual_base + FPGA_PIO_OFFSET_J_Y_3);
	lw__pio_write_ptr_fx_3 = (signed int *)(h2p_lw_virtual_base + FPGA_PIO_OFFSET_FX_3);
	lw__pio_write_ptr_fy_3 = (signed int *)(h2p_lw_virtual_base + FPGA_PIO_OFFSET_FY_3);


	lw__pio_write_ptr_i_x_4 = (signed int *)(h2p_lw_virtual_base + FPGA_PIO_OFFSET_I_X_4);
	lw__pio_write_ptr_i_y_4 = (signed int *)(h2p_lw_virtual_base + FPGA_PIO_OFFSET_I_Y_4);
	lw__pio_write_ptr_j_x_4 = (signed int *)(h2p_lw_virtual_base + FPGA_PIO_OFFSET_J_X_4);
	lw__pio_write_ptr_j_y_4 = (signed int *)(h2p_lw_virtual_base + FPGA_PIO_OFFSET_J_Y_4);
	lw__pio_write_ptr_fx_4 = (signed int *)(h2p_lw_virtual_base + FPGA_PIO_OFFSET_FX_4);
	lw__pio_write_ptr_fy_4 = (signed int *)(h2p_lw_virtual_base + FPGA_PIO_OFFSET_FY_4);


	lw__pio_write_ptr_i_x_5 = (signed int *)(h2p_lw_virtual_base + FPGA_PIO_OFFSET_I_X_5);
	lw__pio_write_ptr_i_y_5 = (signed int *)(h2p_lw_virtual_base + FPGA_PIO_OFFSET_I_Y_5);
	lw__pio_write_ptr_j_x_5 = (signed int *)(h2p_lw_virtual_base + FPGA_PIO_OFFSET_J_X_5);
	lw__pio_write_ptr_j_y_5 = (signed int *)(h2p_lw_virtual_base + FPGA_PIO_OFFSET_J_Y_5);
	lw__pio_write_ptr_fx_5 = (signed int *)(h2p_lw_virtual_base + FPGA_PIO_OFFSET_FX_5);
	lw__pio_write_ptr_fy_5 = (signed int *)(h2p_lw_virtual_base + FPGA_PIO_OFFSET_FY_5);

	lw__pio_write_ptr_i_x_6 = (signed int *)(h2p_lw_virtual_base + FPGA_PIO_OFFSET_I_X_6);
	lw__pio_write_ptr_i_y_6 = (signed int *)(h2p_lw_virtual_base + FPGA_PIO_OFFSET_I_Y_6);
	lw__pio_write_ptr_j_x_6 = (signed int *)(h2p_lw_virtual_base + FPGA_PIO_OFFSET_J_X_6);
	lw__pio_write_ptr_j_y_6 = (signed int *)(h2p_lw_virtual_base + FPGA_PIO_OFFSET_J_Y_6);
	lw__pio_write_ptr_fx_6 = (signed int *)(h2p_lw_virtual_base + FPGA_PIO_OFFSET_FX_6);
	lw__pio_write_ptr_fy_6 = (signed int *)(h2p_lw_virtual_base + FPGA_PIO_OFFSET_FY_6);

	lw__pio_write_ptr_i_x_7 = (signed int *)(h2p_lw_virtual_base + FPGA_PIO_OFFSET_I_X_7);
	lw__pio_write_ptr_i_y_7 = (signed int *)(h2p_lw_virtual_base + FPGA_PIO_OFFSET_I_Y_7);
	lw__pio_write_ptr_j_x_7 = (signed int *)(h2p_lw_virtual_base + FPGA_PIO_OFFSET_J_X_7);
	lw__pio_write_ptr_j_y_7 = (signed int *)(h2p_lw_virtual_base + FPGA_PIO_OFFSET_J_Y_7);
	lw__pio_write_ptr_fx_7 = (signed int *)(h2p_lw_virtual_base + FPGA_PIO_OFFSET_FX_7);
	lw__pio_write_ptr_fy_7 = (signed int *)(h2p_lw_virtual_base + FPGA_PIO_OFFSET_FY_7);

	lw__pio_write_ptr_i_x_8 = (signed int *)(h2p_lw_virtual_base + FPGA_PIO_OFFSET_I_X_8);
	lw__pio_write_ptr_i_y_8 = (signed int *)(h2p_lw_virtual_base + FPGA_PIO_OFFSET_I_Y_8);
	lw__pio_write_ptr_j_x_8 = (signed int *)(h2p_lw_virtual_base + FPGA_PIO_OFFSET_J_X_8);
	lw__pio_write_ptr_j_y_8 = (signed int *)(h2p_lw_virtual_base + FPGA_PIO_OFFSET_J_Y_8);
	lw__pio_write_ptr_fx_8 = (signed int *)(h2p_lw_virtual_base + FPGA_PIO_OFFSET_FX_8);
	lw__pio_write_ptr_fy_8 = (signed int *)(h2p_lw_virtual_base + FPGA_PIO_OFFSET_FY_8);

	lw__pio_write_ptr_i_x_9 = (signed int *)(h2p_lw_virtual_base + FPGA_PIO_OFFSET_I_X_9);
	lw__pio_write_ptr_i_y_9 = (signed int *)(h2p_lw_virtual_base + FPGA_PIO_OFFSET_I_Y_9);
	lw__pio_write_ptr_j_x_9 = (signed int *)(h2p_lw_virtual_base + FPGA_PIO_OFFSET_J_X_9);
	lw__pio_write_ptr_j_y_9 = (signed int *)(h2p_lw_virtual_base + FPGA_PIO_OFFSET_J_Y_9);
	lw__pio_write_ptr_fx_9 = (signed int *)(h2p_lw_virtual_base + FPGA_PIO_OFFSET_FX_9);
	lw__pio_write_ptr_fy_9 = (signed int *)(h2p_lw_virtual_base + FPGA_PIO_OFFSET_FY_9);
	///============================================

	//--------------------------------------------
	// mouse stuff
	//--------------------------------------------

    int fd, bytes;
    unsigned char data[3];

    const char *pDevice = "/dev/input/mice";

    // Open Mouse
    fd = open(pDevice, O_RDWR);
    if(fd == -1)
    {
        printf("ERROR Opening %s\n", pDevice);
        return -1;
    }



	//text

	vga_char_ptr =(unsigned int *)(vga_char_virtual_base);
    vga_pixel_ptr =(unsigned int *)(vga_pixel_virtual_base);    

	/* create a message to be displayed on the VGA 
		and LCD displays */
	// char text_top_row[40] = "DE1-SoC ARM/FPGA\0";
	// char text_bottom_row[40] = "Cornell ece5760\0";
	// char num_string[20], time_string[50] ;
	
	// a pixel from the video
	int pixel_color;
	// video input index
	int i,j, count;
	



	///
    int left, middle, right;
    signed char x, y;


	int mouse_x = 320;
	int mouse_y = 240;

    int prev_mouse_x = mouse_x;
    int prev_mouse_y = mouse_y;


	//store_prev_pixels(mouse_x,mouse_y);


    VGA_box (0, 0, 639, 479, 0x00);
	

    


    int prev_left = 0;
    int prev_right = 0;
    // start the thread
    pthread_t sim_thread;
	int err = pthread_create(&sim_thread, NULL, simulate_thread, NULL);

	pthread_t ux_thread;
	int err2 = pthread_create(&ux_thread, NULL, ux, NULL);
    
    while(1){
        

		bytes = read(fd, data, sizeof(data));
		//*(lw__pio_write_ptr_rst) = 0;

        if(bytes > 0)
        {   
            
            
            VGA_circle(prev_mouse_x,prev_mouse_y,10,0x00);

            
            left = data[0] & 0x1;
            right = data[0] & 0x2;
            middle = data[0] & 0x4;

			x = data[1];
            y = data[2];
			//load_prev_pixels(mouse_x,mouse_y);
			if(mouse_y+1 -y/2< 480 && mouse_y-1-y/2>0){
				mouse_y = mouse_y - y/2;
			}
			if(mouse_x+1 +x/2< 640 && mouse_x +x/2-1>0){
				mouse_x = mouse_x + x/2;
			}


            
			if(left==1&&prev_left==0){

                if(NumOfPartOnScreen<numOfPart){

                    //0 ==> x ; 1=>y
					int i;
					int partperclick = 4;
					for (i=0; i <NUMOFSOLVERS; i++) {

						int x_vel = rand() % 100;
						float init_x_vel= ((float)x_vel)/100;
						int y_vel = rand() % 100;
						float init_y_vel= ((float)y_vel)/100;

						int y_pos = rand() % 20;
						float init_y_pos= ((float)y_pos);
						int x_pos = rand() % 20;
						float init_x_pos= ((float)x_pos);

						part_pos[NumOfPartOnScreen][0] = mouse_x + init_x_pos*3;
						part_pos[NumOfPartOnScreen][1] = mouse_y + init_y_pos*3;

						part_vel[NumOfPartOnScreen][0] = init_x_vel;
						part_vel[NumOfPartOnScreen][1] = init_y_vel;

						part_acc[NumOfPartOnScreen][0] = 0;
						part_acc[NumOfPartOnScreen][1] = accGrav;

						part_color[NumOfPartOnScreen] = white;


						VGA_disc((int)part_pos[NumOfPartOnScreen][0],(int)part_pos[NumOfPartOnScreen][1],sizeOfPartOnScreen,black);
						//VGA_PIXEL((int)part_pos[NumOfPartOnScreen][x],(int)part_pos[NumOfPartOnScreen][y],0xff);
						NumOfPartOnScreen += 1;
						//printf("num of Particles on screen = %d ", NumOfPartOnScreen);
                
					}
					prev_left=1;
					draw_txt();


                }
			}
			if(left==0){
				prev_left =0;

			}

            VGA_circle(mouse_x,mouse_y,10,white);
            prev_mouse_x=mouse_x;
            prev_mouse_y=mouse_y;
        }

	}

    pthread_join(sim_thread, NULL);
    pthread_join(ux_thread, NULL);
} // end main

/****************************************************************************************
 * Subroutine to send a string of text to the VGA monitor 
****************************************************************************************/
void VGA_text(int x, int y, char * text_ptr)
{
  	volatile char * character_buffer = (char *) vga_char_ptr ;	// VGA character buffer
	int offset;
	/* assume that the text string fits on one line */
	offset = (y << 7) + x;
	while ( *(text_ptr) )
	{
		// write to the character buffer
		*(character_buffer + offset) = *(text_ptr);	
		++text_ptr;
		++offset;
	}
}

/****************************************************************************************
 * Subroutine to clear text to the VGA monitor 
****************************************************************************************/
void VGA_text_clear()
{
  	volatile char * character_buffer = (char *) vga_char_ptr ;	// VGA character buffer
	int offset, x, y;
	for (x=0; x<79; x++){
		for (y=0; y<59; y++){
	/* assume that the text string fits on one line */
			offset = (y << 7) + x;
			// write to the character buffer
			*(character_buffer + offset) = ' ';		
		}
	}
}

/****************************************************************************************
 * Draw a filled rectangle on the VGA monitor 
****************************************************************************************/
#define SWAP(X,Y) do{int temp=X; X=Y; Y=temp;}while(0) 

void VGA_box(int x1, int y1, int x2, int y2, short pixel_color)
{
	char  *pixel_ptr ; 
	int row, col;

	/* check and fix box coordinates to be valid */
	if (x1>639) x1 = 639;
	if (y1>479) y1 = 479;
	if (x2>639) x2 = 639;
	if (y2>479) y2 = 479;
	if (x1<0) x1 = 0;
	if (y1<0) y1 = 0;
	if (x2<0) x2 = 0;
	if (y2<0) y2 = 0;
	if (x1>x2) SWAP(x1,x2);
	if (y1>y2) SWAP(y1,y2);
	for (row = y1; row <= y2; row++)
		for (col = x1; col <= x2; ++col)
		{
			//640x480
			//pixel_ptr = (char *)vga_pixel_ptr + (row<<10)    + col ;
			// set pixel color
			//*(char *)pixel_ptr = pixel_color;	
			VGA_PIXEL(col,row,pixel_color);	
		}
}

/****************************************************************************************
 * Draw a outline rectangle on the VGA monitor 
****************************************************************************************/
#define SWAP(X,Y) do{int temp=X; X=Y; Y=temp;}while(0) 

void VGA_rect(int x1, int y1, int x2, int y2, short pixel_color)
{
	char  *pixel_ptr ; 
	int row, col;

	/* check and fix box coordinates to be valid */
	if (x1>639) x1 = 639;
	if (y1>479) y1 = 479;
	if (x2>639) x2 = 639;
	if (y2>479) y2 = 479;
	if (x1<0) x1 = 0;
	if (y1<0) y1 = 0;
	if (x2<0) x2 = 0;
	if (y2<0) y2 = 0;
	if (x1>x2) SWAP(x1,x2);
	if (y1>y2) SWAP(y1,y2);
	// left edge
	col = x1;
	for (row = y1; row <= y2; row++){
		//640x480
		//pixel_ptr = (char *)vga_pixel_ptr + (row<<10)    + col ;
		// set pixel color
		//*(char *)pixel_ptr = pixel_color;	
		VGA_PIXEL(col,row,pixel_color);		
	}
		
	// right edge
	col = x2;
	for (row = y1; row <= y2; row++){
		//640x480
		//pixel_ptr = (char *)vga_pixel_ptr + (row<<10)    + col ;
		// set pixel color
		//*(char *)pixel_ptr = pixel_color;	
		VGA_PIXEL(col,row,pixel_color);		
	}
	
	// top edge
	row = y1;
	for (col = x1; col <= x2; ++col){
		//640x480
		//pixel_ptr = (char *)vga_pixel_ptr + (row<<10)    + col ;
		// set pixel color
		//*(char *)pixel_ptr = pixel_color;	
		VGA_PIXEL(col,row,pixel_color);
	}
	
	// bottom edge
	row = y2;
	for (col = x1; col <= x2; ++col){
		//640x480
		//pixel_ptr = (char *)vga_pixel_ptr + (row<<10)    + col ;
		// set pixel color
		//*(char *)pixel_ptr = pixel_color;
		VGA_PIXEL(col,row,pixel_color);
	}
}

/****************************************************************************************
 * Draw a horixontal line on the VGA monitor 
****************************************************************************************/
#define SWAP(X,Y) do{int temp=X; X=Y; Y=temp;}while(0) 

void VGA_Hline(int x1, int y1, int x2, short pixel_color)
{
	char  *pixel_ptr ; 
	int row, col;

	/* check and fix box coordinates to be valid */
	if (x1>639) x1 = 639;
	if (y1>479) y1 = 479;
	if (x2>639) x2 = 639;
	if (x1<0) x1 = 0;
	if (y1<0) y1 = 0;
	if (x2<0) x2 = 0;
	if (x1>x2) SWAP(x1,x2);
	// line
	row = y1;
	for (col = x1; col <= x2; ++col){
		//640x480
		//pixel_ptr = (char *)vga_pixel_ptr + (row<<10)    + col ;
		// set pixel color
		//*(char *)pixel_ptr = pixel_color;	
		VGA_PIXEL(col,row,pixel_color);		
	}
}

/****************************************************************************************
 * Draw a vertical line on the VGA monitor 
****************************************************************************************/
#define SWAP(X,Y) do{int temp=X; X=Y; Y=temp;}while(0) 

void VGA_Vline(int x1, int y1, int y2, short pixel_color)
{
	char  *pixel_ptr ; 
	int row, col;

	/* check and fix box coordinates to be valid */
	if (x1>639) x1 = 639;
	if (y1>479) y1 = 479;
	if (y2>479) y2 = 479;
	if (x1<0) x1 = 0;
	if (y1<0) y1 = 0;
	if (y2<0) y2 = 0;
	if (y1>y2) SWAP(y1,y2);
	// line
	col = x1;
	for (row = y1; row <= y2; row++){
		//640x480
		//pixel_ptr = (char *)vga_pixel_ptr + (row<<10)    + col ;
		// set pixel color
		//*(char *)pixel_ptr = pixel_color;	
		VGA_PIXEL(col,row,pixel_color);			
	}
}


/****************************************************************************************
 * Draw a filled circle on the VGA monitor 
****************************************************************************************/

void VGA_disc(int x, int y, int r, short pixel_color)
{
	char  *pixel_ptr ; 
	int row, col, rsqr, xc, yc;
	
	rsqr = r*r;
	
	for (yc = -r; yc <= r; yc++)
		for (xc = -r; xc <= r; xc++)
		{
			col = xc;
			row = yc;
			// add the r to make the edge smoother
			if(col*col+row*row <= rsqr+r){
				col += x; // add the center point
				row += y; // add the center point
				//check for valid 640x480
				if (col>639) col = 639;
				if (row>479) row = 479;
				if (col<0) col = 0;
				if (row<0) row = 0;
				//pixel_ptr = (char *)vga_pixel_ptr + (row<<10) + col ;
				// set pixel color
				//*(char *)pixel_ptr = pixel_color;
				VGA_PIXEL(col,row,pixel_color);	
			}
					
		}
}

/****************************************************************************************
 * Draw a  circle on the VGA monitor 
****************************************************************************************/

void VGA_circle(int x, int y, int r, int pixel_color)
{
	char  *pixel_ptr ; 
	int row, col, rsqr, xc, yc;
	int col1, row1;
	rsqr = r*r;
	
	for (yc = -r; yc <= r; yc++){
		//row = yc;
		col1 = (int)sqrt((float)(rsqr + r - yc*yc));
		// right edge
		col = col1 + x; // add the center point
		row = yc + y; // add the center point
		//check for valid 640x480
		if (col>639) col = 639;
		if (row>479) row = 479;
		if (col<0) col = 0;
		if (row<0) row = 0;
		//pixel_ptr = (char *)vga_pixel_ptr + (row<<10) + col ;
		// set pixel color
		//*(char *)pixel_ptr = pixel_color;
		VGA_PIXEL(col,row,pixel_color);	
		// left edge
		col = -col1 + x; // add the center point
		//check for valid 640x480
		if (col>639) col = 639;
		if (row>479) row = 479;
		if (col<0) col = 0;
		if (row<0) row = 0;
		//pixel_ptr = (char *)vga_pixel_ptr + (row<<10) + col ;
		// set pixel color
		//*(char *)pixel_ptr = pixel_color;
		VGA_PIXEL(col,row,pixel_color);	
	}
	for (xc = -r; xc <= r; xc++){
		//row = yc;
		row1 = (int)sqrt((float)(rsqr + r - xc*xc));
		// right edge
		col = xc + x; // add the center point
		row = row1 + y; // add the center point
		//check for valid 640x480
		if (col>639) col = 639;
		if (row>479) row = 479;
		if (col<0) col = 0;
		if (row<0) row = 0;
		//pixel_ptr = (char *)vga_pixel_ptr + (row<<10) + col ;
		// set pixel color
		//*(char *)pixel_ptr = pixel_color;
		VGA_PIXEL(col,row,pixel_color);	
		// left edge
		row = -row1 + y; // add the center point
		//check for valid 640x480
		if (col>639) col = 639;
		if (row>479) row = 479;
		if (col<0) col = 0;
		if (row<0) row = 0;
		//pixel_ptr = (char *)vga_pixel_ptr + (row<<10) + col ;
		// set pixel color
		//*(char *)pixel_ptr = pixel_color;
		VGA_PIXEL(col,row,pixel_color);	
	}
}

// =============================================
// === Draw a line
// =============================================
//plot a line 
//at x1,y1 to x2,y2 with color 
//Code is from David Rodgers,
//"Procedural Elements of Computer Graphics",1985
void VGA_line(int x1, int y1, int x2, int y2, short c) {
	int e;
	signed int dx,dy,j, temp;
	signed int s1,s2, xchange;
     signed int x,y;
	char *pixel_ptr ;
	
	/* check and fix line coordinates to be valid */
	if (x1>639) x1 = 639;
	if (y1>479) y1 = 479;
	if (x2>639) x2 = 639;
	if (y2>479) y2 = 479;
	if (x1<0) x1 = 0;
	if (y1<0) y1 = 0;
	if (x2<0) x2 = 0;
	if (y2<0) y2 = 0;
        
	x = x1;
	y = y1;
	
	//take absolute value
	if (x2 < x1) {
		dx = x1 - x2;
		s1 = -1;
	}

	else if (x2 == x1) {
		dx = 0;
		s1 = 0;
	}

	else {
		dx = x2 - x1;
		s1 = 1;
	}

	if (y2 < y1) {
		dy = y1 - y2;
		s2 = -1;
	}

	else if (y2 == y1) {
		dy = 0;
		s2 = 0;
	}

	else {
		dy = y2 - y1;
		s2 = 1;
	}

	xchange = 0;   

	if (dy>dx) {
		temp = dx;
		dx = dy;
		dy = temp;
		xchange = 1;
	} 

	e = ((int)dy<<1) - dx;  
	 
	for (j=0; j<=dx; j++) {
		//video_pt(x,y,c); //640x480
		//pixel_ptr = (char *)vga_pixel_ptr + (y<<10)+ x; 
		// set pixel color
		//*(char *)pixel_ptr = c;
		VGA_PIXEL(x,y,c);			
		 
		if (e>=0) {
			if (xchange==1) x = x + s1;
			else y = y + s2;
			e = e - ((int)dx<<1);
		}

		if (xchange==1) y = y + s2;
		else x = x + s1;

		e = e + ((int)dy<<1);
	}
}
