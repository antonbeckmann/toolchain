#include "TextTimer.hpp"
#include <fstream>


//#define DEBUG

using json = nlohmann::json;
using namespace std;

int TextTimer::loadData(std::string file)
{
//
// read sheduling file
//
//
    std::fstream fs;
    fs.open ("shedule.txt", std::fstream::in);

    if(!fs.is_open())
        return 1;
    

//
// get URL of the aktor which is controlled by the timer
//
//
#ifdef DEBUG
    fs >> url;
    std::cout<<"DEBUG:: URL "<<url<<"\n";// process pair (a,b)
#else
    fs >> url;
#endif

    if(url.size() == 0)
       std::cout << "URL " << url << " is not correct";

    int a, b;
    std::string desc;
    while (fs  >>desc >> a >> b)
    {
#ifdef DEBUG
        std::cout<<"DEBUG:: " << "desc:"<<desc<< " a:"<< a<<" b: "<< b<< "\n";// process pair (a,b)
#endif
        if(desc.compare("int") == 0)
        {
            intervals.push_back(Interval(a,b));
        }else if(desc.compare("spk") == 0)
        {
            spikes.push_back(Spike(a));
        }
        else
        {
            std::cout <<"shedule command unknown"<<std::endl;
        }        
    }
    fs.close();
    return 0;
}

int TextTimer::loadDataAsJson(std::string file)
{
//
// read sheduling file
//
//
    std::ifstream fs;
    fs.open ("shedule.json", std::fstream::in);

    if(!fs.is_open())
        return 1;

    json j;
    fs >> j;

    j.at("url").get_to(url);
    j.at("on_file").get_to(on_file);
    j.at("off_file").get_to(off_file);

    vector<vector<int> > i;
    j.at("intervals").get_to(i);
    for (int n = 0; n< i.size(); n++)
    { 
        tm s,e;
        s.tm_hour = i.at(n).at(0);
        s.tm_min = i.at(n).at(1);
        e.tm_hour = i.at(n).at(2);
        e.tm_min = i.at(n).at(3);
        
        
        intervals.push_back(
            Interval(s,e)
        );
    }

    vector<int> s;
    j.at("spikes").get_to(s);
    for (vector<int>::  iterator it = s.begin() ; it != s.end(); ++it)
    {
        spikes.push_back(*it);
    }

#ifdef DEBUG
    cout<<"url from Json "<<url<<endl;
    cout<<"on_file from Json "<<on_file<<endl;
    cout<<"off_file from Json "<<off_file<<endl;

    cout<<"intervals"<<endl;
    for (vector<Interval>::  iterator it = intervals.begin() ; it != intervals.end(); ++it)
    {
        std::cout << "start " << ( *it).starttm.tm_hour<<endl;
        std::cout << "      " << ( *it).starttm.tm_min<<endl;

        std::cout << "end   " << ( *it).endtm.tm_hour<<endl;
        std::cout << "      " << ( *it).endtm.tm_min<<endl;
    }

    cout<<"spikes"<<endl;
    for (vector<Spike>::  iterator it = spikes.begin() ; it != spikes.end(); ++it)
    {
        std::cout << "start " << ( *it).start<<endl;
    }
#endif


    //create output in releay
    string cmd= "curl -v -d @" + off_file +" -H \"Content-Type: application/json\" "+url+"/leds";
    const char *command = cmd.c_str(); 
    system(command);

}
Interval TextTimer::getinterval(int i)
{
    if(i<0)
        return Interval(0,0);
    if(i >= intervals.size())
        return Interval(0,0);
    
    return intervals.at(i);
}

void TextTimer::processTime(int hour, int min)
{
    for(int i = 0; i < intervals.size(); i++)    
        {
            if(intervals.at(i).starttm.tm_hour == hour && (intervals.at(i).starttm.tm_min == min ))
            {
                cout<<turnOn()<<endl;
            }   
            if(intervals.at(i).endtm.tm_hour == hour && (intervals.at(i).endtm.tm_min == min ))
            //if(intervals.at(i).end == time)
            {
                cout<<turnOff()<<endl;
            }
        }      
}

string TextTimer::turnOn()
{
                if(OnOff)
                    return string(" +++ relay is allready ON");
                
#ifdef DEBUG               
                string cmd= "curl -v -d @" + on_file +" -H \"Content-Type: application/json\" -X PUT "+url+"/leds";
#else
                string cmd= "curl -d @" + on_file +" -H \"Content-Type: application/json\" -X PUT "+url+"/leds";
#endif
                const char *command = cmd.c_str(); 
                system(command);
                OnOff = true;
                return string(" +++ turn relay on");
}

string TextTimer::turnOff()
{
                if(!OnOff)
                    return string(" +++ relay is allready OFF");;
#ifdef DEBUG                
                string cmd= "curl -v -d @" + off_file +" -H \"Content-Type: application/json\" -X PUT "+url+"/leds";
#else
                string cmd= "curl -d @" + off_file +" -H \"Content-Type: application/json\" -X PUT "+url+"/leds  > /dev/null";
#endif                
                const char *command = cmd.c_str(); 
                system(command);
                OnOff = false; 
                return string(" --- turn relay off");
}
