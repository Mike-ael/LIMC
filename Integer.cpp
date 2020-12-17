#include "Integer.h"


Integer::Integer() = default;

Integer::Integer(const char* str) {
	number.clear();
	std::string str1 = str;
	for (const auto& elem : str1) {
		(!isdigit(elem)) && (elem != '-') ? throw Integer::InvalidValue(str) : number += elem;
	}
}

Integer::Integer(const Integer& otherObject) : Integer(otherObject.number.c_str()){}

std::string Integer::GetValue() const {
	return number;
}

Integer Integer::operator+ (const Integer & otherInteger) {
	if (std::size(number) > std::size(otherInteger.number)) {
		auto diff = number.size() - otherInteger.number.size();
		std::string tempInteger(diff, '0');
		tempInteger += otherInteger.number;
		return Integer(add(number, tempInteger).c_str());
	}
	else if (std::size(number) < std::size(otherInteger.number)) {
		auto diff = otherInteger.number.size() - number.size();
		std::string tempInteger(diff, '0');
		tempInteger += number;
		return Integer(add(tempInteger, otherInteger.number).c_str());
	}
	else
		return Integer(add(number, otherInteger.number).c_str());
}

Integer Integer::operator- (const Integer& otherInteger){
	if (std::size(number) > std::size(otherInteger.number)) {
		auto diff = number.size() - otherInteger.number.size();
		std::string tempInteger(diff, '0');
		tempInteger += otherInteger.number;
		return Integer(subtract(number, tempInteger).c_str());
	}
	else if (std::size(number) < std::size(otherInteger.number)) {
		auto diff = otherInteger.number.size() - number.size();
		std::string tempInteger(diff, '0');
		tempInteger += number;
		return Integer(("-" + subtract(otherInteger.number, tempInteger)).c_str());
	}
	else if (number == otherInteger.number)
		return Integer("0");
	else {
		auto length = std::size(number);
		for (size_t i{ 0 }; i < length; ++i) {
			if (number.at(i) > otherInteger.number.at(i))
				return Integer(subtract(number, otherInteger.number).c_str());
			else if (number.at(i) < otherInteger.number.at(i))
				return Integer(("-" + subtract(otherInteger.number, number)).c_str());
			else
				continue;
		}
	}
}

Integer Integer::operator* (const Integer& otherInteger) {
	return Integer(multiply(number, otherInteger.number).c_str());
}

Integer Integer::operator^ (const Integer& otherInteger) {
	return (Integer(power(*this, otherInteger).c_str()));
}

std::string Integer::add(std::string_view num1, std::string_view num2) {
	std::string tempAns;
	std::uint32_t arguend{ 0 }, addend{ 0 }, sum{ 0 }, remainder{ 0 };
	std::vector<char> num1AsVec,
					  num2AsVec;
	for (const auto& elem : num1) num1AsVec.push_back(elem);
	for (const auto& elem : num2) num2AsVec.push_back(elem);
	auto [iter1, iter2] = std::pair(num1AsVec.crbegin(), num2AsVec.crbegin());
	for (; iter1 != num1AsVec.crend() && iter2 != num2AsVec.crend(); ++iter1, ++iter2){
		arguend = numString.find(*iter1);
		addend = numString.find(*iter2);
		sum = (arguend + addend + remainder);
		remainder = 0;
		if (sum > 9) {
			remainder = sum / 10;
			sum = sum % 10;
		}
		tempAns += (std::to_string(sum));
	}
	if (remainder != 0) 
		tempAns += numString.substr(remainder,1);
	std::reverse(std::begin(tempAns), std::end(tempAns));
	return tempAns.c_str();
}

std::string Integer::subtract(std::string_view num1, std::string_view num2) {
	std::string tempAns;
	std::uint32_t minuend{ 0 }, subtrahend{ 0 }, difference{ 0 };
	std::vector<char> num1AsVec,
		              num2AsVec;
	for (const auto& elem : num1) num1AsVec.push_back(elem);
	for (const auto& elem : num2) num2AsVec.push_back(elem);
	auto [iter1, iter2] = std::pair(num1AsVec.rbegin(), num2AsVec.rbegin());
	for (; iter1 != num1AsVec.rend() && iter2 != num2AsVec.rend(); ++iter1, ++iter2) {
		minuend = numString.find(*iter1);
		subtrahend = numString.find(*iter2);
		if (minuend < subtrahend) {
			minuend += 10;
			++iter1;
			auto val = numString.find(*iter1);
			--val;
			char elem = std::to_string(val)[0];//this is extract the string as a character
			*iter1 = elem;
			--iter1;
		}
		difference = minuend - subtrahend;
		tempAns += std::to_string(difference);
	}
	if (tempAns.back() == '0') tempAns.pop_back();
	std::reverse(std::begin(tempAns), std::end(tempAns));
	return tempAns.c_str();
}

std::string Integer::multiply(std::string_view num1, std::string_view num2) {
	std::vector<char> multiplicand(std::size(num1)), multiplier(std::size(num2));
	for (size_t i{ 0 }; i < std::size(num1); ++i) multiplicand[i] = num1[i];
	for (size_t i{ 0 }; i < std::size(num2); ++i) multiplier[i] = num2[i];
	std::vector<std::string> product;
	auto result = 0, remainder = 0;
	std::string eachAns;
	for (auto i = std::crbegin(multiplier); i != std::crend(multiplier); ++i) {
		for (auto j = std::crbegin(multiplicand); j != std::crend(multiplicand); ++j) {
			result = ((numString.find(*i) * numString.find(*j)) + remainder) % 10;
			remainder = ((numString.find(*i) * numString.find(*j)) + remainder) / 10;
			eachAns += std::to_string(result);
		}
		if (remainder != 0) 
			eachAns += std::to_string(remainder);
		std::reverse(eachAns.begin(), eachAns.end());
		product.push_back(eachAns);
		eachAns.clear();
		remainder = 0;
	}
	//this fills the numbers with zeroes at the end so that the can be added without problems
	for (size_t i{ 1 }; i < product.size(); ++i)
		for (size_t j = 0; j < i; ++j)
			product.at(i).push_back('0');
	//vector of each row of product
	std::vector<Integer> numbersToAdd(std::size(product));
	//creaates a vector of Integer objects from each row of products 
	for (size_t i{ 0 }; i < std::size(product); ++i)
		numbersToAdd[i] = Integer(product[i].c_str());
	auto sumOfProducts = std::accumulate(numbersToAdd.begin(), numbersToAdd.end(), Integer("0"));//love this line
	return sumOfProducts.number;
}

std::string Integer::power(Integer num1,Integer num2) {
	auto powerInInt = std::stoull(num2.number);
	Integer duplicateBase = num1;
	for (size_t i{ 1 }; i < powerInInt; ++i) {
		num1 = num1 * duplicateBase;
	}
	return num1.number;
}

const Integer Integer::operator= (const Integer& otherInteger) {
	number.clear();
	number = otherInteger.number;
	return *this;
}

bool Integer::operator== (const Integer& otherInteger) {
	return (this->number == otherInteger.number) ? true : false;
}

std::ostream& operator<< (std::ostream& output, const Integer& otherInteger) {
	output << otherInteger.number;
	return output;
}
std::istream& operator>> (std::istream& input, Integer& otherInteger) {
	input >> otherInteger.number;
	auto tempObj = otherInteger;//throws exception if there is an error in the input
	return input;
}