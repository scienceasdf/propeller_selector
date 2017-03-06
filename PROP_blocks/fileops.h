#ifndef FILEOPS_H
#define FILEOPS_H

void Trim(std::string &str);

void getAll(std::vector<std::string>& list,
            double minThrust,
            double minDynamicThrust,
            double minEtaProp,
            double minEtaTotal,
            propulsion& p1);

#endif // FILEOPS_H
