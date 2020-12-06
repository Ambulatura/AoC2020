#pragma once

class Day0201
{
public:
	static void Run()
	{
		std::cout << "Day 2, answer 1: " << ValidPasswords() << std::endl;
	}

private:
	Day0201() {}

	static const uint32_t ValidPasswords()
	{
		uint32_t valid_passwords_count = 0;
		const auto& input = Read("day02_input.txt");
		for (const auto& [lower, upper, character, password] : input) {
			uint32_t character_count = 0;
			for (const auto& c : password) {
				if (c == character) {
					character_count++;
				}
			}
			if (character_count >= lower && character_count <= upper) {
				valid_passwords_count++;
			}
		}

		return valid_passwords_count;
	}

	static const std::vector<std::tuple<uint32_t, uint32_t, uint8_t, std::string>> Read(const std::string& file_path)
	{
		std::ifstream file(file_path);
		std::vector<std::tuple<uint32_t, uint32_t, uint8_t, std::string>> input;

		if (!file.is_open()) {
			std::cout << "Failed to open file!" << std::endl;
		}
		else {
			uint8_t trash;
			uint32_t lower;
			uint32_t upper;
			uint8_t character;
			std::string password;
			while (file >> lower >> trash >> upper >> character >> trash >> password) {
				input.push_back(std::make_tuple(lower, upper, character, password));
			}
		}

		return input;
	}
};
