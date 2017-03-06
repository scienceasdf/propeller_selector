#ifndef OBJECTS_H
#define OBJECTS_H

#include<spline.h>
#include<fstream>
#include<sstream>
#include<string>

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
    double rot;     //The revolution of the propeller, not the motor
    double torq;
    double thru;    //unit is Newton
    double pwer;
    double volt;
    double current;
    double eta;
    double eta_motor;
    double U_ub;
    double I_ub;
    double eta_gear;
    double gear_rto;
    //If the ratio is greater than 1.0, the revolution is slowed down by the gear
    std::string prop_name;

    void run();
    void dynamic_run();
    void get_curve(std::string fileName);
    double eta_prop();

    propulsion(double U, double I, motor mt, double rto, double eta):
        U_ub(U), I_ub(I), mot(mt), gear_rto(rto), eta_gear(eta) {}
protected:
    spline<double> p_curve;
    spline<double> thrust_curve;
    spline<double> torque_curve;

    spline<double> dynamic_p_curve;
    spline<double> dynamic_thrust_curve;
    spline<double> dynamic_torque_curve;

private:

};

#endif // OBJECTS_H
