#include <iostream>
#include "Car/Car.h"
#include "User/User.h"
#include "Admin/Admin.h"
#include "vector"

int main() {
    bool flag = true;
    while (flag) {
        int choice;
        cout << "请选择登录身份：" << endl << "1.普通用户" << endl << "2.管理员" << endl << "3.退出系统" << endl;
        cin >> choice;
        switch (choice) {
            case 1:
//                system("cls");
                User::checkCar();
                break;
            case 2:
//                system("cls");
                Admin::manager();
                break;
            default:
                flag = false;
        }
    }

    return 0;
}

