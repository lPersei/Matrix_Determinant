//
//  program.c
//  MyApp_Maciez
//
//  Created by Hryhorii Shynkovskyi on 22.04.18.
//  Copyright © 2018 Hryhorii Shynkovskyi. All rights reserved.
//

#include "program.h"

int dimension_input(int N)  //Wprowadzenie rozmiaru macierzy i sprawdzenie czy podana wartość jest typu liczbowego
{
    int res; //pomocnicza zmienna
    printf("\nInput Dimension of matrix : ");
    do
    {
        res = scanf("%d", &N);
        while (getchar() != '\n');
        if (res == 1 && N>0)
            return N;
        else
            printf("Please input the NUMERIC value ONLY which is BIGGER than 0 :\n");
    }
    while (res != 1);

}

int ** dynamic_TAB_creating(int N)//dynamiczne tworzenie tablicy za pomoca malloc
{
    int M = N;
    int **TAB = (int **)malloc(N*sizeof(int *));
    for(int i = 0; i < N; i++)
    {
        TAB[i] = (int *)malloc(M*sizeof(int));
    }
    return TAB;
}

void dynamic_TAB_free(int **TAB, int N)//Zwolnienie pamieńci nadaną macierzę
{
    for(int i = 0; i < N; i++)
    {
        free(TAB[i]);
    }
    free(TAB);
}

int randomValue(int lowerNUM, int upperNUM)//generator liczb pseudolosowych z zakresu
{
    return ((rand() % (upperNUM-lowerNUM+1)) + lowerNUM);
}

void TAB_random_filling(int **TAB, int N) //zepełnienie losowymi liczbami z zakresu podanego przez uzytkownika
{
    int M=N;
    int lowerNUM,upperNUM;
    printf("\nInput the Lower number for random filing the matrix : ");
    scanf("%d",&lowerNUM);
    printf("\nInput the Upper number for random filing the matrix : ");
    scanf("%d",&upperNUM);
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < M; j++)
        {
            TAB[i][j] = randomValue(lowerNUM,upperNUM);
        }
    }
}

void TAB_print(int **TAB, int N) //wypisywanie macierzy na ekran z zachowaniem formy tabelki
{
    int M=N;
    printf("\n");
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < M; j++)
        {
            printf("%*d", 5, TAB[i][j]);
        }
        printf("\n");
    }
}

void TAB_keyboard_filling(int **TAB, int N) //wypełnienie wartościami z klawiatury
{
    printf("Please input the following indexes with the intigers");
    int M=N;
    for(int i = 0; i < N; i++) //przeliczenie i następne prepisywanie do macierzy wartości
    {
        for(int j = 0; j < M; j++)
        {
            printf("[%d][%d] = ", i,j);
            scanf("%d",&TAB[i][j]);
            printf("\n");
        }
    }
}
//Przy wejściu przyjmuje tylko samą macierz i jej rozmiar. Sprawdzamy rozmiar macierzy, jeśli jest ona większa niż 2x2, idziemy liczyć rekursję. Najpierw tworzymy macierz równą bieżącej z wyciętym wierszem zerowym i j-tum poziomem, a następnie w cyklu liczymy sumę od formuły do zmiennej det.
int matrixDet(int **TAB, int N)
{
    int det = 0;
    int degree = 1; // (-1)^(1+j) z formuły wyznacznika


    if(N == 1) // warunek wyjścia z rekursji
    {
        return TAB[0][0];
    }
    else if(N == 2) // warunek wyjścia z rekursji
    {
        return TAB[0][0]*TAB[1][1] - TAB[0][1]*TAB[1][0];
    }
    else
    {
        //Macierz bez pionu i poziomu
        int **newTAB = (int**)malloc((N-1)*sizeof(int));
        for(int i = 0; i < N-1; i++)
        {
            newTAB[i] = (int*)malloc((N-1)*sizeof(int));
        }


        //Rozklad po 0-em poziomie, cykl leci po pionam
        for(int j = 0; j < N; j++)
        {
            //Usunąć z macierzy i-tą poziomę i j-ty pion
            //Wynik w newTAB
            getMatrixWithoutRowAndCol(TAB, N, 0, j, newTAB);

            //Wywylanie rekursywne
            //Za formullą: summa po j, (-1)^(1+j) * matrix[0][j] * minor_j (to jest summa z formuly)
            //gdzie minor_j - dodatkowy minor elementa matrix[0][j]
            // (przypominam że minor to wyznacznik macierzy bez 0-ej pożiomy i j-go pionu)
            det = det + (degree * TAB[0][j] * matrixDet(newTAB, N-1));
            //"Zmieniamy" stopień mnożnika
            degree = -degree;
        }

        //Czyścimy pamięć na kożnym kroku
        for(int i = 0; i < N-1; i++)
        {
            free(newTAB[i]);
        }
        free(newTAB);
    }
    return det;

}
//Aby obliczyć wyznacznik zgodnie ze wzorem, musimy usunąć macierz i-tego poziomu i j-go piomu z macierzy. Wtedy macierz bez wiersza i bez kolumny będzie rekurencjonowana dopóki rozmiar macierzy nie stanie się 2x2, będzie to warunkiem wyjścia z rekursji.
void getMatrixWithoutRowAndCol(int **TAB, int N, int row, int col, int **newTAB)
{
    int offsetRow = 0; //Przesunieńcie indeksu poziomy w matryce
    int offsetCol = 0; //Przesunieńcie indeksu piony w matryce
    for(int i = 0; i < N-1; i++)
    {
        //Pominąc row-ą poziomę
        if(i == row)
        {
            offsetRow = 1; //Jak tylko spotkasz poziomę, którą trzeba pominąć, rob przesunieńcie dla oryginalnej macierzy
        }

        offsetCol = 0; //Zerowac przesunieńcie pionu
        for(int j = 0; j < N-1; j++)
        {
            //Pominąc col-ny pion
            if(j == col)
            {
                offsetCol = 1; //Spotkaleś właściwy pion, pomijamy go przesunieńciem
            }

            newTAB[i][j] = TAB[i + offsetRow][j + offsetCol];
        }
    }
}

void readfile(FILE *f, int **TAB, int N)//wczytywanie pliku i zapis do macierzy
{
    int M=N;
    f = fopen("data.txt","rt"); //odtwarcie pliku dla wczytywania jako tekstowy plik
    if (f == NULL)
    {
        printf("\nNie udalo sie odtworzyć");
    }
    else
    {
        printf("\nUdalo sie odtworzyć");
    }
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < M; j++)
        {
            fscanf(f,"%d",&TAB[i][j]);//wczytywanie dannych i zapis w macierz
        }
    }
    fclose(f);// zamkniencie pliku
}

void writefile(FILE *f, int **TAB, int N) /*Zapis do pliku data.txt/Usunieńcie istniejącego i twożenie nowego , a jak nie istnieje tego pliku, to jego tworzenie*/
{
    int M=N;
    f = fopen("data.txt","w"); //odtwarcie pliku dla zapisu
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < M; j++)
        {
            fprintf(f,"%d\n",TAB[i][j]); //Zapisywanie dannych do buferu
            fflush(f); // Z buferu do pliku
        }
    }
    fclose(f); // zamkniencie pliku

}
void Application_Start() //start programu
{
    FILE *f; //tworzenie wskaznika na strukturę FILE
    srand((unsigned) time(NULL)); //inicjalizacja generatora liczb losowych
    int **TAB; // wskaznik na macierz
    int N = 0,det; // N - rozmiar macierzy , det - wyznacznik macierzy
    int i =0; // pomocnicza zmienna dla zapętlenia Menu
    char ch; // zmienna dla switch`a w menu

    MENU();
    while(i!=1) //nieskończonne zapętlenie dla menu
    {
        ch = getch(); //wpisuję bez wyświetlenia wartości zmiennej w konsoli
        switch(ch)
        {
        case '1':
            N = dimension_input(N);
            TAB = dynamic_TAB_creating(N);
            system("cls"); //czyszczenie konsoli
            MENU();
            break;
        case '2':
            TAB_random_filling(TAB,N);
            system("cls");
            MENU();
            break;
        case '3':
            TAB_keyboard_filling(TAB,N);
            system("cls");
            MENU();
            break;
        case '4':
            TAB_print(TAB,N);
            system("pause"); //Zatrzymanie dla spojrzenia na to jak wygląda macierz graficznie
            printf("Enter the key to continue . . .\n");
            system("cls");
            MENU();
            break;
        case '5':
            det = matrixDet(TAB,N);
            printf("\nDeterminant of matrix = [%d]\n",det);
            system("pause");
            printf("Enter the key to continue . . .\n");
            system("cls");
            MENU();
            break;
        case '6':
            writefile(f,TAB,N);
            system("cls");
            MENU();
            break;
        case '7':
            readfile(f,TAB,N);
            system("cls");
            MENU();
            break;
        case '8':
            dynamic_TAB_free(TAB,N);
            system("cls");
            MENU();
            break;
        case '9':
            dynamic_TAB_free(TAB,N);
            exit(-1); //Wyjście z programu
        default:
            system("cls");
            printf("Please choose from [1]-[8] options\n"); //dla przypadku nieprawidlowego wybory z menu
            MENU();
        }
    }

}

void MENU() //Wywolanie napisów w menu
{
    printf("MENU :\n\n");
    printf("PRESS 1 to -> Create empty matrix\n");
    printf("PRESS 2 to -> Fill the matrix with the random values\n");
    printf("PRESS 3 to -> Fill the matrix with the values from keyboard\n");
    printf("PRESS 4 to -> Print the matrix\n");
    printf("PRESS 5 to -> Find the Determinant of matrix\n");
    printf("PRESS 6 to -> Save your matrix to the file\n");
    printf("PRESS 7 to -> Open the matrix from the file\n");
    printf("PRESS 8 to -> Free the allocated memory of your matrix\n");
    printf("PRESS 9 to -> Exit the program\n\n");
    printf("Select the option :");
}
