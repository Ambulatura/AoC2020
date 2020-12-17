#pragma once

class Day0901
{
public:
    static void Run()
    {
		std::cout << "Day 9, answer 1: " << InvalidNumber() << std::endl;
	}

private:
	static const uint32_t InvalidNumber()
	{
		const auto& numbers = Read("day09_input.txt");
		const uint32_t invalid_number = AttackXMASData(numbers, 25);

		return invalid_number;
	}

	static const uint32_t AttackXMASData(const std::vector<uint32_t>& numbers, const uint8_t preamble)
	{
		uint32_t start = 0;
		uint32_t end = preamble;
		uint32_t invalid_number = 0;

		while (!invalid_number) {
			uint32_t target_number = numbers[end];
			bool found_number = false;
			for (uint32_t i = start; i < end; i++) {
				for (uint32_t j = i + 1; j < end; j++) {
					if (numbers[i] + numbers[j] == target_number) {
						found_number = true;
						break;
					}
				}
				if (found_number)
					break;
			}
			if (!found_number)
				invalid_number = target_number;
			else {
				start++;
				end++;
			}
		}
		return invalid_number;
	}

	static std::vector<uint32_t> Read(const std::string& file_path)
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
