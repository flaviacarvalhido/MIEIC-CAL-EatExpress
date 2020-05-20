

#include <string>
#include <vector>

#ifndef EATEXPRESS_UTILS_H
#define EATEXPRESS_UTILS_H

#endif //EATEXPRESS_UTILS_H


using namespace std;

bool checkPhone(long int phone);

void trimLeft(string& s);

void trimRight(string& s);

void trim(string& s);

int s1(string m);

int base10(unsigned int times);

int mstoi(string m);

bool compare_str(string str1, string str2);

void replaceAccent(string& str);

vector<string> decompose(string s, char sep);

/*
pair<Hour, Date> currentTimeNDate();

bool compareTime(pair<Hour, Date> T1, pair<Hour, Date> T2);

pair<Hour, Date> addTimetoTimeNDate(pair<Hour, Date> td, Hour t1);

*/