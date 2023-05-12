#ifdef NOERROR
#define PRINTERR(msg)
#else
#define PRINTERR(msg)          \
    cerr << "\033[1;31m";      \
    cerr << "[ERROR] " << msg; \
    cerr << "\033[0m" << endl
#endif

#ifdef NOHINT
#define PRINTHINT(msg)
#else
#define PRINTHINT(msg)         \
    cerr << "\033[0;35m";      \
    cerr << "  HINT: " << msg; \
    cerr << "\033[0m" << endl
#endif

#define PRINT(msg) \
    cout << msg << endl
