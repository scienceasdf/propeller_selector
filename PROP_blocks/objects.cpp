#include<string>
#include<iostream>
#include<objects.h>
#include<spline.h>
#include<omp.h>

inline bool RPM_line(std::string::iterator& iter)
{
     // The line is like " PRO PRPM =       10000"
     if(*iter=='P'){
        ++iter;
        if(*iter=='R') return true;
     }
     return false;
}

void propulsion::run()
{   
    double Km=30.0/mot.Kv/3.14159265358;
    double rev=mot.Kv*U_ub/gear_rto;

    double moment,power;
    power=p_curve.getPos(rev);
    moment=torque_curve.getPos(rev);


    double i=moment/Km/gear_rto/eta_gear;
    volt=i*mot.Ra+rev/mot.Kv*gear_rto;
    while( (volt>U_ub) || (i>I_ub) ){
        rev-=100.0;
        power=p_curve.getPos(rev);

        moment=torque_curve.getPos(rev);

        i=moment/Km/gear_rto/eta_gear;
        volt=i*mot.Ra+rev/mot.Kv*gear_rto;
    }
    if(i<0){
        current=.0;
        rot=.0;
        thru=.0;
        eta=.0;
        eta_motor=.0;
        volt=.0;
    }
    else{
        current=i;
        eta_motor=power/current/volt;
        thru=thrust_curve.getPos(rev);
        eta=.0;
        rot=rev;
    }
}

void propulsion::dynamic_run()
{
    double Km=30.0/mot.Kv/3.14159265358;
    double rev=mot.Kv*U_ub/gear_rto;
    //rev=std::max(rev,dynamic_torque_curve.vecX[0]);
    double x=mot.Kv/Km;
    double moment,power;
    power=dynamic_p_curve.getPos(rev);
    moment=dynamic_torque_curve.getPos(rev);
    //std::cout<<moment<<"bb\n";

    double i=moment/Km/gear_rto/eta_gear;
    volt=i*mot.Ra+rev/mot.Kv*gear_rto;
    while( (volt>U_ub) || (i>I_ub) ){
        rev-=100.0;
        power=dynamic_p_curve.getPos(rev);

        moment=dynamic_torque_curve.getPos(rev);

        i=moment/Km/gear_rto/eta_gear;
        volt=i*mot.Ra+rev/mot.Kv*gear_rto;
    }
    if(i<0){
        current=.0;
        rot=.0;
        thru=.0;
        eta=.0;
        eta_motor=.0;
        volt=.0;
    }
    else{
        current=i;
        eta_motor=moment*rev/30.0*3.14159265358/current/volt;
        thru=dynamic_thrust_curve.getPos(rev);
        eta=speed*thru/current/volt;
        rot=rev;
    }
}

void propulsion::get_curve(std::string fileName)
{
    static std::ifstream fin;
    static std::string line;
    static std::string::iterator iter1;
    static std::stringstream stream;
    //These static varibles can reduce the construction cost

    bool last_interpolated=true;

    double jk1;
    static double n[46];
    static double power[46];
    static double torque[46];
    static double thrust[46];
    static double dynamic_power[46];
    static double dynamic_torque[46];
    static double dynamic_thrust[46];
    int counter=0;
    int sz=0;
    std::string temp;
    bool charFlag=false;

    double v,v1,v2,p1,p2,thru1,thru2,tor1,tor2,dis;

    fin.open("E:\\database\\"+fileName);
    counter=0;
    if(!fin.is_open()){
        //std::cout << "Error opening file";
    }
    else{

        /*std::getline(fin,line);
        stream.clear();
        stream.str(line);
        stream>>prop_name;*/
        fin>>prop_name;

        while(std::getline(fin,line)){

            charFlag=false;
            sz=line.size();
            if(sz>1) iter1=line.begin();
            while(sz>1 && (!charFlag)){
                //iter1=line.begin();
                if((*iter1)!=' '){
                    charFlag=true;
                }
                else{
                    iter1=line.erase(iter1);
                    sz--;
                }

            }
            if(charFlag){
                if(RPM_line(iter1)){
                    if((!last_interpolated)){
                        dynamic_power[counter]=.0;
                        dynamic_thrust[counter]=.0;
                        dynamic_torque[counter]=.0;
                        ++counter;
                    }

                    stream.clear();
                    stream.str(line);
                    stream>>temp>>temp>>temp>>n[counter];
                    last_interpolated=false;
                }

                if(isdigit(*iter1)){
                    stream.clear();
                    stream.str(line);

                    stream>>v;
                    v*=.44704;
                    if(v==.0){
                        stream>>jk1>>jk1>>jk1>>jk1>>power[counter]>>torque[counter]>>thrust[counter];
                        p2=power[counter];
                        thru2=thrust[counter];
                        tor2=torque[counter];
                        v2=.0;
                    }

                    else{
                        p1=p2;
                        thru1=thru2;
                        tor1=tor2;
                        stream>>jk1>>jk1>>jk1>>jk1>>p2>>tor2>>thru2;
                        v1=v2;
                        v2=v;
                        if((v1<speed) && (speed<v2)){
                            dis=(speed-v1)/(v2-v1);
                            dynamic_power[counter]=(p2-p1)*dis+p1;
                            dynamic_torque[counter]=(tor2-tor1)*dis+tor1;
                            dynamic_thrust[counter]=(thru2-thru1)*dis+thru1;
                            ++counter;
                            last_interpolated=true;
                        }

                    }
                }
            }
        }

        //#pragma omp parallel for num_threads(4)
        for(int i=0;i<counter;++i){
            power[i]*=735;
            torque[i]*=0.11298;
            thrust[i]*=4.45;
            dynamic_power[i]*=735;
            dynamic_torque[i]*=.11298;
            dynamic_thrust[i]*=4.45;
        }


        p_curve.clear();
        thrust_curve.clear();
        torque_curve.clear();

        dynamic_p_curve.clear();
        dynamic_thrust_curve.clear();
        dynamic_torque_curve.clear();

        p_curve.addPoint(.0,.0);
        thrust_curve.addPoint(.0,.0);
        torque_curve.addPoint(.0,.0);

        //#pragma omp parallel for num_threads(4)
        for(int i=0;i<counter;++i){
            p_curve.addPoint(n[i],power[i]);
            thrust_curve.addPoint(n[i],thrust[i]);
            torque_curve.addPoint(n[i],torque[i]);
            if(dynamic_thrust[i]!=0){
                dynamic_p_curve.addPoint(n[i],dynamic_power[i]);
                dynamic_thrust_curve.addPoint(n[i],dynamic_thrust[i]);
                dynamic_torque_curve.addPoint(n[i],dynamic_torque[i]);
            }
        }

        fin.close();
    }
}

double propulsion::eta_prop()
{
    return ((eta/eta_gear)/eta_motor);
}
