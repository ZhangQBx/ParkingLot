//
// Created by Qinbo Zhang on 2023/1/19.
//
#include "Admin.h"
#include "../Car/Car.h"

void Admin::manager() {
    int adminChoice;
    cout << "1. 查看所有汽车信息" << endl << "2. 查看指定汽车信息" << endl << \
    "3. 添加汽车" << endl << "4. 修改汽车信息" << endl << "5. 删除汽车" << endl;
    cin>>adminChoice;
    switch(adminChoice){
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
        case 3:
            {
                Car car;
                car.addCar();
                break;
            }
        case 4:
            Car::modCar();
            break;
        case 5:
            Car::delCar();
            break;
        default:
            return ;
    }
}

