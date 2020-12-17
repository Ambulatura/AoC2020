#pragma once

class Day0902
{
public:
    static void Run()
    {
		std::cout << "Day 9, answer 2: " << EncryptionWeakness() << std::endl;
	}

private:
	static const uint32_t EncryptionWeakness()
	{
		const auto& numbers = Read("day09_input.txt");
		const uint32_t invalid_number = AttackXMASData(numbers, 25);
		const uint32_t encryption_weakness = FindEncryptionWeakness(numbers, invalid_number);

		return encryption_weakness;
	}

	static const uint32_t FindEncryptionWeakness(const std::vector<uint32_t>& numbers, const uint32_t invalid_number)
	{
		std::vector<uint32_t> weak_numbers;
		uint32_t sum_of_weak_numbers = 0;
		bool found_weak_numbers = false;
		uint32_t encryption_weakness = 0;

		for (uint32_t i = 0; i < numbers.size(); i++) {
			for (uint32_t j = i; j < numbers.size(); j++) {
				if (sum_of_weak_numbers == invalid_number) {
					found_weak_numbers = true;
					break;
				}
				else {
					weak_numbers.push_back(numbers[j]);
					sum_of_weak_numbers += numbers[j];
				}
			}
			if (found_weak_numbers) {
				std::sort(weak_numbers.begin(), weak_numbers.end());
				encryption_weakness = weak_numbers[0] +  weak_numbers[weak_numbers.size() - 1];
				break;
			}
			else {
				weak_numbers.clear();
				sum_of_weak_numbers = 0;
			}
		}
		return encryption_weakness;
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
				if (found_number) break;
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
