#include <iostream>
#include <climits>

extern "C" int app_main( void )
{    
    using namespace std;
    int n_int = INT_MAX;        
    short n_short = SHRT_MAX;   
    long n_long = LONG_MAX;
    long long n_llong = LLONG_MAX;
    
    cout << "ESP32 limits:" << endl;
    cout << "int is " << sizeof (int) << " bytes." << endl;
    cout << "short is " << sizeof n_short << " bytes." << endl;
    cout << "long is " << sizeof n_long << " bytes." << endl;
    cout << "long long is " << sizeof n_llong << " bytes." << endl;
    cout << endl;
    cout << "Maximum values:" << endl;
    cout << "int: " << n_int << endl;
    cout << "short: " << n_short << endl;
    cout << "long: " << n_long << endl;
    cout << "long long: " << n_llong << endl << endl;
    cout << "Minimum int value = " << INT_MIN << endl;
    cout << "Bits per byte = " << CHAR_BIT << endl;
    cout << "Char max = " << CHAR_MAX << endl;

    return 0;
}
