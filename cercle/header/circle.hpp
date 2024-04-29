#ifndef CIRCLE
#define CIRCLE

#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <string>
#include <pugixml.hpp>
#define _USE_MATH_DEFINES

class readfile{
protected:
struct Point{
    Point(int x,int y):x(x),y(y) {};
    int get(const std::string a){
        int b;
        if(a=="x") b=x;
        if(a=="y") b=y;
        return b;
    }
    private:
        int x;
        int y;
};
private:
bool readxml(std::vector<Point> &input,std::vector<Point> &input1);
void writexml(std::vector<Point> &result);
public:
std::vector<Point> result,c;
std::vector<std::pair<int,int>> sercle;
bool geometry(std::vector<Point> &c,std::vector<std::pair<int,int>> &sercle, const int flag);
};

class logica:readfile{
private:
void equationline(const int &x1,const int &y1,const int &x,const int &y,int &a,int &b,int &c);
bool circle_line_intersection(const int &x1,const int &y1,const int &x,const int &y,const int &x4,const int &y4,const int &r);
bool two_circle_intersection(const int &x1,const int &x,const int &y1,const int &y,const int &r2,const int &r4);
bool circle_intersection_rectangle(std::vector<Point> &X,const int &x1,const int &y1,const int &r);
public:
std::vector<Point> logical(std::vector<Point> &c,const std::vector<std::pair<int,int>> &sercle,bool &calculation);
};

class graphicasa:readfile{
public:
int save(std::vector<Point> &c,std::vector<Point> &result,const std::vector<std::pair<int,int>> &sercle);
};
#endif