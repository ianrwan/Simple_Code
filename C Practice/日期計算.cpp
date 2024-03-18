#include<stdio.h>
#include<stdlib.h>

#define MONTH_TOTAL 12

typedef struct // ����s�� 
{
	int year;
	short int month;
	short int day;
}DATE;

short int leapYear( int ); // �P�_�|�~ 
short int beginDateCalculate( DATE ); // �}�l����p�� 
short int endDateCalculate( DATE ); // ��������p�� 
short int noCrossYear( DATE, DATE); // ����~������p�� 
short int correctInput( DATE, DATE ); // �T�w��J�S�����~ 

short int eachDay[MONTH_TOTAL+1] = {0,31,28,31,30,31,30,31,31,30,31,30,31}; // �U�Ӥ����� 

int main(void)
{
//	�~���ۮt�B�`�Ѽ� 
	int yearDifference, dayTotal = 0;
//	�|�~�P�_�B��J���T�P�_�P�_ 
	short int leapCheck, checkPoint; 

	DATE beginDate, endDate;
	
	do
	{
		printf("�п�J�}�l�~���]�H�Ů���ΡA�ҡG2022 10 10�^: ");
		scanf("%d %d %d", &beginDate.year, &beginDate.month, &beginDate.day);
	
		printf("�п�J�����~���]�H�Ů���ΡA�ҡG2023 10 10�^: ");
		scanf("%d %d %d", &endDate.year, &endDate.month, &endDate.day);
		
		putchar('\n');
		
//		�P�_��J�O�_���T 
		checkPoint = correctInput( beginDate, endDate);
		
		if( checkPoint )
		{
			printf("�Э��s��J\n");
			putchar('\n');
		}
		
	}while( checkPoint );
	
//	�~���ۮt 
	yearDifference = endDate.year - beginDate.year;
	
//	�~�����s�i��L��~�禡 
	if( yearDifference == 0 )
		dayTotal += noCrossYear(beginDate, endDate);
	else
	{
		dayTotal += beginDateCalculate(beginDate);
		dayTotal += endDateCalculate(endDate);
	
		for( int i = 2 ; i <= yearDifference ; i++ )
		{
			leapCheck = leapYear( beginDate.year + i -1 );
			(leapCheck) ? dayTotal += 366 : dayTotal += 365;
		}
	}
	
	printf("�����ۮt�Ѽơ]�t�Ĥ@�ѡ^�G%d ��\n", dayTotal);
	printf("�����ۮt�Ѽơ]���t�Ĥ@�ѡ^�G%d ��\n", dayTotal-1);
	
	system("pause");
}

short int leapYear( int year )
{
//	0 �N���~�B1 �N��|�~

	if( year%4 == 0 && year%100 != 0 )
		return 1;
	else if( year%100 == 0 && year%400 != 0)
		return 0;
		else if( year%400 == 0 )
			return 1;
			else
				return 0;
}

short int beginDateCalculate( DATE date )
{
//	�|�~�P�_�B����ۮt�B����p�� 
	short int leapCheck, monthDifference, monthAdd = 0;
	
	leapCheck = leapYear(date.year);
	monthDifference = 12 - date.month;
	
//	�p�����`�M�A���t�Ĥ@��� 
	for( short int i = 12 ; i > 12-monthDifference ; i-- )
	{
		if( i != 2 )
			monthAdd += eachDay[i];
		else
			( !leapCheck ) ? monthAdd += eachDay[i] : monthAdd = monthAdd + eachDay[i] + 1; 
	}
	
//	�w�`�M��� + �Ĥ@������  
	if( date.month == 2 && leapCheck )
		monthAdd = monthAdd + eachDay[date.month] + 1 - date.day + 1; // +1 �Ϥ���ܬ� 29 -date.day �N���� +1 ��n�ɦ^�� 
	else
		monthAdd = monthAdd + eachDay[date.month] - date.day + 1;
	
	return monthAdd;
}

short int endDateCalculate( DATE date )
{
// 	�|�~�P�_�B����ۮt�B����p�� 
	short int leapCheck, monthDifference, monthAdd = 0;
	
	leapCheck = leapYear(date.year);
	monthDifference = date.month - 1;
	
	for( short int i = 1 ; i < 1+monthDifference ; i++ )
	{
		if( i != 2 )
			monthAdd += eachDay[i];
		else
			( !leapCheck ) ? monthAdd += eachDay[i] : monthAdd = monthAdd + eachDay[i] + 1; 
	}
	
	monthAdd = monthAdd + date.day;
	
	return monthAdd;
}

short int noCrossYear( DATE beginDate, DATE endDate )
{
// 	�|�~�P�_�B����ۮt�B����p�� 
	short int leapCheck, monthDifference, monthAdd = 0;
	
	leapCheck = leapYear( beginDate.year );
	monthDifference = endDate.month - beginDate.month;
	
//	�ۮt���� 0 �i�����p�� 
	if( monthDifference == 0 )
		monthAdd = endDate.day-beginDate.day+1;
		
	else
	{
//		�P�_�_�l�O�_�� 2 ��|�~ 
		if( leapCheck && beginDate.month == 2 )
		{
//			�p��}�l��Y�I��몺�`�M 
			monthAdd =  (eachDay[beginDate.month] + 1 - beginDate.day + 1) + endDate.day;
			
//			��������p�� 
			for( int i = 2 ; i <= monthDifference ; i++ )
				monthAdd += eachDay[beginDate.month+i-1]; 
		}
			
		
		else
		{
//			�p��}�l��Y�I��몺�`�M 
			monthAdd =  (eachDay[beginDate.month] - beginDate.day + 1) + endDate.day;
			
//			������p�� 
			for( int i = 2 ; i <= monthDifference ; i++ )
			{
				if( beginDate.month+i-1 != 2 )
					monthAdd += eachDay[beginDate.month+i-1];
					
				else
					( leapCheck ) ? monthAdd = monthAdd + eachDay[beginDate.month+i-1] + 1 : monthAdd += eachDay[beginDate.month+i-1];
			}
		}
	}
	return monthAdd;
}

//	�ˬd��J 
short int correctInput( DATE beginDate, DATE endDate )
{
//	flag 0 ����J���~�A1 ����J���T�B�}�l�~�|�~�P�_�B�I��~�|�~�P�_ 
	int flag = 0, beginLeapCheck, endLeapCheck;
	
//	�P�_�}�l�M�������ɶ��O�_�ۤ� 
	if( endDate.year < beginDate.year)
	{
		flag = 1;
		printf("�����~�����i�H�p��}�l�~��\n");
	}
	
	else if( endDate.year == beginDate.year )
	{
		if( endDate.month < beginDate.month )
		{
			flag = 1;
			printf("����������i�H�p��}�l���\n");
		}
		
		else if( endDate.month == beginDate.month )
		{
			if( endDate.day < beginDate.day )
			{
				flag = 1;
				printf("����������i�H�p��}�l���\n");
			}
		}
	}
	
//	����ƧP�_ 
	if( beginDate.year <= 0 || beginDate.month <= 0 || beginDate.day <= 0 || endDate.year <= 0 || endDate.month <= 0 || endDate.day <= 0 )
	{
		flag = 1;
		printf("�п�J�����\n");
	}
	
//	����ˬd 
	if( beginDate.month > 12 || endDate.month > 12 )
	{
		flag = 1;
		printf("�@�~�̦h�u�� 12 �Ӥ�\n");
	}
	
//	�e�����~�ݭץ��~�@�ᶵ�ˬd 
	if( flag == 1 )
		return flag;
	
	beginLeapCheck = leapYear(beginDate.year);
	endLeapCheck = leapYear(endDate.year);

//	����ˬd 
	switch( beginLeapCheck )
	{
		case 0:
			switch( endLeapCheck )
			{
				case 0:
					if( beginDate.day > eachDay[beginDate.month] || endDate.day > eachDay[endDate.month] )
					{
						flag = 1;
						printf("%d �~ %d ��u�� %d ��A%d �~ %d ��u�� %d ��\n", beginDate.year, beginDate.month, eachDay[beginDate.month]\
						,endDate.year, endDate.month, eachDay[endDate.month]);
					}
						break;
				case 1:
					if( endDate.month == 2 )
					{
						if( beginDate.day > eachDay[beginDate.month] || endDate.day > eachDay[endDate.month]+1 )
						{
							flag = 1;
							printf("%d �~ %d ��u�� %d ��A%d �~ %d ��u�� %d ��\n", beginDate.year, beginDate.month, eachDay[beginDate.month]\
							,endDate.year, endDate.month, eachDay[endDate.month]+1);
						}
					}
					
					else
						if( beginDate.day > eachDay[beginDate.month] || endDate.day > eachDay[endDate.month] )
						{
							flag = 1;
							printf("%d �~ %d ��u�� %d ��A%d �~ %d ��u�� %d ��\n", beginDate.year, beginDate.month, eachDay[beginDate.month]\
							,endDate.year, endDate.month, eachDay[endDate.month]);
						}		
							break;	
			}
				break;
		case 1:
			switch( endLeapCheck )
			{
				case 0:
					if( beginDate.month == 2 )
					{
						if( beginDate.day > eachDay[beginDate.month]+1 || endDate.day > eachDay[endDate.month] )
						{
							flag = 1;
							printf("%d �~ %d ��u�� %d ��A%d �~ %d ��u�� %d ��\n", beginDate.year, beginDate.month, eachDay[beginDate.month]+1\
							,endDate.year, endDate.month, eachDay[endDate.month]);
						}
					}
						
					else
						if( beginDate.day > eachDay[beginDate.month] || endDate.day > eachDay[endDate.month] )
						{
							flag = 1;
							printf("%d �~ %d ��u�� %d ��A%d �~ %d ��u�� %d ��\n", beginDate.year, beginDate.month, eachDay[beginDate.month]\
							,endDate.year, endDate.month, eachDay[endDate.month]);
						}		
							break;
				case 1:
//					�]����̬Ҭ��|�~�ҥH�����w��G�릳 0 0�B0 1�B1 0�B1 1 ���ˬd 
					if( endDate.month == 2 && beginDate.month == 2 )
					{
						if( beginDate.day > eachDay[beginDate.month]+1 || endDate.day > eachDay[endDate.month]+1 )
						{
							flag = 1;
							printf("%d �~ %d ��u�� %d ��A%d �~ %d ��u�� %d ��\n", beginDate.year, beginDate.month, eachDay[beginDate.month]+1\
							,endDate.year, endDate.month, eachDay[endDate.month]+1);
						}
					}
					
					else if( endDate.month == 2 && beginDate.month != 2 )
					{
						if( beginDate.day > eachDay[beginDate.month] || endDate.day > eachDay[endDate.month]+1 )
						{
							flag = 1;
							printf("%d �~ %d ��u�� %d ��A%d �~ %d ��u�� %d ��\n", beginDate.year, beginDate.month, eachDay[beginDate.month]\
							,endDate.year, endDate.month, eachDay[endDate.month]+1);
						}
					}
					
						else if( endDate.month != 2 && beginDate.month == 2 )
						{
							if( beginDate.day > eachDay[beginDate.month]+1 || endDate.day > eachDay[endDate.month] )
							{
								flag = 1;
								printf("%d �~ %d ��u�� %d ��A%d �~ %d ��u�� %d ��\n", beginDate.year, beginDate.month, eachDay[beginDate.month]+1\
								,endDate.year, endDate.month, eachDay[endDate.month]);
							}
						}
						
							else
								if( beginDate.day > eachDay[beginDate.month] || endDate.day > eachDay[endDate.month] )
								{
									flag = 1;
									printf("%d �~ %d ��u�� %d ��A%d �~ %d ��u�� %d ��\n", beginDate.year, beginDate.month, eachDay[beginDate.month]\
									,endDate.year, endDate.month, eachDay[endDate.month]);
								}		
									break;	
			}
				break;
	}
	
	if( flag == 1 )
		return flag;
		
	printf("���T��J\n");
	return flag;
}
