#ifndef _STRING_HELPER_H
#define _STRING_HELPER_H

#include <algorithm> 
#include <functional> 
#include <cctype>
#include <locale>
#include <string>
#include <sstream> 
#include <ios>
#include <iomanip>

#include <Wt/Utils>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

// trim from start
static inline std::string &ltrim(std::string &s)
{
	s.erase(s.begin(), std::find_if(s.begin(), s.end(),
		std::not1(std::ptr_fun<int, int>(std::isspace))));
	return s;
}

// trim from end
static inline std::string &rtrim(std::string &s)
{
	s.erase(std::find_if(s.rbegin(), s.rend(),
		std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
	return s;
}

// trim from both ends
static inline std::string &trim(std::string &s)
{
	return ltrim(rtrim(s));
}

// Compute MD5 from one string
static inline std::string copmuteMd5(std::string& str)
{
	return Wt::Utils::hexEncode(Wt::Utils::md5(str));
}

// Compute SHA1 from one string
static inline std::string computeSHA1(std::string& str)
{
	return Wt::Utils::hexEncode(Wt::Utils::sha1(str));
}

// Compute MD5 from one char pointer
static inline std::string copmuteMd5(const char* str)
{
	return Wt::Utils::hexEncode(Wt::Utils::md5(str));
}

// Compute SHA1 from one char pointer
static inline std::string computeSHA1(const char* str)
{
	return Wt::Utils::hexEncode(Wt::Utils::sha1(str));
}

// Compute a md5 of SHA1 of a string
static inline std::string encrypt(std::string& str)
{
	return copmuteMd5(computeSHA1(str));
}

// convert all string to lower
static inline std::string toLower(std::string& str)
{
	std::string retString = std::string(str);
	std::transform(retString.begin(), retString.end(), retString.begin(), ::tolower);
	return retString;
}

// Check if a string ends with other string
static inline bool endsWith(std::string& str, std::string& val)
{
	return boost::ends_with(str, val);
}

// Convert string to int
static inline int toInt(std::string& str)
{
	return std::stoi(str);
}

// Convert string to double
static inline double toDouble(std::string& str)
{
	if (str == "unch")
		return -1;

	return std::stod(str);
}

// Convert double to string
static inline std::string toString(double value)
{
	std::stringstream stream;
	stream << std::fixed << std::setprecision(2) << value;
	std::string s = stream.str();
	return s;
}

// Convert a string to posix date
static inline boost::posix_time::ptime toPosixDate(std::string& str, const std::string format)
{
	const std::locale loc = std::locale(std::locale::classic(), new boost::posix_time::time_input_facet(format));
	std::istringstream is(str);
	is.imbue(loc);
	boost::posix_time::ptime t;
	is >> t;
	return t;
}

#endif