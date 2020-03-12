#ifndef TEXTTIME_H
#define TEXTTIME_H
#include <iostream>
#include <string>
#include <vector>
#include "nlohmann/json.hpp"
#include <time.h>


struct Interval
{
    int start;
    int end;
    tm starttm;
    tm endtm;
    Interval(int s, int e):start(s),end(e){}
    Interval(tm s, tm e):starttm(s),endtm(e){}
};

struct Spike
{
    int start;
    Spike(int s):start(s){}
};

class TextTimer
{
    public:
        void sayHello() {std::cout<<"Say hello\n";}
        int loadData(std::string file);
        int loadDataAsJson(std::string file);
        int getIntervalsSize(){return intervals.size();};
        Interval getinterval(int i);
        void processTime(int hour,int min);
        std::string turnOn();
        std::string turnOff();

    private:        
        std::vector<Interval> intervals;
        std::vector<Spike> spikes;
        std::string url;
        std::string on_file;
        std::string off_file;
        bool OnOff;
        
        
};
#endif