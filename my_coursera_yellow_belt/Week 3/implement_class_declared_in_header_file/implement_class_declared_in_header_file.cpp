#include <stdexcept>
#include <string>
#include <sstream>
#include <iostream>

#include "phone_number.h"

PhoneNumber::PhoneNumber(const std::string& international_number) 
{
    std::istringstream is(international_number);

    char sign = is.get();
    std::getline(is, country_code_, '-');
    std::getline(is, city_code_, '-');
    std::getline(is, local_number_);

    if (sign != '+' || country_code_.empty() || city_code_.empty() || local_number_.empty()) 
    {
        throw std::invalid_argument("Phone number must begin with '+' symbol and contain 3 parts separated by '-' symbol: " + international_number);
    }
}

std::string PhoneNumber::GetCountryCode() const 
{
    return country_code_;
}

std::string PhoneNumber::GetCityCode() const 
{
    return city_code_;
}

std::string PhoneNumber::GetLocalNumber() const 
{
    return local_number_;
}

std::string PhoneNumber::GetInternationalNumber() const 
{
    return ("+" + country_code_ + "-" + city_code_ + "-" + local_number_);
}
