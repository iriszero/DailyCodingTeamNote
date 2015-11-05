//
//  fraction.h
//  DailyCodingTeamNote
//
//  Created by IRIS on 10/12/15.
//  Copyright (c) 2015 IRIS. All rights reserved.
//

#pragma once
#include "math.h"
/*NOTE
1. All operation ALWAYS returns value of which denominator is POSITIVE.
2. BE AWARE OF OVERFLOW!
 */

template <typename T>
class Fraction {
public:

    T x, y; // x over y, y SHOULD NOT BE 0
    Fraction() { }
    ~Fraction() { }
    Fraction(T x) {
        this->x = x;
        this->y = 1;
    }
    Fraction(T x, T y) {
        this->x = x;
        this->y = y;
        init();
    }
    void init() { //make y (denominator) POSTIIVE
        if (this->y < 0) {
            this->x *= -1;
            this->y *= -1;
        }
    }

    Fraction<T> operator+ (const Fraction& f) const {
        T g = abs(gcd(this->y, f.y));
        
        T _y = (this->y / g) * f.y;
        T _x = this->x * (_y / this->y) + f.x * (_y / f.y);
        
        T _g = abs(gcd(_x, _y));
        
        return Fraction<T>(_x / _g, _y / _g);
        
    }
    Fraction<T> operator- (const Fraction<T>& f) const {
        return (*this) + Fraction(-f.x, f.y);
    }
    Fraction<T> operator* (const Fraction<T>& f) const {
        
        return Fraction<T>(
                          (this->x / abs(gcd(this->x, f.y)) ) * (f.x / abs(gcd(this->y, f.x))),
                          (this->y / abs(gcd(this->y, f.x)) ) * (f.y / abs(gcd(this->x, f.y)))
                        );
    }
    Fraction<T> operator/ (const Fraction<T>& f) const {
        return (*this) * Fraction( f.y, f.x);
    }
    bool operator== (const Fraction<T>& f) const {
        return ( this->x * f.y == this->y * f.x);
    }
    bool operator== (const T other) const {
        return ( this-> x == other * this->y);
    }
    bool operator!= (const Fraction<T> f) const {
        return ! ( (*this) == f);
    }
    bool operator!= (const T other) const {
        return !  ( (*this) == other);
    }
    void operator+= (const Fraction<T>& f) {
        Fraction<T> result =  (*this) + f;
        this->x = result.y;
        this->y = result.y;
    }
    void operator-= (const Fraction<T>& f) {
        Fraction<T> result = (*this) -f ;
        this->x = result.x;
        this->y = result.y;
    }
    void operator*= (const Fraction<T>& f) {
        Fraction<T> result = (*this) * f;
        this->x = result.x;
        this->y = result.y;
    }
    void operator/= (const Fractoin<T>& f) {
        Fraction<T> result = (*this)/ f;
        this->x = result.x;
        this->y = result.y;
    }
};
