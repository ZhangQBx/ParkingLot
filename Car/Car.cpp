//
// Created by Qinbo Zhang on 2023/1/16.
//
#include "Car.h"
#include <fstream>
#include <vector>
#include <cstdio>
#include <cctype>

vector<string> split(string str, const char &separator) {
    vector<string> res;
    str += separator;
    string value = "";
    for (char i: str) {
        if (i == separator || i == '\0') {
            res.push_back(value);
            value = "";
        } else {
            value += i;
        }
    }
    return res;
}

bool isCarExist(const vector<string> &existCarNum, const string &carNum) {
    for (const string &i: existCarNum) {
        if (carNum == i) {
            return true;
        }
    }

    return false;
}

time_t stringToTime(const string &str) {
    struct tm pTime;
    int year, month, day, hour, min, sec;
    sscanf(str.c_str(), "%d-%d-%d_%d:%d:%d", &year, &month, &day, &hour, &min, &sec);
    pTime.tm_year = year - 1900;
    pTime.tm_mon = month - 1;
    pTime.tm_mday = day;
    pTime.tm_hour = hour;
    pTime.tm_min = min;
    pTime.tm_sec = sec;
    pTime.tm_isdst = 0;
    time_t t = mktime(&pTime);

    return t;
}

vector<string> secToDate(double diffSec) {
    vector<string> res;
    string resTime;
    string parkingFee;
    int hour, minute, sec;
    hour = (int) diffSec / 3600;
    minute = ((int) diffSec / 60) % 60;
    sec = (int) diffSec % 60;

    resTime = to_string(hour) + '-' + to_string(minute) + '-' + to_string(sec);
    parkingFee = to_string((minute || sec) ? 8 * (hour + 1) : 8 * hour);
    res.push_back(resTime);
    res.push_back(parkingFee);

    return res;
}

void Car::addCar() {
    ifstream ifs;
    string tempData;
    string carNum;
    vector<string> existCarNum;
    bool isExist = false;   //检查是否车牌号是否已存在

    ifs.open("../carData.txt", ios::in);
    if (!ifs) {
        cout << "打开读取文件失败。" << endl;
        return;
    }
    while (getline(ifs, tempData)) {
        existCarNum.push_back(split(tempData, ' ')[0]);
    }
    ifs.close();

    while (!isExist) {
        cout << "请输入车牌号: " << endl;
        cin >> carNum;
        isExist = !(isCarExist(existCarNum, carNum));
        if (!isExist) {
            cout << "已录入，请重新输入。" << endl;
        }
    }
    _carNum = carNum;

    cout << "验证通过，请继续输入其他信息。" << endl;
    cout << "输入车辆类型：" << endl;
    cin >> _carType;
    cout << "输入车辆颜色：" << endl;
    cin >> _carColor;
    time(&_enterTime);
    saveInfo();
    cout << "保存成功" << endl;
//    return ;
}

void Car::delCar() {
    ifstream ifs;
    ofstream ofs;
    bool isExist = false;   //检查是否车牌号是否已存在

    ifs.open("../carData.txt", ios::in);
    if (!ifs) {
        cout << "打开读取文件失败。" << endl;
        return;
    }
    ofs.open("../carDataTemp.txt", ios::out | ios::app);
    if (!ofs) {
        cout << "打开临时写入文件失败" << endl;
        return;
    }

    string delCarNum;
    string tempData;
    vector<string> existCarNum;

    //读取源文件中的所有车牌号
    while (getline(ifs, tempData)) {
        existCarNum.push_back(split(tempData, ' ')[0]);
    }

    while (!isExist) {
        cout << "请输入车牌号: " << endl;
        cin >> delCarNum;
        isExist = isCarExist(existCarNum, delCarNum);
        if (!isExist) {
            cout << "车辆不存在，请重新输入。" << endl;
        }
    }

    //重新设置文件流状态
    ifs.clear();
    ifs.seekg(0, ios::beg);

    int carNumIndex = 0;
    while (getline(ifs, tempData)) {
        if (delCarNum != existCarNum[carNumIndex]) {
            ofs << tempData << endl;
        }
        carNumIndex++;
    }

    tempData = "";
    ifs.close();
    ofs.close();

    ifstream newIfs;
    ofstream newOfs;
    newIfs.open("../carDataTemp.txt", ios::in);
    if (!newIfs) {
        cout << "打开临时读取文件失败。" << endl;
    }
    newOfs.open("../carData.txt", ios::out | ios::trunc);
    if (!newOfs) {
        cout << "打开写入文件失败。" << endl;
    }

    while (getline(newIfs, tempData)) {
        newOfs << tempData << endl;
    }

    newIfs.close();
    newOfs.close();

    remove("../carDataTemp.txt");
    cout << "删除完成。" << endl;
}

void Car::findCar() {
    ifstream ifs;
    ifs.open("../carData.txt", ios::in);

    bool findCar = false;
    string findCarNum;
    string tempData;
    cout << "请输入需要查询的车牌号：" << endl;
    cin >> findCarNum;

    while (getline(ifs, tempData)) {
        if (findCarNum == split(tempData, ' ')[0]) {
            //To be completed
            findCar = true;
            cout << tempData << endl;
        }
    }

    if (!findCar) {
        cout << "未查询到车辆。" << endl;
    }
    ifs.close();
}

void Car::modCar() {
    bool isExist = false;
    ifstream ifs;
    ifs.open("../carData.txt", ios::in);
    if (!ifs.good()) {
        cout << "打开读取文件失败。" << endl;
    }

    ofstream ofs;
    ofs.open("../carDataTemp.txt", ios::out | ios::trunc);
    if (!ofs.good()) {
        cout << "打开临时写入文件失败。" << endl;
    }

    string modCarNum;
    string tempData;
    vector<string> existCarNum;
    vector<string> existCarEnterTime;
    while (getline(ifs, tempData)) {
        existCarNum.push_back(split(tempData, ' ')[0]);
        existCarEnterTime.push_back(split(tempData, ' ')[3]);
    }

    while (!isExist) {
        cout << "请输入需要修改的汽车车牌号：" << endl;
        cin >> modCarNum;
        isExist = isCarExist(existCarNum, modCarNum);
        if (!isExist) {
            cout << "车辆不存在，请重新输入。" << endl;
        }
    }

    string newCarNum, carType, carColor;
    cout << "请输入修改后的车牌照：";
    cin >> newCarNum;
    cout << "请输入修改后的车辆类型：";
    cin >> carType;
    cout << "请输入修改后的车辆颜色：";
    cin >> carColor;

    int carNumIndex = 0;
    tempData = "";
    ifs.clear();
    ifs.seekg(0, ios::beg);

    while (getline(ifs, tempData)) {
        if (modCarNum != existCarNum[carNumIndex]) {
            ofs << tempData << endl;
        } else {
            ofs << newCarNum << ' ' << carType << ' ' << carColor << ' ' << existCarEnterTime[carNumIndex] << endl;
        }
        carNumIndex++;
    }

    ifs.close();
    ofs.close();

    ifstream newIfs;
    newIfs.open("../carDataTemp.txt", ios::in);
    if (!newIfs.good()) {
        cout << "打开临时读取文件失败。" << endl;
    }

    ofstream newOfs;
    newOfs.open("../carData.txt", ios::out | ios::trunc);
    if (!newOfs.good()) {
        cout << "打开写入文件失败。" << endl;
    }

    tempData = "";
    while (getline(newIfs, tempData)) {
        newOfs << tempData << endl;
    }

    newIfs.close();
    newOfs.close();
    remove("../carDataTemp.txt");

    cout << "修改完成" << endl;
}

void Car::showInfo(const string &carNum) {
    string tempData;
    vector<string> parkingFee;
    bool find = false;
    ifstream ifs;
    ifs.open("../carData.txt", ios::in);
    if (!ifs.good()) {
        cout << "打开读取文件失败。" << endl;
    }

    parkingFee = timeAmount(1);
    int index = 0;
    if (carNum == "all") {
        while (getline(ifs, tempData)) {
            cout << tempData << " 费用：" << parkingFee[index] << endl;
            index++;
        }
        index = 0;
        return;
    } else {
        while (getline(ifs, tempData)) {
            if (carNum == split(tempData, ' ')[0]) {
                cout << tempData << " 费用：" << parkingFee[index] << endl;
                find = true;
            }
            index++;
        }
        index = 0;
        if (!find)
            cout << "车辆不存在" << endl;
    }

    ifs.close();

}

vector<string> Car::timeAmount(bool timeOrFee) {
//    struct tm *pTime;
    vector<time_t> enterTime;
    vector<string> existCarNum;
    vector<string> res;
    string previousTime;
    string tempData;
    time_t nowTime;
    int index;
    time(&nowTime);
//    pTime = localtime(&nowTime);

    if (timeOrFee)
        index = 1;
    else
        index = 0;
    ifstream ifs;
    ifs.open("../carData.txt", ios::in);
    if (!ifs.good()) {
        cout << "打开读取文件失败。" << endl;
    }

    while (getline(ifs, tempData)) {
        previousTime = split(tempData, ' ')[3];
        enterTime.push_back(stringToTime(previousTime));
        existCarNum.push_back(split(tempData, ' ')[0]);
    }

    ifs.close();
    for (int i = 0; i < existCarNum.size(); i++) {
        res.push_back(secToDate(difftime(nowTime, enterTime[i]))[index]);
    }

    return res;
}

void Car::saveInfo() {
    struct tm *pTime;
    ofstream ofs;
    ofs.open("../carData.txt", ios::out | ios::app);
    if (!ofs) {
        cout << "打开写入文件失败" << endl;
        return;
    }

    pTime = localtime(&_enterTime);
    string parkingTime = to_string(1900 + pTime->tm_year) + '-' + to_string(1 + pTime->tm_mon) + '-' + \
                        to_string(pTime->tm_mday) + '_' + to_string(pTime->tm_hour) + ':' + \
                        to_string(pTime->tm_min) + ':' + to_string(pTime->tm_sec);

    ofs << _carNum << ' ' << _carType << ' ' << _carColor << ' ' << parkingTime << endl;
    cout << "写入完成" << endl;
    ofs.close();

}
