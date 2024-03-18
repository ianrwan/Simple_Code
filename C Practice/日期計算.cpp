#include<stdio.h>
#include<stdlib.h>

#define MONTH_TOTAL 12

typedef struct // 日期存放 
{
	int year;
	short int month;
	short int day;
}DATE;

short int leapYear( int ); // 判斷閏年 
short int beginDateCalculate( DATE ); // 開始日期計算 
short int endDateCalculate( DATE ); // 結束日期計算 
short int noCrossYear( DATE, DATE); // 未跨年分日期計算 
short int correctInput( DATE, DATE ); // 確定輸入沒有錯誤 

short int eachDay[MONTH_TOTAL+1] = {0,31,28,31,30,31,30,31,31,30,31,30,31}; // 各個月份日期 

int main(void)
{
//	年分相差、總天數 
	int yearDifference, dayTotal = 0;
//	閏年判斷、輸入正確與否判斷 
	short int leapCheck, checkPoint; 

	DATE beginDate, endDate;
	
	do
	{
		printf("請輸入開始年月日（以空格分割，例：2022 10 10）: ");
		scanf("%d %d %d", &beginDate.year, &beginDate.month, &beginDate.day);
	
		printf("請輸入結束年月日（以空格分割，例：2023 10 10）: ");
		scanf("%d %d %d", &endDate.year, &endDate.month, &endDate.day);
		
		putchar('\n');
		
//		判斷輸入是否正確 
		checkPoint = correctInput( beginDate, endDate);
		
		if( checkPoint )
		{
			printf("請重新輸入\n");
			putchar('\n');
		}
		
	}while( checkPoint );
	
//	年分相差 
	yearDifference = endDate.year - beginDate.year;
	
//	年份為零進到無跨年函式 
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
	
	printf("兩日期相差天數（含第一天）：%d 天\n", dayTotal);
	printf("兩日期相差天數（不含第一天）：%d 天\n", dayTotal-1);
	
	system("pause");
}

short int leapYear( int year )
{
//	0 代表平年、1 代表閏年

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
//	閏年判斷、月份相差、日期計算 
	short int leapCheck, monthDifference, monthAdd = 0;
	
	leapCheck = leapYear(date.year);
	monthDifference = 12 - date.month;
	
//	計算月份總和，不含第一月份 
	for( short int i = 12 ; i > 12-monthDifference ; i-- )
	{
		if( i != 2 )
			monthAdd += eachDay[i];
		else
			( !leapCheck ) ? monthAdd += eachDay[i] : monthAdd = monthAdd + eachDay[i] + 1; 
	}
	
//	已總和日期 + 第一月份日期  
	if( date.month == 2 && leapCheck )
		monthAdd = monthAdd + eachDay[date.month] + 1 - date.day + 1; // +1 使日期變為 29 -date.day 將日期減掉 +1 減掉要補回來 
	else
		monthAdd = monthAdd + eachDay[date.month] - date.day + 1;
	
	return monthAdd;
}

short int endDateCalculate( DATE date )
{
// 	閏年判斷、月份相差、日期計算 
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
// 	閏年判斷、月份相差、日期計算 
	short int leapCheck, monthDifference, monthAdd = 0;
	
	leapCheck = leapYear( beginDate.year );
	monthDifference = endDate.month - beginDate.month;
	
//	相差等於 0 可直接計算 
	if( monthDifference == 0 )
		monthAdd = endDate.day-beginDate.day+1;
		
	else
	{
//		判斷起始是否為 2 月閏年 
		if( leapCheck && beginDate.month == 2 )
		{
//			計算開始月即截止月的總和 
			monthAdd =  (eachDay[beginDate.month] + 1 - beginDate.day + 1) + endDate.day;
			
//			中間月份計算 
			for( int i = 2 ; i <= monthDifference ; i++ )
				monthAdd += eachDay[beginDate.month+i-1]; 
		}
			
		
		else
		{
//			計算開始月即截止月的總和 
			monthAdd =  (eachDay[beginDate.month] - beginDate.day + 1) + endDate.day;
			
//			中間月計算 
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

//	檢查輸入 
short int correctInput( DATE beginDate, DATE endDate )
{
//	flag 0 為輸入錯誤，1 為輸入正確、開始年閏年判斷、截止年閏年判斷 
	int flag = 0, beginLeapCheck, endLeapCheck;
	
//	判斷開始和結束的時間是否相反 
	if( endDate.year < beginDate.year)
	{
		flag = 1;
		printf("結束年份不可以小於開始年份\n");
	}
	
	else if( endDate.year == beginDate.year )
	{
		if( endDate.month < beginDate.month )
		{
			flag = 1;
			printf("結束月份不可以小於開始月份\n");
		}
		
		else if( endDate.month == beginDate.month )
		{
			if( endDate.day < beginDate.day )
			{
				flag = 1;
				printf("結束日期不可以小於開始日期\n");
			}
		}
	}
	
//	正整數判斷 
	if( beginDate.year <= 0 || beginDate.month <= 0 || beginDate.day <= 0 || endDate.year <= 0 || endDate.month <= 0 || endDate.day <= 0 )
	{
		flag = 1;
		printf("請輸入正整數\n");
	}
	
//	月份檢查 
	if( beginDate.month > 12 || endDate.month > 12 )
	{
		flag = 1;
		printf("一年最多只有 12 個月\n");
	}
	
//	前項錯誤需修正才作後項檢查 
	if( flag == 1 )
		return flag;
	
	beginLeapCheck = leapYear(beginDate.year);
	endLeapCheck = leapYear(endDate.year);

//	日期檢查 
	switch( beginLeapCheck )
	{
		case 0:
			switch( endLeapCheck )
			{
				case 0:
					if( beginDate.day > eachDay[beginDate.month] || endDate.day > eachDay[endDate.month] )
					{
						flag = 1;
						printf("%d 年 %d 月只有 %d 日，%d 年 %d 月只有 %d 日\n", beginDate.year, beginDate.month, eachDay[beginDate.month]\
						,endDate.year, endDate.month, eachDay[endDate.month]);
					}
						break;
				case 1:
					if( endDate.month == 2 )
					{
						if( beginDate.day > eachDay[beginDate.month] || endDate.day > eachDay[endDate.month]+1 )
						{
							flag = 1;
							printf("%d 年 %d 月只有 %d 日，%d 年 %d 月只有 %d 日\n", beginDate.year, beginDate.month, eachDay[beginDate.month]\
							,endDate.year, endDate.month, eachDay[endDate.month]+1);
						}
					}
					
					else
						if( beginDate.day > eachDay[beginDate.month] || endDate.day > eachDay[endDate.month] )
						{
							flag = 1;
							printf("%d 年 %d 月只有 %d 日，%d 年 %d 月只有 %d 日\n", beginDate.year, beginDate.month, eachDay[beginDate.month]\
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
							printf("%d 年 %d 月只有 %d 日，%d 年 %d 月只有 %d 日\n", beginDate.year, beginDate.month, eachDay[beginDate.month]+1\
							,endDate.year, endDate.month, eachDay[endDate.month]);
						}
					}
						
					else
						if( beginDate.day > eachDay[beginDate.month] || endDate.day > eachDay[endDate.month] )
						{
							flag = 1;
							printf("%d 年 %d 月只有 %d 日，%d 年 %d 月只有 %d 日\n", beginDate.year, beginDate.month, eachDay[beginDate.month]\
							,endDate.year, endDate.month, eachDay[endDate.month]);
						}		
							break;
				case 1:
//					因為兩者皆為閏年所以必須針對二月有 0 0、0 1、1 0、1 1 的檢查 
					if( endDate.month == 2 && beginDate.month == 2 )
					{
						if( beginDate.day > eachDay[beginDate.month]+1 || endDate.day > eachDay[endDate.month]+1 )
						{
							flag = 1;
							printf("%d 年 %d 月只有 %d 日，%d 年 %d 月只有 %d 日\n", beginDate.year, beginDate.month, eachDay[beginDate.month]+1\
							,endDate.year, endDate.month, eachDay[endDate.month]+1);
						}
					}
					
					else if( endDate.month == 2 && beginDate.month != 2 )
					{
						if( beginDate.day > eachDay[beginDate.month] || endDate.day > eachDay[endDate.month]+1 )
						{
							flag = 1;
							printf("%d 年 %d 月只有 %d 日，%d 年 %d 月只有 %d 日\n", beginDate.year, beginDate.month, eachDay[beginDate.month]\
							,endDate.year, endDate.month, eachDay[endDate.month]+1);
						}
					}
					
						else if( endDate.month != 2 && beginDate.month == 2 )
						{
							if( beginDate.day > eachDay[beginDate.month]+1 || endDate.day > eachDay[endDate.month] )
							{
								flag = 1;
								printf("%d 年 %d 月只有 %d 日，%d 年 %d 月只有 %d 日\n", beginDate.year, beginDate.month, eachDay[beginDate.month]+1\
								,endDate.year, endDate.month, eachDay[endDate.month]);
							}
						}
						
							else
								if( beginDate.day > eachDay[beginDate.month] || endDate.day > eachDay[endDate.month] )
								{
									flag = 1;
									printf("%d 年 %d 月只有 %d 日，%d 年 %d 月只有 %d 日\n", beginDate.year, beginDate.month, eachDay[beginDate.month]\
									,endDate.year, endDate.month, eachDay[endDate.month]);
								}		
									break;	
			}
				break;
	}
	
	if( flag == 1 )
		return flag;
		
	printf("正確輸入\n");
	return flag;
}
