#include "TextTimer.hpp"
#include <iostream>
#include <chrono>
#include <thread>
#include <time.h>

// for convenience

using namespace std;
int main(int argc, char** argv)
{
    TextTimer tt;
    tt.sayHello();
    tt.loadDataAsJson("shedule.json");
    
    int time_ = 0;
    bool running = true;
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    
    
    while(running)
    {
        time_t Zeitstempel;
        tm *nun;
        Zeitstempel = time(0);
        nun = localtime(&Zeitstempel);
        cout<<nun->tm_hour
            << ':' << nun->tm_min << endl;
    
        tt.processTime(nun->tm_hour,nun->tm_min);  
 //       time_++;
        std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        if(time_ > 110) 
          running = false;
        std::cout<<"time "<<time_<<std::endl;
    }

    return 0;
}