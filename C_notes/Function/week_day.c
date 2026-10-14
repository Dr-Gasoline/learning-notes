int week_day(int year,int month,int day)
 {
 int century, weekday;
 if(month < 3)
 {
 year--;
 month += 12;
 }
 century = year/ 100;
 year %= 100;
 // Zeller formula
 weekday = (year+ year/4 + century/4-2*century +(26*(month+1))/10 + day-1) % 7;
 if(weekday<0)
 weekday+=7;

 return weekday;//0==Sunday
}   
