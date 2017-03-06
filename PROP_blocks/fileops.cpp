#include<sstream>
#include<fstream>
#include<string>
#include<iostream>
#include<vector>
#include<objects.h>

void trim(std::string &s)
{

    if( !s.empty() )
    {
        s.erase(0,s.find_first_not_of(" "));
        s.erase(s.find_last_not_of(" ") + 1);
    }

}

void getAll(std::vector<std::string>& list,
            double minThrust,
            double minDynamicThrust,
            double minEtaProp,
            double minEtaTotal,
            propulsion& p1)
{
    std::stringstream ss1;
    std::ifstream index("E:\\database\\PER2_TITLEDAT.txt");
    std::string file;

    std::getline(index,file);
    std::getline(index,file);
    std::getline(index,file);
    std::getline(index,file);

    while(std::getline(index,file)){
            //Trim(file,iter1);
            trim(file);
            ss1.clear();
            ss1.str(file);
            ss1>>file;

            p1.get_curve(file);
            p1.run();
            if(p1.thru>minThrust){
                p1.dynamic_run();
                if(p1.thru>minDynamicThrust && p1.eta>minEtaTotal &&p1.eta_prop()>minEtaProp){
                    list.push_back(p1.prop_name);
                }
            }
    }
}
