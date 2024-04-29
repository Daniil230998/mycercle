#include "../header/circle.hpp"

/*!
  * \brief equationline Функция для расчета коэффициентов уравнения прямой
  * \param x1 Координата первой точки по оси x, которая образует прямую линию
  * \param y1 Координата первой точки по оси y, которая образует прямую линию
  * \param x Координата второй точки по оси x, которая образует прямую линию
  * \param y Координата второй точки по оси y, которая образует прямую линию
  * \param a коэффициент a уравнения для заданной прямой
  * \param b коэффициент b уравнения для заданной прямой
  * \param c коэффициент c уравнения для заданной прямой
  * \return a,b,c
*/
//Функция для расчета кооэффициентов уравнения прямой
void logica::equationline(const int &x1,const int &y1,const int &x,const int &y,int &a,int &b,int &c){
    int y3,x3;
    y3 = y - y1;
    x3 = x1 - x;

    if (x == x1) {
        a = y3;
        b = (y1 * (-1)) * x3;
        c = (x1 * (-1)) * y3;
    }
    if (y == y1) {
        b = x3;
        a = (x1 * (-1)) * y3;
        c = (y1 * (-1)) * x3;
    }
}

/*!
  * \brief circle_line_intersection Функция для расчета пересечение окружности с контуром фигуры
  * \param x1 Координата первой точки по оси x, которая образует прямую линию
  * \param y1 Координата первой точки по оси y, которая образует прямую линию
  * \param x Координата второй точки по оси x, которая образует прямую линию
  * \param y Координата второй точки по оси y, которая образует прямую линию
  * \param x4 Координата центра окружности по оси x
  * \param y4 Координата центра окружности по оси y
  * \param r Внутренний радиус окружности
  * \return true если окружность пересекает прямую, false если не пересекает
  */
//Функция circle_line_intersection позволяет вычислить пересечение окружности с контуром фигуры
bool logica::circle_line_intersection(const int &x1,const int &y1,const int &x,const int &y,const int &x4,const int &y4,const int &r) {
    int d=0, a=0, b=0, c=0;//, x3=0, y3=0;
    bool f=false;
    equationline(x1,y1,x,y,a,b,c);
    //Формула для вычисления расстояния между прямой и центром окружности
    d = ((abs(((a * x4) + (b * y4) + c))) / (sqrt(pow(a, 2) + pow(b, 2))));
    if(r<d)f=false;
    if(r==d)f=true;
    if(r>d)f=true;
    return f;
}

/*!
  * \brief two_circle_intersection  Функция для определения пересекаются две окружности или нет
  * \param x1 Координата первой окружности по оси x
  * \param x Координата второй окружности по оси x
  * \param y1 Координата первой окружности по оси y
  * \param y Координата второй окружности по оси y
  * \param r2 Радиус первой окружности
  * \param r4 Радиус второй окружности
  * \return true если окружности пересекаются, false если не пересекаются
  */
bool logica::two_circle_intersection(const int &x1,const int &x,const int &y1,const int &y,const int &r2,const int &r4) {
    int d;
    bool f=false;
    //Формула вычисления расстояния между окружностями
    d = sqrt(pow((x1 - x), 2) + pow((y1 - y), 2));
    //Если расстояние между центрами меньше чем сумма радиусов, или равна им значит есть пересечение
    if (d < (r2 + r4))f = true;
    if (d == (r2 + r4))f = true;
    if ((d + r2) == r4)f = true;
    if (d<(r4-r2) || (d+r2)<r4)f = true;
    return f;
}

/*!
  * \brief circle_intersection_rectangle Функция для проверки пересечения окружности с прямоугольной зоной исключения
  * \param X Вектор точек образующих зоны исключения
  * \param x1 Координата по оси x центра окружности
  * \param y1 Координата по оси y центра окружности
  * \param r Радиус окружности
  * \return true если окружность пересекает любую зону исключения, false если не пересекает
  */
bool logica::circle_intersection_rectangle(std::vector<Point> &X,const int &x1,const int &y1,const int &r){
 bool d=false;
 int i,i2,i3,d1=0,size=0,i5;
 int d0=0, a=0, b=0, c=0, x3=0, y3=0,d2=0,x2=0,y2=0;
 i3=1;
 i=4;
 i2=5;
 //Расчет количества зон исключения. Этот парамутр нужен для цикла
 d1=(X.size()-4)/4;
 //Цикл проверки того что окружность не находится внутри зоны исключения
 while(i3<=d1){
    i=0;

    i2=(i3*4)+1;
          equationline(X[i2].get("x"),X[i2].get("y"),X[i+(i3*4)+3].get("x"),X[i+(i3*4)+3].get("y"),a,b,c);
            x3=X[i+(i3*4)+3].get("y")+(y1*(-1));
            y3=X[i2].get("y")+(y1*(-1));
            x2=X[i+(i3*4)+3].get("x")+(x1*(-1));
            y2=X[i2].get("x")+(x1*(-1));
          if(((x3>=0 && y3<=0) || (x3<=0 && y3>=0))&& ((x2>=0 && y2<=0)||(x2<=0 && y2>=0))){
              size=size+1;
          }
          i3=i3+1;
  }
 //Если окружность не находинтся внутри не одной из зон исключения. Значит проверяется есть ли пересечения контура с одной из зон
 if(size==0){
i=0;
i2=5;
i3=1;

   while(i3<=d1){
    i=0;
    //Расчет номера первой точки прмоугольной зоны
    i2=(i3*4)+1;
    //Цикл проверки есть ли пересечение с одной из зон исключения
  while(i<4){
        d=false;
        //Если номер точки равен 3 значит нужно взять 0 точку
        if(i==3)i2=i3*4;
          equationline(X[i2].get("x"),X[i2].get("y"),X[i+(i3*4)].get("x"),X[i+(i3*4)].get("y"),a,b,c);
          //Условия для расчета находится ли точки в пределах прямой линии по оси x или y
          if(X[i2].get("x")==X[(i)+(i3*4)].get("x")){
            x3=X[(i)+(i3*4)].get("y")+(y1*(-1));
            y3=X[i2].get("y")+(y1*(-1));
          }
          if(X[i2].get("y")==X[(i)+(i3*4)].get("y")){
            x3=X[(i)+(i3*4)].get("x")+(x1*(-1));
            y3=X[i2].get("x")+(x1*(-1));
          }
          //Если точка находится в пределах прямой по одной из координат значит мы можем просто вычислить расстояние до прямой.
          //Если нет то расчет происходит для оси x и y по отдельности
          if(((x3>=0 && y3<=0) || (x3<=0 && y3>=0))){
            x2 = ((abs(((a * x1) + (b * y1) + c))) / (sqrt(pow(a, 2) + pow(b, 2))));
            if(x2<=r) d=true;
          } else {
             x2=sqrt(pow((X[i2].get("x")-x1), 2) + pow((X[i2].get("y")-y1), 2));
             y2=sqrt(pow((X[(i3*4)+i].get("x")-x1), 2) + pow((X[(i3*4)+i].get("y")-y1), 2));
              if(x2<=r || y2<=r) d=true;
          }

        i=i+1;
        i2=i2+1;
        if(d==1)break;
 }
  //Проверка если есть пересечение с любой из сторон прямоугольника, то происходит выход из цикла
  if(d==1)break;
i3=i3+1;
          }
 } else {
     //Данное условие выполняется если окружность находится внутри одной из зон исключения.
     d=true;
 }
 return d;
}

/*!
  * \brief logical Функция для расчета положения окружностей на заданной фигуре
  * \param c Вектор точек образующих прямоугольники и зоны исключения
  * \param sercle Вектор внешних и внутренних радиусов окружностей
  * \param calculation Флаг успешности расчета
  * \return вектор расположения коружностей и флаг успешности расчета
  */
 std::vector<readfile::Point> logica::logical(std::vector<Point> &c,const std::vector<std::pair<int,int>> &sercle,bool &calculation){
    std::vector<Point> result;
    bool d,d1,d2;
    int x0,y0,rin,rout,i,i2,i1,i3,i4,l,l1;

    l=abs(c[0].get("x")-c[2].get("x"));
    l1=abs(c[0].get("y")-c[2].get("y"));
    for(i4=0;i4<sercle.size();i4=i4+1){
        x0=c[1].get("x");
        y0=c[1].get("y");
        rin=sercle[i4].first;
        rout=sercle[i4].second;
        i3=0;
        i1=0;
        i=0;
        d=false;
        while(i3<l1){
            if((d==1 || d1==1 || d2==1) || (d==1 && d1==1 && d2==1)){
                y0=y0-1;
                d=false;
                d1=false;
                d2=false;
                x0=c[1].get("x");
            }
            i1=0;
            while(i1<l){
                i=0;
                i2=1;
                while(i<4){
                    if(i==3)i2=0;
                    d=circle_line_intersection(c[i].get("x"),c[i].get("y"),c[i2].get("x"),c[i2].get("y"),x0,y0,rin);
                    if(d==1)break;
                    i2=i2+1;
                    i=i+1;
                }
                i=0;
            
                //цикл проверки пересечения кругов
                while(i<result.size()){
                    d1=two_circle_intersection(x0,result[i].get("x"),y0,result[i].get("y"),rout,sercle[i].second);
                    if(d1==1)break;
                    i=i+1;
                }
                //Проверка пересекает ли внутренний радиус окружности зону исключения
                d2=circle_intersection_rectangle(c,x0,y0,rin);

                if((d==1 || d1==1 || d2==1) || (d==1 && d1==1 && d2==1))x0=x0+1;
                i1=i1+1;
            }
            i3=i3+1;
        }
       if(d==0 && d1==0 && d2==0){
         calculation=true;
         result.push_back(Point(x0,y0));
       } else {
         calculation=false;
         break;
       }
    }
    return result;
}
