#include "../header/circle.hpp"

/*!
  * \brief geometry Функция для расчета всех четырех точек образующих зону расстоновки и зоны исключения
  * \param c Вектор точек образующих зону расстановки и зону исключения
  * \param sercle Вектор окружностей
  * \param flag Флаг для выполнения записи или чтения из xml файла
  * \return true если удалось выполнить чтение из файла или запись в файл, false если не удалось
  */

bool readfile::geometry(std::vector<readfile::Point> &c,std::vector<std::pair<int,int>> &sercle,const int flag){
    int i=0,x=0,y=0,n=0;
    std::vector<Point> input,input1;
    bool r=true;
    if(flag==1){
    r=readxml(input,input1);
    if(r==true) {
    n=input.size()/2;
    for(i=0;i<n;i=i+1){
    x=abs(input[(i*2)+1].get("x")-input[i*2].get("x"));
    y=abs(input[(i*2)+1].get("y")-input[i*2].get("y"));
    //Условия для проверки последовательности значений и ввод данных значений в вектор фигры.
    //Значения могут быть поданны в поредке левый нижний угол, правый верхний или левый верхний правый нижний.
    if(input[i*2].get("x")<input[(i*2)+1].get("x") && input[i*2].get("y")>input[(i*2)+1].get("y")){
       c.push_back(Point(input[i*2].get("x"),input[i*2].get("y")-y));
       c.push_back(Point(input[i*2].get("x"),input[i*2].get("y")));
       c.push_back(Point(input[i*2].get("x")+x,input[i*2].get("y")));
       c.push_back(Point(input[i*2].get("x")+x,abs(input[i*2].get("y"))-y));
    }
    if(input[i*2].get("x")<input[(i*2)+1].get("x") && input[i*2].get("y")<input[(i*2)+1].get("y")){
       c.push_back(Point(input[i*2].get("x"),input[i*2].get("y")));
       c.push_back(Point(input[i*2].get("x"),input[i*2].get("y")+y));
       c.push_back(Point(input[i*2].get("x")+x,input[i*2].get("y")+y));
       c.push_back(Point(input[i*2].get("x")+x,input[i*2].get("y")));
    }
    }
    i=0;
    n=n*4;
    i=0;
    for(i=0;i<input1.size();i=i+1){
    sercle.push_back(std::make_pair(input1[i].get("x"),input1[i].get("y")));
    }

    }
    } else if (flag==2){
        writexml(c);
    }
    return r;
}

/*!
  * \brief readxml Функция чтения из xml файла
  * \param input Вектор точек образующих зоны исключения и границы зоны расстановки
  * \param input1 Вектор внутренних и внешних радиусов окружностей
  * \return true если удалось считать данные и если они коректные
  */
bool readfile::readxml(std::vector<Point> &input,std::vector<Point> &input1){
       pugi::xml_document doc;
       int x,y,x1,y1;
       int inner_rad,outter_rad;
       bool r=true;
       pugi::xml_parse_result result = doc.load_file("../input.xml");
       if (!result)
           exit;

       pugi::xpath_node_set tools_with_timeout1 = doc.select_nodes("/data/placement_zone/rect");

       pugi::xpath_node_set tools_with_timeout = doc.select_nodes("/data/placement_zone/alarms/alarms");
       pugi::xpath_node_set tools_with_timeout2 = doc.select_nodes("/data/circles/circle");

       for (pugi::xpath_node node1: tools_with_timeout1)
       {
           pugi::xml_node tool1 = node1.node();
           x=tool1.child("min_point").attribute("x").as_int();
           y=tool1.child("min_point").attribute("y").as_int();
           x1=tool1.child("max_point").attribute("x").as_int();
           y1=tool1.child("max_point").attribute("y").as_int();
           if(x>x1){
               r=false;
               break;
           }
           input.push_back(Point(x,y));
           input.push_back(Point(x1,y1));
       }
       if(r==true){
       for (pugi::xpath_node node: tools_with_timeout)
       {
           pugi::xml_node tool = node.node();
           x=tool.child("min_point").attribute("x").as_int();
           y=tool.child("min_point").attribute("y").as_int();
           x1=tool.child("max_point").attribute("x").as_int();
           y1=tool.child("max_point").attribute("y").as_int();
           if(x>x1){
               r=false;
               break;
           }
           input.push_back(Point(x,y));
           input.push_back(Point(x1,y1));
       }
       for (pugi::xpath_node node2: tools_with_timeout2)
       {
            pugi::xml_node tool2 = node2.node();
           inner_rad=tool2.attribute("inner_rad").as_int();
           outter_rad=tool2.attribute("outter_rad").as_int();
           if(inner_rad==0 || outter_rad==0){
           r=false;
           break;
           }
           input1.push_back(Point(inner_rad,outter_rad));
       }
       }
       return r;
}

/*!
  * \brief writexml Функция для записи результатов в xml файл
  * \param result Вуктор содержащий информацию о найденных расположениях окружностей
  * \return true если окружность пересекает любую зону исключения, false если не пересекает
  */
void readfile::writexml(std::vector<Point> &result){
    int i;
 pugi::xml_document doc;

 pugi::xml_node root1=doc.append_child("data");
 pugi::xml_node declarationNode=root1.append_child("circles");
 for(i=0;i<result.size();i=i+1){
 pugi::xml_node declarationNode1=declarationNode.append_child("circle");
 declarationNode1.append_attribute("id")=i;
 declarationNode1.append_attribute("x")=result.at(i).get("x");
 declarationNode1.append_attribute("y")=result.at(i).get("y");
 }
 
bool saveSucceeded = doc.save_file("../output.xml",PUGIXML_TEXT("  "));
}
