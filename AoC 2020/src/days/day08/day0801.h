#pragma once

class Day0801
{
public:
    static void Run()
    {
		std::cout << "Day 8, answer 1: " << CalculateAccumulatorValue() << std::endl;
	}

private:
	static const uint32_t CalculateAccumulatorValue()
	{
		auto& boot_codes = Read("day08_input.txt");
		std::vector<uint32_t> processed_codes;
		uint32_t index = 0;
		int32_t accumulator = 0;

		while (true) {
			const auto& [operation_code, value] = boot_codes[index];

			if (std::find(processed_codes.begin(), processed_codes.end(), index) != processed_codes.end()) {
				return accumulator;
			}
			processed_codes.push_back(index);

			switch (operation_code) {
			case 1 << 0: {	// nop
				index++;
				break;
			}
			case 1 << 1: {	// jmp
				index += value;
				break;
			}
			case 1 << 2: {	// acc
				accumulator += value;
				index++;
				break;
			}
			default:
				break;
			}
		}
		return 0;
	}

	static std::unordered_map<uint32_t, std::tuple<uint8_t, int32_t>> Read(const std::string& file_path)
    {
		std::ifstream file(file_path);
		std::unordered_map<uint32_t, std::tuple<uint8_t, int32_t>> input;

		if (!file.is_open()) {
			std::cout << "Failed to open file!" << std::endl;
		}
		else {
			std::unordered_map<std::string, uint8_t> operation_codes = {
				{"nop", 1 << 0}, {"jmp", 1 << 1}, {"acc", 1 << 2},
			};
			uint32_t number = 0;
			std::string operation;
			int32_t value;

			while (file >> operation >> value) {
				input[number++] = std::make_tuple(operation_codes[operation], value);
			}
		}
		return input;
	}



};
