#ifndef WINDFARM_CSV_PARSER_H
#define WINDFARM_CSV_PARSER_H

#include <string>
#include <vector>


struct Date {
    int year;
    int month;
    int day;
    int hour;
};

bool operator ==(const Date &a, const Date &b);

bool operator !=(const Date &a, const Date &b);

bool operator >(const Date &a, const Date &b);

bool operator <(const Date &a, const Date &b);

bool operator >=(const Date &a, const Date &b);

bool operator <=(const Date &a, const Date &b);


struct WindMeasurement {
    Date date;
    std::vector<float> values;
};


std::vector<std::string> split(const std::string &str, char delimiter);

Date stringToDate(const std::string &str);

WindMeasurement stringToWindMeasurement(const std::string &str);

std::vector<WindMeasurement> parseFile(const std::string &filepath,
                                       unsigned int row_offset, char delimiter);

std::vector<WindMeasurement> cut(const std::vector<WindMeasurement> &measurements,
                                 Date a, Date b);

WindMeasurement getByDate(const std::vector<WindMeasurement> &measurements, Date d);

float avg(const std::vector<WindMeasurement> &measurements, unsigned int column);

float max(const std::vector<WindMeasurement> &measurements, unsigned int column);

float min(const std::vector<WindMeasurement> &measurements, unsigned int column);


#endif //WINDFARM_CSV_PARSER_H