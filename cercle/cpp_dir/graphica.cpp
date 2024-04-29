#include "../header/circle.hpp"

/*!
  * \brief save  Функция для рисования зоны расстановки и окружностей в полученных точках,а также функция сохраняет полученное изображение в виде картинки
  * \param c Вектор точек образующих прямоугольники
  * \param result Вектор положения окружностей
  * \param sercle Вектор радиусов окружностей
  * \return 0
  */
int graphicasa::save(std::vector<Point> &c, std::vector<Point> &result,const std::vector<std::pair<int,int>> &sercle){
    sf::RenderTexture texture;
    float x1=0.0,y1=0.0,x2=0.0,y2=0.0;
    double f1;
    int i=0,i2=1,i3=0,i4=1,r=0,size;
    //Создание векторов для вывода фигур
    sf::Vertex line[(c.size()*2)],cercle[(result.size()*2)*100],Point[result.size()];
    size=c.size()/4;
    texture.create(1000, 1000);
    //Цикл для расчета пропорции положения прямоугольников в пикселях.
    for(r=0;r<size;r=r+1){
        i2=(r*4)+1;
        for(i=0;i<4;i=i+1){
            if(i==3)i2=r*4;
            line[i3]=sf::Vertex(sf::Vector2f(((50+(c[i+(r*4)].get("x")*4))+450),(100-((c[i+(r*4)].get("y"))*4))+450));
            line[i4]=sf::Vertex(sf::Vector2f(((50+(c[i2].get("x")*4))+450),((100-((c[i2].get("y"))*4))+450)));
            i2=i2+1;
            i3=i3+2;
            i4=i4+2;
        }
    }
        i4=0;
        i=0;
        i2=0;
        i3=0;
        //Цикл для расчета пропорции положения окружностей
        for(i=0;i<(result.size()*2);i=i+1){
            y2=(i/2.0);
            x2=modf(y2,&f1);
            if(x2==0.0)r=sercle[i3].first*4;//4;
            if(x2==0.5)r=sercle[i3].second*4;//4;
            x1=0.0;
            for(i2=0;i2<100;i2=i2+1){
                y1=x1*(M_PI/180.0);
                cercle[i2+(i*100)]=sf::Vertex(sf::Vector2f(float((50+(result[i3].get("x")*4)+450)+(r*cos(y1))),float((100-(result[i3].get("y")*4)+450)+(r*sin(y1)))));
                x1=x1+3.6;
            }
            if(x2==0.5)i3=i3+1;
        }
        i=0;
        //Цикл для расчета пропорции положения точек цента окружностей
        for(i=0;i<result.size();i=i+1){
            Point[i]=sf::Vertex(sf::Vector2f(float(50+(result[i].get("x")*4)+450),float(100-(result[i].get("y")*4)+450)));
        }
        texture.clear();
        texture.draw(Point,result.size(),sf::Points);
        texture.draw(line,c.size()*2,sf::Lines);
        texture.draw(cercle,((result.size()*2)*100),sf::Points);
        texture.display();
    //Функция для сохранения изображения
    texture.getTexture().copyToImage().saveToFile("new_file.png");
    return 0;
}
