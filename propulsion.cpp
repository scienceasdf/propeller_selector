#include<vector>
#include<algorithm>
#include<iostream>
#include<fstream>
#include<string>
#include<sstream>

double* root(double* a, double* b, double* c, double* d, int n)
{
    if(n==1){
        double* x=new double[1];
        x[0]=d[0]/b[0];
        return x;
    }
    else{
        double* alpha=new double[n-1];
        double* beta;
        beta=new double[n];
        beta[0]=b[0];
        for(int i=0;i<=n-2;++i){
            alpha[i]=a[i]/beta[i];
            beta[i+1]=b[i+1]-alpha[i]*(c[i]);
        }
        double* x=new double[n],*y=new double[n];
        y[0]=d[0];
        for(int i=1;i<=n-1;++i) y[i]=d[i]-alpha[i-1]*(y[i-1]);
        x[n-1]=beta[n-1];
        for(int i=n-1;i>=0;--i) x[i]=(y[i]-c[i]*x[i+1])/beta[i];
        delete [] y;
        delete [] alpha;
        delete [] beta;
        return x;
    }
}


template<class T>
class spline{
public:
    std::vector<T> vecX;
    std::vector<T> vecY;
    spline() {}
    spline(T* xFirst, T* xLast, T* yFirst);
    /*spline(std::vector<T>::iterator xFirst,
           std::vector<T>::iterator xLast,
           std::vector<T>::iterator yFirst);*/
    ~spline(){delete [] m;}

    void addPoint(T x, T y) {vecX.push_back(x); vecY.push_back(y); sort(); isUpdated=false;}
    T getPos(T x);
    void clear();
private:
    bool isUpdated;
    T* m;
    void sort();
};

template<class T> T spline<T>::getPos(T x)
{
    int n=vecX.size()-1;
    if(isUpdated==false){
        T* alpha=new T[n+1];
        T* beta=new T[n+1];
        T* a=new T[n]; T* h=new T[n];
        T* b=new T[n+1]; T* c=new T[n];
        h[0]=vecX[1]-vecX[0];
        alpha[0]=1.0; alpha[n]=0.0;
        beta[0]=3.0/h[0]*(vecY[1]-vecY[0]);
        c[0]=1.0;
        b[0]=2.0; b[n]=2.0;

        for(int i=1; i<n; ++i){
            h[i]=vecX[i+1]-vecX[i];
            alpha[i]=h[i-1]/(h[i-1]+h[i]);
            beta[i]=3.0*((1.0-alpha[i])/h[i-1]*(vecY[i]-vecY[i-1])+alpha[i]/h[i]*(vecY[i+1]-vecY[i]));
            a[i-1]=1.0-alpha[i];
            c[i]=alpha[i];
            b[i]=2.0;

        }
        a[n-1]=1.0;
        beta[n]=3.0/h[n-1]*(vecY[n]-vecY[n-1]);

        m=root(a,b,c,beta,n+1);
        delete [] alpha;
        delete [] beta;
        delete [] a;
        delete [] b; delete [] c; delete [] h;
        isUpdated=true;
    }

    int i=n/2, min=0, max=n-1;
    if(x<=vecX[1]) i=0;
    else{
        if(x>=vecX[n-1]) i=n-1;
        else{
            while(((x-vecX[i])*(x-vecX[i+1]))>0){
                if((x-vecX[i])<0){
                    max=i;
                    i=(i+min)/2;
                }
                else{
                    min=i;
                    i=(i+max)/2;
                }

            }
        }
    }

    T s;
    s=(1.0+2.0*(x-vecX[i])/(vecX[i+1]-vecX[i]))*((x-vecX[i+1])/(vecX[i]-vecX[i+1]))*((x-vecX[i+1])/(vecX[i]-vecX[i+1]))*vecY[i];
    s+=(1.0+2.0*(x-vecX[i+1])/(vecX[i]-vecX[i+1]))*((x-vecX[i])/(vecX[i+1]-vecX[i]))*((x-vecX[i])/(vecX[i+1]-vecX[i]))*vecY[i+1];
    s+=(x-vecX[i])*((x-vecX[i+1])/(vecX[i]-vecX[i+1]))*((x-vecX[i+1])/(vecX[i]-vecX[i+1]))*m[i];
    s+=(x-vecX[i+1])*((x-vecX[i])/(vecX[i+1]-vecX[i]))*((x-vecX[i])/(vecX[i+1]-vecX[i]))*m[i+1];

    return s;
}

template<class T> void spline<T>::sort()
{
    const size_t n=vecX.size();

    for(int gap=n/2; 0<gap; gap/=2)
        for(int i=gap; i<n; i++)
            for(int j=i-gap; 0<=j; j-=gap)
                if(vecX[j+gap]<vecX[j]){
                    std::swap(vecX[j],vecX[j+gap]);
                    std::swap(vecY[j],vecY[j+gap]);
                }
}

template<class T> void spline<T>::clear()
{
    vecX.clear();
    vecY.clear();
}

class motor{
public:
    double Kv;
    double Ra;
    motor(double Kv_value, double resis): Kv(Kv_value),Ra(resis) {}
};

class propulsion{
public:
    motor mot;
    double speed;
    double rot;
    double torq;
    double thru;
    double pwer;
    double volt;
    double current;
    double eta;
    double eta_motor;
    double U_ub;
    double I_ub;
    void run(spline<double>& p_curve, spline<double>& thrust_curve, spline<double>& torque_curve);
    propulsion(double U, double I, motor mt):U_ub(U), I_ub(I),mot(mt) {}
};

void propulsion::run(spline<double>& p_curve, spline<double>& thrust_curve, spline<double>& torque_curve)
{
    double Km=30.0/mot.Kv/3.14159265358;
    double rev=mot.Kv*U_ub;

    double moment,prop,power;
    power=p_curve.getPos(rev);
    moment=torque_curve.getPos(rev);


    double i=moment/Km;
    volt=i*mot.Ra+rev/mot.Kv;
    while( (volt>U_ub) || (i>I_ub) ){
        rev-=100.0;
        power=p_curve.getPos(rev);
        moment=torque_curve.getPos(rev);

        i=moment/Km;
        volt=i*mot.Ra+rev/mot.Kv;
    }
    if(i<0){
        rot=.0;
        thru=.0;
        eta=.0;
    }
    else{
        current=i;
        eta_motor=power/current/volt;
        thru=thrust_curve.getPos(rev);
        eta=speed*thru/current/i;
        rot=rev;
    }
}

void Trim(std::string &str)
 {
 int s=str.find_first_not_of(" \t");
 int e=str.find_last_not_of(" \t");
 str=str.substr(s,e-s+1);
 }

int main()
{
    double n[46];//={1,2,3,4,5,6};
    double power[46];//={.007, .053,.177,.46,.97,1.698};
    double torque[46];//={.0429, 1.685 , 3.723,7.254,12.221,17.836};
    double thrust[46];//={.4, 1.605, 3.623,6.53,10.368,15.165};
    /*for(int i=0;i<6;++i){
        n[i]*=1e3;
        power[i]*=735;
        torque[i]*=0.11298;
        thrust[i]*=.454;
    }*/

    double jk1,jk2,jk3,jk4,jk5;
    std::stringstream stream,ss1;
    std::string temp;
    int counter=0;

    std::string::iterator iter1,iter2;
    motor mt1(1100,.042);
    propulsion p1(10.5,60,mt1);

    std::ifstream index("E:\\APC propeller_database\\PER2_TITLEDAT.txt");
    std::ifstream fin;

    double MaxThru=0.0,MaxI=.0,MaxV=0.0,MaxRot=.0;
    std::string MaxFileName;

    spline<double> n_power;
    spline<double> n_thrust;
    spline<double> n_torque;

    if(!index.is_open()){
        std::cout << "Error opening index file";
        exit (1);
    }

    std::string line,file;
    for(int i=0;i<4;++i){
        std::getline(index,line);
    }

    while(std::getline(index,file)){
        //std::cout<<file;
        Trim(file);
        //std::cout<<file<<"o-o\n";
        ss1.clear();
        ss1.str(file);
        ss1>>file;

        //std::cout<<("E:\\APC propeller_database\\"+file)<<"\n";

        fin.open("E:\\APC propeller_database\\"+file);
        counter=0;
        if(!fin.is_open()){
            //std::cout << "Error opening file";
        }
        else{

            while(std::getline(fin,line)){
                //Trim(line);
                iter1=line.begin();
                while((*iter1)==' '){
                    iter1=line.erase(iter1);
                }
                //std::cout<<"\n";
                if(*iter1=='P'){
                    ++iter1;
                    if(*iter1=='R'){
                        stream.clear();
                        stream.str(line);
                        stream>>temp;
                        stream>>temp;
                        stream>>temp;
                        stream>>n[counter];
                        //std::cout<<n[counter]<<"\n";
                    }
                }

                if(*iter1=='0'){
                    ++iter1;
                    if(*iter1=='.'){
                        ++iter1;
                        if(*iter1=='0'){
                            stream.clear();
                            stream.str(line);

                            stream>>jk1;
                            stream>>jk2;
                            stream>>jk3;
                            stream>>jk4;
                            stream>>jk5;
                            stream>>power[counter];
                            stream>>torque[counter];
                            stream>>thrust[counter];
                            ++counter;
                        }
                    }
                }
            }

            for(int i=0;i<counter;++i){
                power[i]*=735;
                torque[i]*=0.11298;
                thrust[i]*=.454;
                //std::cout<<n[i]<<"\t"<<power[i]<<"\t"<<torque[i]<<"\t"<<thrust[i]<<"\n";
            }

            n_power.clear();
            n_thrust.clear();
            n_torque.clear();

            for(int i=0;i<counter;++i){
                n_power.addPoint(n[i],power[i]);
                n_thrust.addPoint(n[i],thrust[i]);
                n_torque.addPoint(n[i],torque[i]);
            }

            p1.speed=jk1;
            p1.run(n_power,n_thrust,n_torque);

            if(MaxThru<p1.thru){
                MaxI=p1.current;
                MaxThru=p1.thru;
                MaxV=p1.volt;
                MaxRot=p1.rot;
                MaxFileName=file;
                //std::cout<<"\n";
            }
            fin.close();
        }
    }

    std::cout<<MaxThru<<"\t"<<MaxV<<"\t"<<MaxI<<"\t"<<MaxRot<<"\t"<<MaxFileName;

    //std::cout<<p1.rot<<"\t"<<p1.volt<<"\t"<<p1.current;
    //std::cout<<"\n"<<p1.thru;
    //std::cout<<"\n"<<p1.eta<<"\t"<<p1.eta_motor;
    return 0;

}
