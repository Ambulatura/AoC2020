#pragma once

class Day0101
{
public:
	static void Run()
	{
		std::cout << "Day 1, answer 1: " << Sum2020Product() << std::endl;
	}

private:
	Day0101() {}

	static const uint32_t Sum2020Product()
	{
		const auto& numbers = Read("day01_input.txt");

		for (uint32_t i = 0; i < numbers.size(); i++) {
			for (uint32_t j = i + 1; j < numbers.size(); j++) {
				if (numbers[i] + numbers[j] == 2020) {
					return numbers[i] * numbers[j];
				}
			}
		}

		return 0;
	}
	static const std::vector<uint32_t> Read(const std::string& file_path)
	{
		std::ifstream file(file_path);
		std::vector<uint32_t> input;

		if (!file.is_open()) {
			std::cout << "Failed to open file!" << std::endl;
		}
		else {
			uint32_t number;
			while (file >> number) {
				input.push_back(number);
			}
		}

		return input;
	}
};
