#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>

#define STUDENT_ID_MAX 9
typedef struct studentNode
{
    char id[STUDENT_ID_MAX+1];
    float grade;
    float rank;
    float pr;
    float zscore;
}student;

enum dataEnum{AVERAGE, Q1, Q2, Q3, SD};
#define INFO_NAME_MAX 30
#define INFO_MAX 10
typedef struct infoNode
{
    char name[INFO_NAME_MAX];
    float data;
}info;
// 0 = average 

void typeArray(int *);
void typeArrayFloat(float *);

void readIO(char *);
int *findSpecificDataInLine(char);
int findLastInArray(int *);
int *findSpecificCharacterInString(char *, char);

int *combineArray(int *, int *);
float *setScoreArray(int *);
student *setStrudentInfoToStruct(int *, float *);
void writeIO(char *, student *, int);

void calculateAverage(student *, int);
student *copyArrayStudent(student *, int);
void bubbleSort(student *, int);
void findIQR(student *, int);
void calculateRank(student *, int);
void calculatePR(student* , int);
void calculateSD(student*, int);
void calculateZscore(student*, int);

#define SOURCE_DATA_MAX 500

char sourceData[SOURCE_DATA_MAX][100] = {0};

info dataInfo[INFO_MAX];

int main(void)
{
    int *idInSourceDataLine;
    int *eofPlace;
    float *score;

    readIO("Source_Data.txt");

    idInSourceDataLine = findSpecificDataInLine('A');
    eofPlace = findSpecificDataInLine('E');

    idInSourceDataLine = combineArray(idInSourceDataLine, eofPlace);
    free(eofPlace);

    score = setScoreArray(idInSourceDataLine);

    student *studentInfo = setStrudentInfoToStruct(idInSourceDataLine, score);
    int counterStudent = findLastInArray(idInSourceDataLine)-1;
    
    calculateAverage(studentInfo, counterStudent);
    student *studentInfoCopy = copyArrayStudent(studentInfo, counterStudent);

    bubbleSort(studentInfoCopy, counterStudent);
    findIQR(studentInfoCopy, counterStudent);
    calculateRank(studentInfoCopy, counterStudent);
    calculatePR(studentInfoCopy, counterStudent);
    calculateSD(studentInfoCopy, counterStudent);
    calculateZscore(studentInfoCopy, counterStudent);

    writeIO("Result.txt", studentInfoCopy, counterStudent);

    free(idInSourceDataLine);
    free(score);

    system("pause");
}

void readIO(char *fileAddress)
{
    FILE *fptr;

    fptr = fopen(fileAddress, "r");
    if(fptr == NULL)
    {
        printf("Error: Can't open the file");
        return;
    }
        

    int counterRow = 0;
    int counterCol = 0;
    char chTemp;

    while((chTemp = getc(fptr)) != EOF)
    {
        sourceData[counterRow][counterCol++] = (chTemp != '\n') ? chTemp : '\0';
        
        if(chTemp == '\n')
        {
            counterRow++;
            counterCol = 0;
        }
    }
    
    counterRow++;
    char endOfFile[3] = "EOF";
    for(int i = 0 ; i < 3 ; i++)
    {
        sourceData[counterRow][i] = endOfFile[i];
    }

    fclose(fptr);

    return;
}

void writeIO(char *fileAddress, student *studentInfo, int length)
{
    FILE *fptr;
    fptr = fopen(fileAddress, "w");

    fprintf(fptr, "%-15s %-10s %-14s %-10s\n", "STUDENT_ID", "SCORE", "PR", "Z-SCORE");
    for(int i = 0 ; i < length ; i++)
    {
        fprintf(fptr, "%-15s %-10.1f PR %-10.0f %- 10.2f ", studentInfo[i].id, studentInfo[i].grade, floor(studentInfo[i].pr), studentInfo[i].zscore);

        float percent = 0.25;
        for(int j = 1 ; j < 4 ; j ++)
        {
            if(ceil(length*percent) == i)
                fprintf(fptr, "%-10s", dataInfo[j].name);

            percent += 0.25;
        }
        fprintf(fptr,"\n");
    }

    putc('\n', fptr);
    for(int i = 0 ; i < length; i++)
    {
        fprintf(fptr, "%-20s: %5.3f\n", dataInfo[i].name, dataInfo[i].data);

        if(dataInfo[i+1].name[0] == '\0')
            break;
    }
    fclose(fptr);
}

int *findSpecificDataInLine(char targetData)
{
    int *storage = (int*)calloc(SOURCE_DATA_MAX, sizeof(int));

    int counterStorage = 0;
    for(int i = 0 ; i < SOURCE_DATA_MAX ; i++)
    {
        if(*sourceData[i] == targetData)
        {
            storage[counterStorage++] = i;
        }
    }

    return storage;
}

int findLastInArray(int *originalArray)
{
    int i = 0;
    while(originalArray[i] != '\0')
    {
        i++;
    }

    return i;
}

int findLastInString(char *originalArray)
{
    int i = 0;
    do
    {
        i++;
    }while(originalArray[i] != '\0');

    return i;
}

int *findSpecificCharacterInString(char *originalArray, char targetChar)
{
    int *storage = (int*)calloc(SOURCE_DATA_MAX, sizeof(int));

    int i = 0;
    int counterStorage = 0;
    while(originalArray[i] != '\0')
    {
        if(originalArray[i] == targetChar)
            storage[counterStorage++] = i;

        i++; 
    }

    return storage;
}

int *combineArray(int *arrayOne, int *arrayTwo)
{
    int arrayOneLast = findLastInArray(arrayOne);
    
    int i = 0;
    int counterArrayOne = arrayOneLast;

    while(arrayTwo[i] != 0)
    {
        arrayOne[counterArrayOne++] =  arrayTwo[i++];
    }

    return arrayOne;
}

float *setScoreArray(int *positionArray)
{
    float *score = (float*)calloc(SOURCE_DATA_MAX, sizeof(int));

    int i = 0;
    while(positionArray[i+1] != 0)
    {
        char *sourceDataFraction = sourceData[positionArray[i+1]-1];
        
        int sourceDataLast = 0;
        int *blankArray = NULL, blankArrayLast = 0;

        sourceDataLast = findLastInString(sourceDataFraction);
        blankArray = findSpecificCharacterInString(sourceDataFraction, ' ');
        blankArrayLast = findLastInArray(blankArray);
        
        int counterCurrent = (blankArrayLast == 0) ? 0 :  blankArray[blankArrayLast-1]+1;
        int j = 0;
        char *scoreCharTemp = (char*)malloc(sizeof(char)*10);
        while(counterCurrent < sourceDataLast)
        {
            scoreCharTemp[j++] = sourceDataFraction[counterCurrent++];
        }
        score[i++] = atof(scoreCharTemp);

        free(scoreCharTemp);
    }
    score[i] = -1;
    return score;
}

student *setStrudentInfoToStruct(int *studentIDArray, float *studentScoreArray)
{
    student *studentInfo = (student*)malloc(sizeof(student)*SOURCE_DATA_MAX);

    int i = 0;
    while(studentScoreArray[i] != -1)
    {  
        strcpy(studentInfo[i].id, sourceData[studentIDArray[i]]);
        studentInfo[i].grade = studentScoreArray[i];
        
        i++;
    }

    return studentInfo;
}

void calculateAverage(student *studentInfo, int length)
{
    strcpy(dataInfo[AVERAGE].name, "Arithmetic Average");
    float temp = 0.0;
    for(int i = 0 ; i < length ; i++)
    {
        temp += studentInfo[i].grade;
    }
    dataInfo[0].data = temp/length;

    return;
}

student *copyArrayStudent(student *studentInfo, int length)
{
    student *studentInfoCopy = (student*)malloc(sizeof(student)*SOURCE_DATA_MAX);

    for(int i = 0 ; i < SOURCE_DATA_MAX ; i++)
    {
        strcpy(studentInfoCopy[i].id, studentInfo[i].id);
        studentInfoCopy[i].grade = studentInfo[i].grade;
    }

    return studentInfoCopy;
}

void bubbleSort(student *studentInfo, int length)
{
    for(int i = 1 ; i <= length-1 ; i++)
    {
        for(int i = 0 ; i < length-1 ; i++)
        {
            if(studentInfo[i].grade < studentInfo[i+1].grade )
            {
                student studentTemp;
                studentTemp = studentInfo[i];
                studentInfo[i] = studentInfo[i+1];
                studentInfo[i+1] = studentTemp;
            }
        }
    }
}

void findIQR(student *studentInfo, int length)
{
    strcpy(dataInfo[Q3].name, "Q3(25\%)");
    strcpy(dataInfo[Q2].name, "Q2(50\% Median)");
    strcpy(dataInfo[Q1].name, "Q1(75\%)");

    float percent = 0.25;
    for(int i = 1 ; i < 4 ; i++)
    {
        // float data = length*percent;
        dataInfo[i].data = studentInfo[(int)ceil(length*percent)].grade;
        percent += 0.25;
    }

    return;
}

void calculateRank(student *studentInfo, int length)
{
    bool isSame = false;

    for(int i = 0 ; i < length ; i++)
    {
        if(i != 0)
        {
            isSame = (studentInfo[i-1].grade == studentInfo[i].grade) ? true : false; 
        }

        studentInfo[i].rank = isSame ? studentInfo[i-1].rank : i+1;
    }

    return;
}

void calculatePR(student *studentInfo, int length)
{
    int lastRank = studentInfo[length-1].rank;

    for(int i = 0 ; i < length ; i++)
    {
        studentInfo[i].pr = (float)(lastRank-studentInfo[i].rank)/lastRank*100;
    }

    return;
}

void calculateSD(student *studentInfo, int length)
{
    float accumulatorPower = 0.0;
    float tempGrade = 0.0;
    float sdResult = 0.0;

    for(int i = 0 ; i < length; i++)
    {
        tempGrade = studentInfo[i].grade;
        accumulatorPower += pow(tempGrade, 2);
    }

    sdResult = accumulatorPower/length - pow(dataInfo[AVERAGE].data, 2);
    sdResult = sqrt(sdResult);

    strcpy(dataInfo[SD].name, "Standard Deviation");
    dataInfo[SD].data = sdResult;

    return;
}

void calculateZscore(student *studentInfo, int length)
{
    for(int i = 0 ; i < length ; i++)
    {
        studentInfo[i].zscore = (studentInfo[i].grade-dataInfo[AVERAGE].data)/dataInfo[SD].data;    
    }
}

void typeArray(int *array)
{
    int i = 0;
    while(array[i] != 0)
    {
        printf("%d ", array[i++]);
    }
}

void typeArrayFloat(float *array)
{
    int i = 0;
    while(array[i] != -1)
    {
        printf("%f ", array[i++]);
    }
}