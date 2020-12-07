#pragma once

#include "utils.h"

class Day0402
{
public:
    static void Run()
    {
		std::cout << "Day 4, answer 2: " << ValidPassports() << std::endl;
    }

private:
    static const uint32_t ValidPassports()
    {
		const auto& passports = Read("day04_input.txt");
		const std::unordered_map<std::string_view, uint8_t> fields = {
			{"byr", 1 << 0}, {"iyr", 1 << 1}, {"eyr", 1 << 2}, {"hgt", 1 << 3},
			{"hcl", 1 << 4}, {"ecl", 1 << 5}, {"pid", 1 << 6}, {"cid", 1 << 7},
		};

		uint32_t valid_passports_count = 0;

		for (const std::string_view passport : passports) {
			if (passport.empty()) continue;
			std::unordered_map<std::uint8_t, std::string> saved_fields;
			uint8_t binary_form = 0;
			for (const std::string& field : split_string(passport, " ")) {
				if (field.empty()) continue;
				const auto& field_code = fields.find(field.substr(0, 3));
				const std::string& field_value = field.substr(4, field.length() - 1);
				if (field_code != fields.end()) {
					binary_form |= field_code->second;
					saved_fields[field_code->second] = field_value;
				}
			}
			if (IsValid(binary_form)) {
				bool is_value_valid = true;
				for (const auto& field : saved_fields) {
					if(!IsValueValid(field.first, field.second)) {
						is_value_valid = false;
						break;
					}
				}
				if (is_value_valid)
					valid_passports_count++;
			}
		}

		return valid_passports_count;
    }

    static const bool IsValid(const uint8_t binary_form)
    {
		const uint8_t mask = (1 << 7) - 1; // 127, 01111111
		return (binary_form & mask) == mask;
    }

    static const bool IsValueValid(const uint8_t field_code, const std::string& field_value)
    {
		switch (field_code) {
		case 1 << 0: {
			const auto birth_year = std::stoi(field_value);
			if (birth_year >= 1920 && birth_year <= 2002)
				return true;
			else
				return false;
			break;
		}
		case 1 << 1: {
			const auto issue_year = std::stoi(field_value);
			if (issue_year >= 2010 && issue_year <= 2020)
				return true;
			else
				return false;
			break;
		}
		case 1 << 2: {
			const auto expiration_year = std::stoi(field_value);
			if (expiration_year >= 2020 && expiration_year <= 2030)
				return true;
			else
				return false;
			break;
		}
		case 1 << 3: {
			const auto& height_type = field_value.substr(field_value.length() - 2, field_value.length() - 1);
			if (height_type == "cm") {
				const auto height = std::stoi(field_value);
				if (height >= 150 && height <= 193)
					return true;
				else
					return false;
			}
			else if (height_type == "in") {
				const auto height = std::stoi(field_value);
				if (height >= 59 && height <= 76)
					return true;
				else
					return false;
			}
			else
				return false;
			break;
		}
		case 1 << 4: {
			const std::regex hair_regex("#.[^abcdef0-9]");
			if (field_value.length() == 7 && !std::regex_match(field_value, hair_regex))
				return true;
			else
				return false;
			break;
		}
		case 1 << 5: {
			const std::regex eye_regex("amb|blu|brn|gry|grn|hzl|oth");
			if (std::regex_match(field_value, eye_regex))
				return true;
			else
				return false;
			break;
		}
		case 1 << 6: {
			const std::regex pid_regex("[^0-9]");
			if (field_value.length() == 9 && !std::regex_match(field_value, pid_regex))
				return true;
			else
				return false;
			break;
		}
		case 1 << 7:
			return true;
		default:
			return false;
		}
	}

    static const std::vector<std::string> Read(const std::string& file_path)
    {
		std::ifstream file(file_path);
		std::vector<std::string> input;

		if (!file.is_open()) {
			std::cout << "Failed to open file!" << std::endl;
		}
		else {

			std::string line;
			std::string text;

			while (std::getline(file, line)) {
				text += line + ' ';
				if (line.empty()) {
					text += '\n';
				}
			}
			input = split_string(text, "\n");
		}
		return input;
    }
};
