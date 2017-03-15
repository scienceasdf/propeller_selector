#ifndef FILEOPS_H
#define FILEOPS_H

#include<string>
#include<vector>
#include<objects.h>
#include<report.h>

void Trim(std::string &str);

void getAll_on_RPM(report& rep,
            double RPM,
            double speed,
            double minThrust,
            double minDynamicThrust,
            double minEtaProp,
            double maxPower,
            propeller& p1);

void getAll_on_power(report& rep,
            double power,
            double speed,
            double minThrust,
            double minDynamicThrust,
            double minEtaProp,
            propeller& p1);

void searchProp(const std::string&& str,
           std::vector<std::string>& nameLists,
           std::vector<std::string>& pathLists);

#endif // FILEOPS_H
