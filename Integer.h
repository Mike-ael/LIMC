#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cctype>
#include <iostream>
#include <numeric>
#include <string_view>
using namespace std::literals::string_view_literals;
//class to handle big numbers that cant be handled by the standard types
class Integer {
public:
	class InvalidValue : public std::exception {
	private:
		std::string value;
		std::string_view errorMessage;
	public:
		InvalidValue(std::string_view val) : value(val) {
			errorMessage = "ERROR: " + value + " is not a valid integer.\n";
		}
		const char* what() const noexcept override {
			return errorMessage.data();
		}
	};
	Integer();
	Integer(const char*);
	Integer(const Integer&);
	std::string GetValue() const;
	//overloading the math operators
	Integer operator+ (const Integer&);
	Integer operator- (const Integer&);
	Integer operator* (const Integer&);
	Integer operator/ (const Integer&);
	Integer operator^ (const Integer&);
	bool operator== (const Integer&);
	const Integer operator= (const Integer&);
	void* operator new (size_t size) {
		return malloc(size);
	}
	void operator delete (void* memory) {
		free(memory);
	}
	void* operator new[](size_t size) {
		return malloc(size);
	}
	void operator delete[] (void* memory) {
	    free(memory);
	}
	//overloading the stream operators
	friend std::ostream& operator<< (std::ostream&, const Integer&);
	friend std::istream& operator>> (std::istream&, Integer&);
private:
	std::string number{""};
	std::string numString{"0123456789"};
	std::string add(std::string_view, std::string_view);
	std::string subtract(std::string_view, std::string_view);
	std::string multiply(std::string_view, std::string_view);
	std::string divide(std::string_view, std::string_view);
	std::string power(Integer, Integer);
};
