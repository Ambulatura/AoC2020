#pragma once

class Day0202
{
public:
	static void Run()
	{
		std::cout << "Day 02, answer 2: " << ValidPasswords() << std::endl;
	}

private:
	static const uint32_t ValidPasswords()
	{
		uint32_t valid_passwords_count = 0;
		const auto& input = Read("day02_input.txt");
		for (const auto& [lower, upper, character, password] : input) {
			if ((password[lower - 1] == character) ^ (password[upper - 1] == character)) {
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
