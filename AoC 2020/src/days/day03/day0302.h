#pragma once

class Day0302
{
public:
	static void Run()
	{
		std::cout << "Day 3, answer 2: " << FindTrees() << std::endl;
	}

private:
	static const uint64_t FindTrees()
	{
		const auto& tree_map = Read("day03_input.txt");
		const size_t& row_size = tree_map.size();
		const size_t& col_size = tree_map[0].size();
		const std::array<const std::array<uint8_t, 2>, 5> slopes = {
			{{1, 1}, {3, 1}, {5, 1}, {7, 1}, {1, 2}}
		};
		std::array<uint32_t, 5> tree_counts = { 0, 0, 0, 0, 0 };

		uint8_t tree_count = 0;
		for (uint32_t slope_index = 0; slope_index < slopes.size(); slope_index++) {
			const auto& slope = slopes[slope_index];
			uint32_t x = slope[0];
			uint32_t y = slope[1];
			while (y < row_size) {
				if (x >= col_size) {
					x %= col_size;
				}
				if (tree_map[y][x] == '#') {
					tree_count++;
				}
				x += slope[0];
				y += slope[1];
			}
			tree_counts[slope_index] = tree_count;
			tree_count = 0;
		}
		uint64_t result = 1;
		for (const uint64_t& count : tree_counts) {
			result *= count;
		}
		return result;
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
				input.push_back(line);
			}
		}

		return input;
	}
};
