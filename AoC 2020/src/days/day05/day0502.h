#pragma once

class Day0502
{
public:
    static void Run()
    {
		std::cout << "Day 5, answer 2: " << MySeatID() << std::endl;
	}

private:
    static const uint32_t MySeatID()
    {
		std::vector<uint32_t> seat_ids;
		const auto& boarding_passes = Read("day05_input.txt");
		for (const std::string_view boarding_pass : boarding_passes) {
			const std::string_view row = boarding_pass.substr(0, 7);
			const std::string_view column = boarding_pass.substr(7, 10);
			const auto row_number = DecodeBoardingPass(row, 0, 0, 127);
			const auto column_number = DecodeBoardingPass(column, 0, 0, 7);
			const uint32_t seat_id = CalculateSeatID(row_number, column_number);
			seat_ids.push_back(seat_id);
		}

		uint32_t my_seat_id = 0;
		for (uint32_t seat_id = *std::min_element(seat_ids.begin(), seat_ids.end()); seat_id <= *std::max_element(seat_ids.begin(), seat_ids.end()); seat_id++) {
			if (std::find(seat_ids.begin(), seat_ids.end(), seat_id) == seat_ids.end()) {
				my_seat_id = seat_id;
				break;
			}
		}

		return my_seat_id;
	}

	static const uint32_t CalculateSeatID(const uint32_t row, const uint32_t column)
	{
		return row * 8 + column;
	}

	static const uint8_t DecodeBoardingPass(const std::string_view boarding_pass, const uint8_t index, const uint8_t lower_bound, const uint8_t upper_bound)
	{
		if (boarding_pass[index] == 'F' || boarding_pass[index] == 'L') {
			if (upper_bound - lower_bound == 1)
				return lower_bound;
			else {
				return DecodeBoardingPass(boarding_pass, index + 1, lower_bound, (lower_bound + upper_bound) / 2);
			}
		}
		else if (boarding_pass[index] == 'B' || boarding_pass[index] == 'R') {
			if (upper_bound - lower_bound == 1)
				return upper_bound;
			else {
				const uint8_t half = (lower_bound + upper_bound + 1) / 2;
				const uint8_t lower = half % 2 == 0 ? half : half - 1;
				return DecodeBoardingPass(boarding_pass, index + 1, lower, upper_bound);
			}
		}
		return 0;
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

			while (file >> line) {
				if (!line.empty())
					input.push_back(line);
			}
		}
		return input;
    }
};
