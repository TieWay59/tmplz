const int days_of_month[] = {
        0, // 可以指定保留[0] = 0
        31, 28, 31, 30,
        31, 30, 31, 31,
        30, 31, 30, 31
};

bool isLeapYear(int year) {
    return year % 4 == 0 &&
           year % 100 > 0 ||
           year % 400 == 0;
}

int getMonthDays(int y, int m) {
    return days_of_month[m] + int(m == 2 && isLeapYear(y));
}