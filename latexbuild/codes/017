const string weekday[] = {
        "Sunday",
        "Monday",
        "Tuesday",
        "Wednesday",
        "Thursday",
        "Friday",
        "Saturday"
};

/**
 *  @Source: myself
 *  @Author: Tieway59
 *  @Complexity: $O(1)$
 *  @Description:
 *      y [1, 9999]
 *      m [1, 12]
 *      d [1, 31]
 *      return [0, 6]
 *
 *  @Example:
 *      KimLarsen(2020, 10, 11) == 6 (Sunday)
 *      KimLarsen(2020, 10, 12) == 0 (Monday)
 *
 *  @Verification:
 *      https://vjudge.net/solution/27715588
 *      cout << weekday[KimLarsen(2011, m, d)] << endl;
 *
 */
int KimLarsen(int y, int m, int d) {
    if (m == 1 || m == 2) {//一二月换算
        m += 12;
        y--;
    }
    return (d +
            2 * m + 3 * (m + 1) / 5 +
            y + y / 4 - y / 100 + y / 400 + 1) % 7;
}
