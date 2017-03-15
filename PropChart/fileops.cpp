#include<fileops.h>
#include<iostream>
#include<QCoreApplication>

void trim(std::string &s)
{

    if( !s.empty() )
    {
        s.erase(0,s.find_first_not_of(" "));
        s.erase(s.find_last_not_of(" ") + 1);
    }

}

void getAll_on_RPM(report& rep,
            double RPM,
            double speed,
            double minThrust,
            double minDynamicThrust,
            double minEtaProp,
            double maxPower,
            propeller& p1)
{
    std::stringstream ss1;


    std::ifstream index(QCoreApplication::applicationDirPath().toStdString()+"\\database\\PER2_TITLEDAT.txt");
    std::string file;

    std::getline(index,file);
    std::getline(index,file);
    std::getline(index,file);
    std::getline(index,file);

    double thrust=.0;
    double dynamicThrust=.0;
    double eta=.0;
    double power=.0;

    while(std::getline(index,file)){
            //Trim(file,iter1);
            trim(file);
            ss1.clear();
            ss1.str(file);
            ss1>>file;

            double tempThru=.0;
            p1.getCurve(file);
            thrust=p1.thrust_on_RPM(RPM,.0);
            power=p1.power_on_RPM(RPM,.0);

            if(thrust>minThrust && power<maxPower){

                dynamicThrust=p1.thrust_on_RPM(RPM,speed);
                eta=p1.eta_on_RPM(RPM,speed);
                power=p1.power_on_RPM(RPM,speed);
                if(dynamicThrust>minDynamicThrust && eta>minEtaProp && power<maxPower){
                    rep.files.push_back(file);
                    rep.props.push_back(p1.prop_name);
                    rep.thrust.push_back(thrust);
                    rep.dynamicThrust.push_back(dynamicThrust);
                    rep.etaProp.push_back(eta);
                    //nameLists.push_back(p1.prop_name);

                }
            }
    }
}

void getAll_on_power(report& rep,
            double power,
            double speed,
            double minThrust,
            double minDynamicThrust,
            double minEtaProp,
            propeller& p1)
{
    std::stringstream ss1;

    std::ifstream index(QCoreApplication::applicationDirPath().toStdString()+"\\database\\PER2_TITLEDAT.txt");
    std::string file;

    std::getline(index,file);
    std::getline(index,file);
    std::getline(index,file);
    std::getline(index,file);

    double thrust=.0;
    double dynamicThrust=.0;
    double eta=.0;


    while(std::getline(index,file)){
            //Trim(file,iter1);
            trim(file);
            ss1.clear();
            ss1.str(file);
            ss1>>file;

            double tempThru=.0;
            p1.getCurve(file);
            thrust=p1.thrust_on_power(power,.0);
            //power=p1.power_on_RPM(RPM,.0);

            if(thrust>minThrust){

                double RPM=p1.RPM_on_power(power,speed);
                dynamicThrust=p1.thrust_on_RPM(RPM,speed);
                eta=p1.eta_on_RPM(RPM,speed);
                if(dynamicThrust>minDynamicThrust && eta>minEtaProp){
                    rep.files.push_back(file);
                    rep.props.push_back(p1.prop_name);
                    rep.thrust.push_back(thrust);
                    rep.dynamicThrust.push_back(dynamicThrust);
                    rep.etaProp.push_back(eta);
                    //nameLists.push_back(p1.prop_name);

                }
            }
    }
}

void searchProp(const std::string&& str,
           std::vector<std::string>& nameLists,
           std::vector<std::string>& pathLists)
{
    std::stringstream ss1;
    QString strPath = QCoreApplication::applicationDirPath();

    pathLists.clear();
    nameLists.clear();

    std::ifstream index(strPath.toStdString()+"\\database\\PER2_TITLEDAT.txt");
    std::string line,info1,info2;

    std::getline(index,line);
    std::getline(index,line);
    std::getline(index,line);
    std::getline(index,line);

    while(std::getline(index,line)){
        std::size_t found=line.find(str);
        if(found!=std::string::npos){
            ss1.clear();
            ss1.str(line);
            ss1>>info1>>info2;
            pathLists.push_back(info1);
            nameLists.push_back(info2);
        }
    }
}

