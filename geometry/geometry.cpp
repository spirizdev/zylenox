template<class T> struct Point {
    T x, y;
    Point(T _x=0, T _y=0):x(_x), y(_y) {}
    template<class U> operator Point<U>() {
        return Point<U>(U(x), U(y));
    }
    Point &operator+=(Point p) {
        x+=p.x;
        y+=p.y;
        return *this;
    }
    Point &operator-=(Point p) {
        x-=p.x;
        y-=p.y;
        return *this;
    }
    Point &operator*=(T v) {
        x*=v;
        y*=v;
        return *this;
    }
    Point &operator/=(T v) {
        x/=v;
        y/=v;
        return *this;
    }
    Point operator-() const {
        return Point(-x, -y);
    }
    friend Point operator+(Point a, Point b) {
        return a+=b;
    }
    friend Point operator-(Point a, Point b) {
        return a-=b;
    }
    friend Point operator*(Point a, T v) {
        return a*=v;
    }
    friend Point operator*(T v, Point a) {
        return a*=v;
    }
    friend Point operator/(Point a, T v) {
        return a/=v;
    }
    friend bool operator==(Point a, Point b) {
        return a.x==b.x and a.y==b.y;
    }
    friend istream& operator>>(istream& in, Point& p) {
        return in>>p.x>>p.y;
    }
    friend ostream& operator<<(ostream& out, Point p) {
        return out<<p.x<<' '<<p.y;
    }
};
template<class T> db len(Point<T> a, Point<T> b) {
    return (a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y);
}
template<class T> T dot(Point<T> a, Point<T> b) {
    return a.x*b.x+a.y*b.y;
}
template<class T> T cross(Point<T> a, Point<T> b) {
    return a.x*b.y-a.y*b.x;
}
template<class T> T dot(Point<T> a, Point<T> b, Point<T> c) {
    return dot(b-a, c-a);
}
template<class T> T cross(Point<T> a, Point<T> b, Point<T> c) {
    return cross(b-a, c-a);
}
template<class T> T square(Point<T> a) {
    return dot(a, a);
}
template<class T> double length(Point<T> p) {
    return sqrt(square(p));
}
long double length(Point<long double> p) {
    return sqrt(square(p));
}
template<class T> Point<T> normalize(Point<T> p) {
    return p/length(p);
}
template<class T> T manhattan(Point<T> a, Point<T> b) {
    return abs(a.x-b.x)+abs(a.y-b.y);
}
template<class T> int sign(T x) {
    return (x==0?0:(x<0?-1:1));
}
//segment AB, point C
template<class T> bool onSegment(Point<T> a, Point<T> b, Point<T> c) {
    return cross(a-c, b-c)==0 and dot(a-c, b-c)<=0;
}
//segment AB, CD
template<class T> bool intersect(Point<T> a, Point<T> b, Point<T> c, Point<T> d) {
    return onSegment(a, b, c) or onSegment(a, b, d) or onSegment(c, d, a) or onSegment(c, d, b) or
           (sign(cross(a, b, c))*sign(cross(a, b, d))<0 and sign(cross(c, d, a))*sign(cross(c, d, b))<0);
}
using point=Point<long long>;
template<class T> struct Line {
    T a, b, c; //ax+by+c=0
    Line(Point<T> A, Point<T> B) {
        a=B.y-A.y;
        b=A.x-B.x;
        c=-A.x*B.y+A.y*B.x;
    }
    Line(T _a=0, T _b=0, T _c=0) {
        a=_a, b=_b, c=_c;
    }
    T func(T x, T y) {
        return a*x+b*y+c;
    }
    friend istream& operator>>(istream& in, Line& d) {
        return in>>d.a>>d.b>>d.c;
    }
};
//line AB, point C
template<class T> long double LineToPoint(Point<T> a, Point<T> b, Point<T> c) {
    return abs(cross(a, b, c))/length(a-b);
}
//line AB, point C
template<class T> long double LineToPoint(Line<T> d, Point<T> p) {
    return abs(d.func(p.x, p.y))/sqrt(d.a*d.a+d.b*d.b);
}
using line=Line<long long>;
//line AB, CD
template<class T> bool parallel(Point<T> a, Point<T> b, Point<T> c, Point<T> d) {
    Line<T> d1(a, b), d2(c, d);
    return (d1.a*d2.b==d1.b*d2.a);
}
//ray AB, point C
template<class T> long double RayToPoint(Point<T> a, Point<T> b, Point<T> c) {
    return (dot(a, b, c)>=0?LineToPoint(a, b, c):min(length(a-c), length(b-c)));
}
// line L, segment AB
template<class T> bool intersectLineSegment(Line<T> L, Point<T> a, Point<T> b) {
    T fa = L.func(a.x, a.y);
    T fb = L.func(b.x, b.y);
    return fa * fb <= 0;
}
