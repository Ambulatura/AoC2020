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

static void remove_character(std::string& str, const uint8_t character)
{
	str.erase(std::remove(str.begin(), str.end(), character), str.end());
}

static void replace_substring(std::string& str, const std::string& substr, const std::string& replace_str)
{
	std::regex pattern(substr);
	str = std::regex_replace(str, pattern, replace_str);
}

static std::vector<uint32_t> find_numbers_in_string(const std::string_view str)
{
	std::vector<uint32_t> number_indices;
	const std::string_view digits = "0123456789";
	for (uint32_t i = 0; i < digits.length(); i++) {
		for (uint32_t j = 0; j < str.length(); j++) {
			if (digits[i] == str[j]) 
				number_indices.push_back(j);
		}
	}
	std::sort(number_indices.begin(), number_indices.end());
	return number_indices;
}
