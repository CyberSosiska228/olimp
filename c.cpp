#include <bits/extc++.h>
#define int __int128

const int INF = std::numeric_limits<int>::max();

int pw(int n, int pw) {
    int res = 1;
    for (int i = 0; i < pw; ++i) {
        res *= n;
    }
    return res;
}

std::istream &operator>>(std::istream &in,int &num) {
    std::string str;
    in >> str;
    int n = str.size();
    num = 0;
    for (int i = 0 + (str.front() == '-'); i < n; ++i) {
        num += int(str[i] - '0') * pw(10, n - i - 1);
    }
    num *= (str.front() == '-' ? -1 : 1);
    return in;
}

std::ostream &operator<<(std::ostream &out, const int &num) {
    std::string str;
    int x = num;
    if (x == 0) {
        str = "0";
    }
    while (x > 0) {
        str.push_back((char) (x % 10 + '0'));
        x /= 10;
    }
    std::reverse(str.begin(), str.end());
    out << str;
    return out;
}


struct node {
    int th, a, b, c, d;

    node() {
        a = b = c = d = 0;
        th = -1;
    }
    node(int _th, int _a, int _b, int _c, int _d) {
        th = _th;
        a = _a;
        b = _b;
        c = _c;
        d = _d;
    }

    bool operator==(node &oth) {
        return (th == oth.th && a == oth.a && b == oth.b && c == oth.c && d == oth.d);
    }
};


void minmax1(int x, int &mx1, int &mx2) {
    if (mx1 < x) {
        mx2 = mx1;
        mx1 = x;
    } else if (mx2 < x) {
        mx2 = x;
    }
}

void minmax2(int x, int &mn1, int &mn2) {
    if (x == 0) {
        return;
    }

    if (mn1 > x) {
        mn2 = mn1;
        mn1 = x;
    } else if (mn2 > x) {
        mn2 = x;
    }
}


void setup(std::vector<std::vector<int>> &g, std::vector<int> &mon, std::vector<node> &sal, int n) {
    for (int i = 0; i < size(g[n]); i++) {
        setup(g, mon, sal, g[n][i]);
    }

    int mx1, mx2, mn1, mn2;
    mx1 = mx2 = -INF;
    mn1 = mn2 = INF;

    for (int i = 0; i < size(g[n]); i++) {
        int k = g[n][i];
        minmax1(sal[k].th, mx1, mx2);
        minmax2(sal[k].th, mn1, mn2);
        minmax1(sal[k].a, mx1, mx2);
        minmax1(sal[k].b, mx1, mx2);
        minmax2(sal[k].c, mn1, mn2);
        minmax2(sal[k].d, mn1, mn2);
    }

    if (mn1 == INF) {
        mn1 = 0;
    }
    if (mn2 == INF) {
        mn2 = 0;
    }

    if (size(g[n]) > 0) {
        sal[n] = node(mon[n], mx1, mx2, mn1, mn2);
    } else {
        sal[n] = node(mon[n], 0, 0, 0, 0);
    }
}

void upd(std::vector<int> &par, std::vector<std::vector<int>> &g, std::vector<node> &sal, int n) {
    do {
        int mx1, mx2, mn1, mn2;
        mx1 = mx2 = -INF;
        mn1 = mn2 = INF;

        for (int i = 0; i < size(g[n]); i++) {
            int k = g[n][i];
            minmax1(sal[k].th, mx1, mx2);
            minmax2(sal[k].th, mn1, mn2);
            minmax1(sal[k].a, mx1, mx2);
            minmax1(sal[k].b, mx1, mx2);
            minmax2(sal[k].c, mn1, mn2);
            minmax2(sal[k].d, mn1, mn2);
        }

        if (mn1 == INF) {
            mn1 = 0;
        }
        if (mn2 == INF) {
            mn2 = 0;
        }


        node newv;
        if (size(g[n]) > 0) {
            newv = node(sal[n].th, mx1, mx2, mn1, mn2);
        } else {
            newv = node(sal[n].th, 0, 0, 0, 0);
        }

        if (sal[n] == newv) {
            return;
        }

        sal[n] = newv;
        n = par[n];
    } while (par[n] != n);
}


signed main() {
    int n;
    std::cin >> n;
    std::vector<std::vector<int>> g(n);
    std::vector<int> par(n, 0);
    std::vector<node> sal(n);
    std::vector<int> mon(n);

    for (int i = 1; i < n; i++) {
        int x;
        std::cin >> x;
        if (i != x - 1) {
            g[x - 1].push_back(i);
        }
        par[i] = x - 1;
    }


    for (int i = 0; i < n; i++) {
        std::cin >> mon[i];
    }

    for (int i = 0; i < n; i++) {
        if (sal[i].th == -1) {
            setup(g, mon, sal, i);
        }
    }

    for (int i = 0; i < n; i++) {
        node k = sal[i];
        //std::cout << k.th << ' ' << k.a << ' ' << k.b << ' ' << k.c << ' ' << k.d << '\n';
    }

    int q;
    std::cin >> q;
    while (q--) {
        int t;
        std::cin >> t;
        if (t == 1) {
            int x;
            std::cin >> x;
            x--;
            std::cout << (sal[x].a + sal[x].b - sal[x].c - sal[x].d);
            std::cout << '\n';
        } else {
            int x, d;
            std::cin >> x >> d;
            x--;
            sal[x].th += d;
            sal[x].a += d;
            sal[x].b += d;
            sal[x].c += d;
            sal[x].d += d;
            upd(par, g, sal, par[x]);
        }
    }
    for (auto i : par) {
        //std::cout << i << ' ';
    }
    //std::cout << '\n';
    for (int i = 0; i < n; i++) {
        node k = sal[i];
    //    std::cout << k.th << ' ' << k.a << ' ' << k.b << ' ' << k.c << ' ' << k.d << '\n';
    }


    return 0;
}
