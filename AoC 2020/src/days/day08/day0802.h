#pragma once

class Day0802
{
public:
    static void Run()
    {
		std::cout << "Day 8, answer 2: " << AccumulatorValueAfterTerminate() << std::endl;
	}

private:
	static const uint32_t AccumulatorValueAfterTerminate()
	{
		auto& boot_codes = Read("day08_input.txt");
		std::vector<uint32_t> processed_codes;
		std::vector<uint32_t> changed_codes;
		bool is_code_changed = false;
		bool terminated = false;
		bool found_accumulator_after_terminate = false;
		uint32_t index = 0;
		int32_t accumulator = 0;

		while (!terminated || !found_accumulator_after_terminate) {
			const auto& [operation_code, value] = boot_codes[index];

			if (std::find(processed_codes.begin(), processed_codes.end(), index) != processed_codes.end()) {
				accumulator = 0;
				is_code_changed = false;
				processed_codes.clear();
			}
			processed_codes.push_back(index);

			switch (operation_code) {
			case 1 << 0: {	// nop
				if (!is_code_changed && std::find(changed_codes.begin(), changed_codes.end(), index) == changed_codes.end()) {
					is_code_changed = true;
					changed_codes.push_back(index);
					index += value;
				}
				else
					index++;
				break;
			}
			case 1 << 1: {	// jmp
				if (!is_code_changed && std::find(changed_codes.begin(), changed_codes.end(), index) == changed_codes.end()) {
					is_code_changed = true;
					changed_codes.push_back(index);
					index++;
				}
				else
					index += value;
				break;
			}
			case 1 << 2: {	// acc
				accumulator += value;
				index++;
				break;
			}
			default:
				if (!terminated) {
					const auto code_that_should_change  = changed_codes[changed_codes.size() - 1];
					auto& [o_code, _val] = boot_codes[code_that_should_change];
					if (o_code == 1 << 0)
						o_code = 1 << 1;
					else
						o_code = 1 << 0;

					index = 0;
					accumulator = 0;
					processed_codes.clear();
					changed_codes.clear();
					is_code_changed = true;
					terminated = true;
				}
				else
					found_accumulator_after_terminate = true;
				break;
			}
		}
		return accumulator;
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
