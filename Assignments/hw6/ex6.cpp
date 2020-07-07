#include <iostream>
using namespace std;

long long f(long long a, long long n)
{
    long long temp = a * a + 1;
    temp = temp % n;
    return temp;
}

long long gcd(long long a, long long b)
{
    if(b == 0) return a;
    return gcd(b, a % b);
}

int main()
{
    long long n;
    cout << "Input n: ";
    cin >> n;
    cout << "= ";
    if (n > 1){
        while (1){
            long long a = 2, b = 2, d = 1;
            while (d == 1){
                a = f(a, n);
                long long temp = f(b, n);
                b = f(temp, n);
                if (a > b){
                    d = gcd(a-b, n);
                }
                else{
                    d = gcd(b-a, n);
                }
            }
            if (d == n){
                cout << d;
                break;
            } else{
                cout << d <<"*";
                n /= d;
            }
        }
    }
    cout << endl;
    return 0;
}