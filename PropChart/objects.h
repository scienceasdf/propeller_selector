#ifndef OBJECTS_H
#define OBJECTS_H

#include<string>
#include<vector>
#include<cmath>
#include<fstream>
#include<sstream>

class propeller{
public:
    double diameter;    // The unit is meter
    std::string prop_name;
    int count;
    std::vector<double> n;  // Revolution, the unit of n is 1/s
    std::vector<std::vector<double>> J_curve;
    std::vector<std::vector<double>> Pe_curve;
    std::vector<std::vector<double>> Ct_curve;
    std::vector<std::vector<double>> Cp_curve;

    propeller() :count(0){}
    ~propeller() {}

    void clearCurve();
    void getCurve(std::string&& path);
    void getCurve(std::string path);

    inline int nearest(double RPM){
        RPM=RPM/60.0;
        if(RPM<n[0]) return 0;
        if(RPM>n[count-1]) return (count-2);
        for(int i=0;i<count;++i){
            if((n[i]<=RPM) && (n[i+1]>RPM)){
                return ((fabs(RPM-n[i])<fabs(RPM-n[i+1]))?i:(i+1));
            }
        }
    }

    inline int between(double RPM, double speed){
        double J=speed/(RPM/60.0)/diameter;
        int k=nearest(RPM);
        if(J==.0) return 0;

        int sz=J_curve[k].size();
        if(J>J_curve[k][sz-1]) return (sz-2);
        for(int i=0;;++i){
            if((J_curve[k][i]<=J) && (J_curve[k][i+1]>J))
                return i;
        }

    }

    double thrust_on_RPM(double RPM, double speed);
    double eta_on_RPM(double RPM, double speed);
    double power_on_RPM(double RPM, double speed);
    double RPM_on_power(double power, double speed);
    double thrust_on_power(double power, double speed);
    double eta_on_power(double power, double speed);
};

#endif // OBJECTS_H
