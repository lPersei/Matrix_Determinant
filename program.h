//
//  program.h
//  MyApp_Maciez
//
//  Created by Hryhorii Shynkovskyi on 22.04.18.
//  Copyright © 2018 Hryhorii Shynkovskyi. All rights reserved.
//
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#ifndef program_h
#define program_h

void Application_Start();

void MENU();

int dimension_input(int N);

void readfile(FILE *f, int **TAB, int N);

void writefile(FILE *f, int **TAB, int N);

int ** dynamic_TAB_creating(int N);

void dynamic_TAB_free(int **TAB, int N);

void TAB_random_filling(int **TAB, int N);

int randomValue(int lowerNUM, int upperNUM);

void TAB_print(int **TAB, int N);

void TAB_keyboard_filling(int **TAB, int N);

int matrixDet(int **TAB, int size);

void getMatrixWithoutRowAndCol(int **TAB, int size, int row, int col, int **newTAB);

#endif /* program_h */
