#include<objects.h>
#include<iostream>
#include<QCoreApplication>

inline bool RPM_line(std::string::iterator& iter)
{
     // The line is like " PRO PRPM =       10000"
     if(*iter=='P'){
        ++iter;
        if(*iter=='R') return true;
     }
     return false;
}




inline double linearInter(double x1, double x2, double y1, double y2, double x)
{
    return (x==x1)?y1:((y2-y1)/(x2-x1)*(x-x1)+y1);
}

double propeller::eta_on_RPM(double RPM, double speed)
{
    int i=nearest(RPM);
    int k=between(RPM,speed);
    double J=speed/(RPM/60.0)/diameter;
    double Pe=linearInter(J_curve[i][k],J_curve[i][k+1],Pe_curve[i][k],Pe_curve[i][k+1],J);
    return Pe;
}

double propeller::power_on_RPM(double RPM, double speed)
{
    int i=nearest(RPM);
    int k=between(RPM,speed);
    double J=speed/(RPM/60.0)/diameter;
    double Cp=linearInter(J_curve[i][k],J_curve[i][k+1],Cp_curve[i][k],Cp_curve[i][k+1],J);
    return (1.225*pow(diameter,5)*pow(RPM/60.0,3)*Cp);
}

double propeller::thrust_on_RPM(double RPM, double speed)
{
    if(RPM==0) return 0;
    int i=nearest(RPM);
    int k=between(RPM,speed);
    double J=speed/(RPM/60.0)/diameter;
    double Ct=linearInter(J_curve[i][k],J_curve[i][k+1],Ct_curve[i][k],Ct_curve[i][k+1],J);
    return (Ct>0)?(1.225*pow(diameter,4)*pow(RPM/60.0,2)*Ct):0;
}


double propeller::RPM_on_power(double power, double speed)
{
    double y0=.0,y1=.0;
    int i;
    y1=power_on_RPM(n[0]*60.0,speed);
    for(i=1;i<count-1;++i){
        y0=y1;
        y1=power_on_RPM(n[i]*60.0,speed);
        //std::cout<<n[i]<<"\n";
        if(y0<=power && y1>=power) break;
    }
    if(i>=count-1) return 0;    // It means it is beyond the upper RPM limits
    --i;
    double RPM=n[i]*60.0;
    //y0=power_on_RPM(n[i],speed);
    i=0;
    for(;;RPM+=50.0){
        y0=y1;
        y1=power_on_RPM(RPM,speed);
        ++i;
        if(y0<=power && y1>=power) break;
        if(i==40) return 0.0;
    }
    return RPM;
}

double propeller::eta_on_power(double power, double speed)
{
    double RPM=RPM_on_power(power,speed);
    return eta_on_RPM(RPM,speed);

}

double propeller::thrust_on_power(double power, double speed)
{
    double RPM=RPM_on_power(power,speed);
    return thrust_on_RPM(RPM,speed);

}

void propeller::clearCurve()
{
    if(count){
        for(int i=0;i<count;++i){
            Pe_curve[i].clear();
            Cp_curve[i].clear();
            Ct_curve[i].clear();
            J_curve[i].clear();
        }

        Pe_curve.clear();
        Cp_curve.clear();
        Ct_curve.clear();
        J_curve.clear();
        n.clear();
        count=0;
    }
}

void propeller::getCurve(std::string&& path)
{
    clearCurve();

    static std::ifstream fin;
    static std::string line;
    static std::string::iterator iter1;
    static std::stringstream stream;

    double jk1,Cp,Ct,Pe,J,n1;
    std::string temp;
    bool charFlag=false;
    size_t sz;

    path=QCoreApplication::applicationDirPath().toStdString()+"\\database\\"+path;
    fin.open(path);
    count=0;
    if(!fin.is_open()){
        std::cout << "Error opening file";
    }
    else{

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
                    stream.clear();
                    stream.str(line);
                    stream>>temp>>temp>>temp>>n1;
                    n.push_back(n1/60.0);
                    count++;
                    Cp_curve.push_back(std::vector<double>());
                    Ct_curve.push_back(std::vector<double>());
                    Pe_curve.push_back(std::vector<double>());
                    J_curve.push_back(std::vector<double>());
                }

                if(isdigit(*iter1)){
                    stream.clear();
                    stream.str(line);

                    stream>>jk1>>J>>Pe>>Ct>>Cp>>jk1>>jk1>>jk1;

                    J_curve[count-1].push_back(J);
                    Cp_curve[count-1].push_back(Cp);
                    Ct_curve[count-1].push_back(Ct);
                    Pe_curve[count-1].push_back(Pe);
                }
            }
        }
    }

        stream.str(prop_name);
        stream>>diameter;
        diameter=diameter*.0254;
        fin.close();

}

void propeller::getCurve(std::string path)
{
    clearCurve();

    static std::ifstream fin;
    static std::string line;
    static std::string::iterator iter1;
    static std::stringstream stream;

    double jk1,Cp,Ct,Pe,J,n1;
    std::string temp;
    bool charFlag=false;
    size_t sz;

    path=QCoreApplication::applicationDirPath().toStdString()+"\\database\\"+path;
    fin.open(path);
    count=0;
    if(!fin.is_open()){
        std::cout << "Error opening file";
    }
    else{

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
                    stream.clear();
                    stream.str(line);
                    stream>>temp>>temp>>temp>>n1;
                    n.push_back(n1/60.0);
                    count++;
                    Cp_curve.push_back(std::vector<double>());
                    Ct_curve.push_back(std::vector<double>());
                    Pe_curve.push_back(std::vector<double>());
                    J_curve.push_back(std::vector<double>());
                }

                if(isdigit(*iter1)){
                    stream.clear();
                    stream.str(line);

                    stream>>jk1>>J>>Pe>>Ct>>Cp>>jk1>>jk1>>jk1;

                    J_curve[count-1].push_back(J);
                    Cp_curve[count-1].push_back(Cp);
                    Ct_curve[count-1].push_back(Ct);
                    Pe_curve[count-1].push_back(Pe);
                }
            }
        }
    }

        stream.str(prop_name);
        stream>>diameter;
        diameter=diameter*.0254;
        fin.close();

}

