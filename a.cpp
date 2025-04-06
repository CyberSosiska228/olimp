#include <bits/extc++.h>

signed main() {
    int n, m;
    std::cin >> n >> m;
    std::cout << std::max(0, m - n + 1) << '\n';

    return 0;
}
