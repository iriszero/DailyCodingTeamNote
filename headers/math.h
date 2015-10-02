//
//  math.h
//  DailyCodingTeamNote
//
//  Created by IRIS on 9/7/15.
//  Copyright (c) 2015 IRIS. All rights reserved.
//
#include <stdio.h>
#include <math.h>
#include <vector>

using namespace std;

bool isPrime(int n);
bool isPrime(int n, vector<int> v);
vector<int> getPrimes(int n);

vector<pair<int, int>> factorize(int n);
vector<pair<int, int>> factorize(int n, vector<int> v);



template<typename T>
T gcd(T a, T b) {
    return (b==0)? a: gcd(b, a%b);
}
// U must cover T
template<typename T, typename U>
U lcm(T a, T b) {
    return a / gcd(a,b ) * (U)b;
}


bool isPrime(int n) {
    return isPrime(n, getPrimes((int)sqrt(n)));
}
bool isPrime(int n, const vector<int> v) {
    for (auto now : v) {
        if (n % now == 0) return false;
    }
    return true;
}

//Verified in range of (0, 10^6) at least
vector<int> getPrimes(int N) {
    vector<int> ret;
    
    if (N>=2) ret.push_back(2);
    if (N>=3) ret.push_back(3);
    
    int i,j,k;
    
    bool ctn = true;
    int mid_point = (int)sqrt(N-1) / 6 + 1;
    
    for (i=1; ctn && i<= mid_point ; i++) {
        for (j=-1; j<=1; j+=2) {
            int now = i * 6 + j;
            
            if (now > sqrt(N)) {
                ctn = false;
                break;
            }
            
            bool flag = true;
            for (auto here : ret) {
                if (now % here == 0) {
                    flag = false;
                    break;
                }
                
            }
            if (flag) {
                ret.push_back(now);
            }
        }
    }
    
    ctn = true;
    
    int ret_sqrt_cnt = (int)ret.size();
    for (i=mid_point-2; ctn && i<= (N-1)/ 6 + 1; i++) {
        for (j=-1; j<=1; j+=2) {
            int now = i*6 + j;
            if (now <= ret[ret_sqrt_cnt-1]) continue;
            if (now > N) {
                ctn = false;
                break;
            }
            
            bool flag = true;
            for (k=0; k<ret_sqrt_cnt; k++) {
                if (now % ret[k] == 0) {
                    flag = false;
                    break;
                }
            }
            if (flag) {
                ret.push_back(now);
            }
        }
    }
    return ret;
}


//return <prime number, power_cnt>
//ex) N = 12 / return vector<pair<2, 2>, pair<3, 1>>
vector<pair<int, int>> factorize(int N) {
    auto primes=getPrimes(sqrt(N)+5);
    return factorize(N, primes);
    
}
vector<pair<int, int>> factorize(int N, vector<int> primes) {
    vector<pair<int, int>> ret;
    
    for (auto p : primes) {
        int c=0;
        while (N % p == 0) {
            N /= p;
            c++;
        }
        if (c>0) ret.push_back(make_pair(p, c));
    }
    
    if (N > 1) ret.push_back(make_pair(N, 1));
    
    return ret;
}

int main(void) {
    
    return 0;
}