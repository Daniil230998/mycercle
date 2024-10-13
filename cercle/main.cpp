#include "circle.hpp"

int main(){
    object read;
    int i;
    bool calculation,r;
    std::cout<<"Read from file ..\n";
    r=read.geometry(read.c,read.sercle,1);
    std::cout<<"Read from file end\n";
    if(r==true){
    // правда 1, ложь 0
    std::cout<<"Calculation start\n";
    read.result=read.logical(read.c,read.sercle,calculation);
    if(calculation==true){
    std::cout<<"Calculation completed successfully\n";
    std::cout<<"Save image ..\n";
    read.save(read.c,read.result,read.sercle);
    std::cout<<"Save image succesfull\n";
    } else {
        std::cout<<"error\n";
    }
    read.geometry(read.result,read.sercle,2);
    } else {
        std::cout<<"error input data\n";
    }
    read.c.clear();
    read.result.clear();
    read.sercle.clear();
}
