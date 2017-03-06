#include<vector>
#include<algorithm>
#include<iostream>
#include <chrono>
#include<string>


#include<spline.h>
#include<objects.h>
#include<fileops.h>

int main()
{
    auto start = std::chrono::system_clock::now();
    motor mt1(220,.042);
    propulsion p1(12.5,10,mt1,1.0,1.0);
    std::vector<std::string> s1;

    p1.speed=7.0;

    getAll(s1,10,.0,.5,.6,p1);
    int i=0;
    std::vector<std::string>::iterator iter=s1.begin();
    for(;iter!=s1.end();++iter){
        std::cout<<(*iter)<<"\t"<<i<<"\n";
        ++i;
    }

    auto end   = std::chrono::system_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    std::cout <<  "Duration time is "
         << double(duration.count()) * std::chrono::microseconds::period::num / std::chrono::microseconds::period::den
         << " seconds" << std::endl;
    return 0;

}
