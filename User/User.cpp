//
// Created by Qinbo Zhang on 2023/1/19.
//
#include "User.h"
#include "../Car/Car.h"

void User::checkCar() {
    int userChoice;
    cout << "1. 查看所有汽车信息" << endl << "2. 查看指定汽车信息" << endl << "3. 返回主菜单" << endl;
    cin >> userChoice;
    switch (userChoice) {
        case 1:
            Car::showInfo("all");
            break;
        case 2:
            {
                string carNum;
                cout << "请输入要查询的车牌号：" << endl;
                cin >> carNum;
                Car::showInfo(carNum);
                break;
            }
        default:
            return ;
    }
}
