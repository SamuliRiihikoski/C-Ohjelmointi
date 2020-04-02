#include <stdlib.h>
#include <math.h>

#define MAX_ARRAY 1000

typedef struct Databank {
    
    int count;
    int max;                // max temp
    int min;                // min temp
    int tempsRange;         // abs(MAX-MIN)
    int temps[MAX_ARRAY];   // Temps are int numbers. 
                            // First number from right is a decimal number.

} Databank;

void InitData(Databank *TempData) {

    for(int i=0; i<MAX_ARRAY; i++)
        TempData->temps[i] = -1000;
    
    TempData->count = 0;
    TempData->max = -1000;
    TempData->min = 1000;
    TempData->tempsRange = 0;
}

void ImportData(Databank *TempData) {

    FILE *fp;
    char line[256];
    
    InitData(TempData);

    // READ LÄMPÖTILA DATA FROM FILE

    fp = fopen("day_temp.txt","r");
    if(fp == NULL) {
        printf("Error!");
    }

    int array_index = 0;
    float temp;
    int row = 0;
    
    while (fgets(line, sizeof(line), fp) != NULL) {
        
        if (row >= 2 && (line[0] >= 48 && line[0] <= 57)) {

            sscanf(line, "%f", &temp);

            // Makes sure that number rouding is correct.

            if(temp >= 0)       
                temp += 0.05;
            else
                temp -= 0.05;    
            
            // Multiply temp with 10 we move first decimal to left side of the decimal point

            temp *= 10;    

            TempData->temps[array_index] = (int)temp;

            // Calc MAX and MIN of temps
            
            if(TempData->temps[array_index] >= TempData->max)
                TempData->max = TempData->temps[array_index];

            if (TempData->temps[array_index] <= TempData->min)
                TempData->min = TempData->temps[array_index];
            
            array_index++;
        }
        row++;
            
    }
    TempData->tempsRange = abs(TempData->max - TempData->min);

    fclose(fp);

}