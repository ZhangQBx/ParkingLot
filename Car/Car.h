//
// Created by Qinbo Zhang on 2023/1/16.
//

#ifndef PARKINGSYSTEM_CAR_H
#define PARKINGSYSTEM_CAR_H

#include <iostream>

using namespace std;

class Car {
public:
//    Car();
    void addCar();
    static void delCar();
    static void findCar();
    static void modCar();
    static vector<string> timeAmount(bool timeOrFee);
    static void showInfo(const string &carNum);
    void saveInfo();

private:
    string _carNum;
    string _carType;
    string _carColor;
    time_t _enterTime;

};

#endif //PARKINGSYSTEM_CAR_H
