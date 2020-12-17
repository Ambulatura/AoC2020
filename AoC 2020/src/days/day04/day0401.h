#pragma once

#include "utils.h"

class Day0401
{
public:
	static void Run()
	{
		std::cout << "Day 04, answer 1: " << ValidPassports() << std::endl;
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
			uint8_t binary_form = 0;
			for (const std::string_view field : split_string(passport, " ")) {
				const auto& field_code = fields.find(field.substr(0, 3));
				if (field_code != fields.end())
					binary_form |= field_code->second;
			}
			if (IsValid(binary_form)) {
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
