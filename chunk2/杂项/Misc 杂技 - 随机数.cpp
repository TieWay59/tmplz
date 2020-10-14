

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

inline int suiJi(const int &l, const int &r) {
return uniform_int_distribution<int>(l, r)(rng);
}