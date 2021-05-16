#include "phone_number.h"
#include <sstream>
#include <stdexcept>
#include <regex>

PhoneNumber::PhoneNumber(const string &international_number) {
    regex r("^\\+[^-]+-[^-]+-.+$");
    if (!regex_match(international_number, r)) {
        throw invalid_argument("");
    }
    auto firstDelimiter = international_number.find('-');
    auto secondDelimiter = international_number.find('-', firstDelimiter + 1);
    country_code_ = international_number.substr(1, firstDelimiter - 1);
    city_code_ = international_number.substr(firstDelimiter + 1, secondDelimiter - firstDelimiter - 1);
    local_number_ = international_number.substr(secondDelimiter + 1);
}

string PhoneNumber::GetCountryCode() const {
    return country_code_;
}

string PhoneNumber::GetCityCode() const {
    return city_code_;
}

string PhoneNumber::GetLocalNumber() const {
    return local_number_;
}

string PhoneNumber::GetInternationalNumber() const {
    stringstream ss;
    ss << '+' << country_code_ << '-' << city_code_ << '-' << local_number_;
    return ss.str();
}
