#pragma once

static std::vector<std::string> split_string(const std::string_view str, const std::string_view delimeter)
{
	std::vector<std::string> splitted;
	size_t next = 0;
	size_t last = 0;
	std::string token = "";
	while (next < str.length()) {
		next = str.find(delimeter, last);
		token = str.substr(last, next - last);
		last = next + delimeter.length();
		splitted.push_back(std::move(token));
	}
	return splitted;
}
