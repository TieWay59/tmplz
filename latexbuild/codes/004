
/* Author: bnfcc -> tc2000731 -> tieway59
 * Description:
 *      维护下凸包，对于每个x维护f(x)=k*x+b的最大值。
 *      query max value within all f(x) functions.
 *      c++11 features included.
 * Problems:
 *      https://nanti.jisuanke.com/t/41306
 *      https://nanti.jisuanke.com/t/41097
 */
template<typename var=long long, const int SIZE = 1000005, typename ldb=long double>
struct Hull {
    struct fx {
        var k, b;

        fx() {}

        fx(var k, var b) : k(k), b(b) {}

        var f(var x) { return k * x + b; }
    };

    int cnt;
    fx arr[SIZE];

    bool empty() {
        return cnt == 0;
    }

    void init() {
        cnt = 0;
    }

    void add(const fx &p) {
        arr[cnt++] = p;
    }

    void pop() {
        cnt--;
    }

    bool chek(const fx &a, const fx &b, const fx &c) {
        ldb ab, ak, bb, bk, cb, ck;
        tie(ab, ak, bb, bk, cb, ck) =
                tie(a.b, a.k, b.b, b.k, c.b, c.k);
        return (ab - bb) / (bk - ak) > (ab - cb) / (ck - ak);
    }

    void insert(const fx &p) {///k从小到大插入
        if (cnt && arr[cnt - 1].k == p.k) {
            if (p.b <= arr[cnt - 1].b)return;
            else pop();
        }
        while (cnt >= 2 && chek(arr[cnt - 2], arr[cnt - 1], p))pop();
        add(p);
    }

    /*var query(var x) {///x从大到小查询       从小到大用队列
        while (cnt > 1 && arr[cnt - 2].f(x) > arr[cnt - 1].f(x))pop();;
        return arr[cnt - 1].f(x);
    }*/

    var query(var x) {///二分查询，x顺序任意
        int l = 0, r = cnt - 1;
        while (l < r) {
            int mid = (l + r) >> 1;
            if (arr[mid].f(x) >= arr[mid + 1].f(x))r = mid;
            else l = mid + 1;
        }
        return arr[l].f(x);
    }
};

// vector stack
template<typename var=long long, const int SIZE = 1000005, typename ldb=long double>
struct Hull {
    struct Line {
        var k, b;

        Line() {}

        Line(var k, var b) : k(k), b(b) {}

        var f(var x) { return k * x + b; }
    };

    int cnt;
    vector <Line> con;//

    bool empty() {
        return cnt == 0;
    }

    void init(const int &n) {
        con.clear();
        if (n > con.capacity())con.reserve(n);
        cnt = 0;
    }

    void add(const Line &p) {
        con.emplace_back(p);
        cnt++;
    }

    void pop() {
        cnt--;
        con.pop_back();
    }

    bool chek(const Line &a, const Line &b, const Line &c) {
        ldb ab, ak, bb, bk, cb, ck;
        tie(ab, ak, bb, bk, cb, ck) =
                tie(a.b, a.k, b.b, b.k, c.b, c.k);
        return (ab - bb) / (bk - ak) > (ab - cb) / (ck - ak);
    }

    void insert(const Line &p) {///k从小到大插入
        if (cnt && con[cnt - 1].k == p.k) {
            if (p.b <= con[cnt - 1].b)return;
            else pop();
        }
        while (cnt >= 2 && chek(con[cnt - 2], con[cnt - 1], p))pop();
        add(p);
    }

    var query(var x) {///二分查询，x顺序任意
        int l = 0, r = cnt - 1;
        while (l < r) {
            int mid = (l + r) >> 1;
            if (con[mid].f(x) >= con[mid + 1].f(x))r = mid;
            else l = mid + 1;
        }
        return con[l].f(x);
    }
};

Hull<> hull;