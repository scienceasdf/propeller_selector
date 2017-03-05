#include<vector>
#include<algorithm>
#include<iostream>

#include<string>


#include<spline.h>
#include<objects.h>


int main()
{

    motor mt1(1100,.042);
    propulsion p1(21,60,mt1,2.0,1.0);

    p1.speed=22.0;
    p1.get_curve("PER3_15x4E.dat");
    std::cout<<p1.prop_name<<"\n";
    p1.run();
    std::cout<<p1.current<<"\t"<<p1.volt<<"\t"<<p1.thru<<"\t"<<p1.rot<<"\t"<<p1.eta<<"\t"<<p1.eta_motor<<"\n";
    p1.dynamic_run();
    std::cout<<p1.current<<"\t"<<p1.volt<<"\t"<<p1.thru<<"\t"<<p1.rot<<"\t"<<p1.eta<<"\t"<<p1.eta_motor<<"\n";
    return 0;

}
