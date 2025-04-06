#include <bits/extc++.h>
#define int long long

int f2(int ln, std::vector<int> &v, int n) {
    int res = 0;
    if (n == ln) {
        return 1;
    }

    for (int i = v[n] + 1; i <= 9; i++) {
        v.push_back(i);
        res += f2(ln, v, n + 1);
        v.pop_back();
    }

    return res;
}


int f(int ln1, int ln2, std::vector<int> &v, int n) {
    int res = 0;
    if (n == ln1) {
        return f2(ln2, v, n);
    }

    if (n == 0) {
        for (int i = 1; i < 9; i++) {
            v.push_back(i);
            res += f(ln1, ln2, v, n + 1);
            v.pop_back();
        }
    } else {
        for (int i = v[n - 1] - 1; i >= 0; i--) {
            v.push_back(n);
            res += f(ln1, ln2, v, n + 1);
            v.pop_back();
        }
    }
    return res;
}


int f4(std::string s, std::vector<int> &v, int n) {
    int res = 0;
    if (n == size(s)) {
        return 1;
    }

    for (int i = v[n] + 1; i < s[n] - '0'; i++) {
        v.push_back(i);
        res += f4(s, v, n + 1);
        v.pop_back();
    }

    if (s[n] - '0' >= v[n] + 1) {
        v.push_back(s[n] - '0');
        res += f4(s, v, n + 1);
        v.pop_back();
    }

    return res;
}


int f3(int ln, std::string s, std::vector<int> &v, int n) {
    int res = 0;
    if (n == ln) {
        return f4(s, v, n);
    }

    if (n == 0) {
        for (int i = 1; i < s[n] - '0'; i++) {
            v.push_back(i);
            res += f(ln, size(s), v, n + 1);
            v.pop_back();
        }
        v.push_back(s[n] - '0');
        res += f3(ln, s, v, n + 1);
        v.pop_back();
    } else {
        for (int i = std::min((int) v[n - 1] - 1, (int) (s[n] - '0') - 1); i >= 0; i--) {
            v.push_back(i);
            res += f(ln, size(s), v, n + 1);
            v.pop_back();
        }
        if (s[n] - '0' <= v[n - 1] - 1) {
            v.push_back(s[n] - '0');
            res += f3(ln, s, v, n + 1);
            v.pop_back();
        }
    }
    return res;
}

signed main() {
    std::string n;
    std::cin >> n;

    int res = 0;
    std::vector<int> v;

    for (int i = 3; i < size(n); i++) {
        for (int j = 2; j < i; j++) {
            res += f(j, i, v, 0);
        }
    }

    for (int i = 2; i < size(n); i++) {
        res += f3(i, n, v, 0);
    }

    std::cout << res << '\n';
    return 0;
}
