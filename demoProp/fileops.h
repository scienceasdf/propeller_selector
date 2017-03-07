#ifndef FILEOPS_H
#define FILEOPS_H
#include<report.h>

void Trim(std::string &str);

void getAll(report& rep,
            double minThrust,
            double minDynamicThrust,
            double minEtaProp,
            double minEtaTotal,
            propulsion& p1);

#endif // FILEOPS_H
