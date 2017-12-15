#include <string>
#include <utility>
#include <vector>
#include <sstream>
#include <fstream>
#include <iostream>
#include "DataParser.h"

using std::string;
using std::vector;


bool operator ==(const Date &a, const Date &b) {
    return (a.year == b.year) && (a.month == b.month) && (a.day == b.day) && (a.hour == b.hour);
}

bool operator !=(const Date &a, const Date &b) {
    return !(a == b);
}

bool operator >(const Date &a, const Date &b) {
    if (a.year == b.year) {
        if (a.month == b.month) {
            if (a.day == b.day) {
                return a.hour > b.hour;
            } else {
                return (a.day > b.day);
            }
        } else {
            return (a.month > b.month);
        }
    } else {
        return (a.year > b.year);
    }
}

bool operator <(const Date &a, const Date &b) {
    return (a != b) && !(a > b);
}

bool operator >=(const Date &a, const Date &b) {
    return (a > b) || (a == b);
}

bool operator <=(const Date &a, const Date &b) {
    return (a < b) || (a == b);
}


vector<string> split(const string &str, char delimiter) {
    vector<string> splitString;
    std::istringstream stream(str);
    string field;
    while (std::getline(stream, field, delimiter)) {
        splitString.push_back(field);
    }
    return splitString;
}

Date stringToDate(const string &str) {
    Date result = {};
    sscanf(str.c_str(), "%4d-%2d-%2d %2d", &result.year,
        &result.month, &result.day, &result.hour);
    return result;
}

WindMeasurement stringToWindMeasurement(const string &str, char delimiter) {
    WindMeasurement result = {};
    vector<string> stringFields = split(str, delimiter);
    result.date = stringToDate(stringFields.at(0));
    vector<float> v;
    for (unsigned int i = 1; i < stringFields.size(); i++) {
        try {
            float f = stof(stringFields.at(i));
            v.push_back(f);
        } catch (std::invalid_argument e) {
            throw e;
        }
    }
    result.values = v;
    return result;
}

vector<WindMeasurement> parseFile(const string &filepath, unsigned int row_offset, char delimiter) {
    vector<WindMeasurement> result;
    std::ifstream file(filepath);
    if (file.is_open()) {
        string line;
        for (unsigned int i = 0; i < row_offset; i++) {
            std::getline(file, line);
        }
        while (std::getline(file, line)) {
            try {
                WindMeasurement measurement = stringToWindMeasurement(line, delimiter);
                result.push_back(measurement);
            } catch (std::invalid_argument e) {
                continue;
            }
        }
        file.close();
    }
    return result;
}

vector<WindMeasurement> cut(const vector<WindMeasurement> &measurements, Date a, Date b) {
    vector<WindMeasurement> result;
    for (auto &i : measurements) {
        if (i.date >= a && i.date <= b) {
            result.push_back(i);
        } else if (i.date > b) {
            break;
        }
    }
    return result;
}

WindMeasurement getByDate(const vector<WindMeasurement> &measurements, Date d) {
    WindMeasurement result = {0};
    for (auto &i : measurements) {
        if (i.date == d) {
            result = i;
            break;
        }
    }
    return result;
}

float avg(const vector<WindMeasurement> &measurements, unsigned int column) {
    float sum = 0.0;
    int count = 0;
    for (auto &i : measurements) {
        sum += i.values.at(column);
        count++;
    }
    return sum / (float)count;
}

float max(const vector<WindMeasurement> &measurements, unsigned int column) {
    float max = measurements.at(0).values.at(column);
    for (auto &i : measurements) {
        if (i.values.at(column) > max) {
            max = i.values.at(column);
        }
    }
    return max;
}

float min(const vector<WindMeasurement> &measurements, unsigned int column) {
    float min = measurements.at(0).values.at(column);
    for (auto &i : measurements) {
        if (i.values.at(column) < min) {
            min = i.values.at(column);
        }
    }
    return min;
}