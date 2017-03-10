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

void searchProp(const std::string&& str,
           std::vector<std::string>& nameLists,
           std::vector<std::string>& pathLists);

#endif // FILEOPS_H
