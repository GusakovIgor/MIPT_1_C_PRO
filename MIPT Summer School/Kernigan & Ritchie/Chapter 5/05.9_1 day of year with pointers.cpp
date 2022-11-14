/* Day of year */
/* Calculating day of the year from current month and day of month*/
#include <stdio.h>

int      year_table[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};    // Days per month for not leap year
int leap_year_table[] = {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};    // Days per month for leap year
int*  num_day_table[] = { year_table, leap_year_table };

void day_of_year (int year, int month, int* mday);

int main()
    {
    int day = 0;
    int month = 0;
    int year = 0;
    printf("Please enter date:\n");
    printf("Day: "  ); scanf("%d", &day);
    printf("Month: "); scanf("%d", &month);
    printf("Year: " ); scanf("%d", &year);

    day_of_year (year, month, &day);

    return 0;
    }

void day_of_year (int year, int month, int* mday)
    {
    int leap = (year % 4 == 0) && (year % 100 != 0) || (year % 400 == 0);

    for (int i = 1; i < month; i++)
        *mday += *(*(num_day_table + leap) + i);

    printf ("There is %d day of the year", *mday);
    }
