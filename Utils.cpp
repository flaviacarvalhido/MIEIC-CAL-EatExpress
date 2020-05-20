#include <algorithm>
#include "Utils.h"


void trimLeft(string& s) {
    s.erase(0, s.find_first_not_of(" "));
}
void trimRight(string& s) {
    s.erase(s.find_last_not_of(" ") + 1, s.length());
}
void trim(string& s) {
    trimLeft(s);
    trimRight(s);
}

int s1(string m) {
    if (m == "0") return 0;
    if (m == "1") return 1;
    if (m == "2") return 2;
    if (m == "3") return 3;
    if (m == "4") return 4;
    if (m == "5") return 5;
    if (m == "6") return 6;
    if (m == "7") return 7;
    if (m == "8") return 8;
    if (m == "9") return 9;
    return 0;
}

int base10(unsigned int times) {
    int result = 1;
    for (unsigned int i = 0; i < times; i++) {
        result *= 10;
    }
    return result;
}

int mstoi(string m) {
    int result = 0;
    trim(m);
    int counter = m.length();
    //cout << "length-"<<counter;
    //cout << "input-" << m;
    string usage;
    bool neg = false;
    for (unsigned int i = 0; i < m.size(); i++) {
        usage = m[i];
        if (usage == "-") {
            neg = true;
            continue;
        }
        //cout << "(" << m[i] << ")";
        result += s1(usage) * base10(counter - 1);
        //cout <<"("<< result<<")";
        counter--;
    }
    if (neg)
        result *= -1;
    //cout << result;
    return result;
}




/*
pair<Hour, Date> currentTimeNDate() {
    Hour t;
    Date d;

    time_t now = time(0);
#pragma warning(suppress : 4996)
    tm* td = gmtime(&now);

    t.setMin(td->tm_min);
    t.setHour(td->tm_hour);
    d.setDay(td->tm_mday);
    d.setMonth(td->tm_mon + 1);
    d.setYear(1900 + td->tm_year);

    return make_pair(t, d);
}
 */
/*
pair<Hour, Date> addTimetoTimeNDate(pair<Hour, Date> td,Hour t1) {

    Hour temp = td.first;
    td.first = td.first + t1;
    if (td.first < temp) td.second = td.second + 1;

    return td;

}

*/

vector<string> decompose(string s, char sep) {
    vector<string> elements;
    string usage = "";
    for (unsigned int i = 0; i < s.length(); i++) {
        if (s[i] == sep) {
            trim(usage);
            elements.push_back(usage);
            usage = "";
        }
        else {
            usage += s[i];

            if (i == s.length() - 1) {
                trim(usage);
                elements.push_back(usage);
            }

        }
    }
    return elements;
}





bool compare_str(string str1, string str2) {

    transform(str1.begin(), str1.end(), str1.begin(), ::toupper);
    transform(str2.begin(), str2.end(), str2.begin(), ::toupper);
    if (str1 == str2) return true;
    return false;
}


/*
bool compareTime(pair<Hour, Date> T1, pair<Hour, Date> T2) {
    Date d1 = T1.second;
    Date d2 = T2.second;
    Hour t1 = T1.first;
    Hour t2 = T2.first;
    if (d1 < d2)return true;
    if (d2 < d1)return false;

    return t1 < t2;
}
 */









