/**
 *  @Source: https://zh.cppreference.com/w/cpp/language/parameter_pack
 *  @Complexity:
 *  @Description: 用cout模仿格式化输出
 *  @Example: see below
 *  @Verification: TODO
 */
void coutf(const char *format) {
    std::cout << format;
}

template<typename T, typename... Targs>
//void coutf(const char *format, T value, Targs... Fargs) // 递归变参函数
void coutf(const char *format, const T &value, const Targs &... Fargs) {
    for (; *format != '\0'; format++) {
        if (*format == '%') {
            std::cout << value;
            coutf(format + 1, Fargs...); // 递归调用
            return;
        }
        std::cout << *format;
    }
}

/*
void example(){
    coutf("% world% %\n", "Hello", '!', 123);
    cout.precision(9);
    fixed(cout);
    coutf("% % % %\n", 0x3f, 1.2 / 7, acos(-1), 22.3);
}
 */
