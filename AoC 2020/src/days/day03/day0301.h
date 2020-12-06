#pragma once

class Day0301
{
public:
	static void Run()
	{
		std::cout << "Day 3, answer 1: " << FindTrees() << std::endl;
	}

private:
	Day0301() {}

	static const uint32_t FindTrees()
	{
		const auto& tree_map = Read("day03_input.txt");
		const size_t row_size = tree_map.size();
		const size_t col_size = tree_map[0].size();

		uint32_t x = 3;
		uint32_t y = 1;
		uint32_t tree_count = 0;
		while (y < row_size) {
			if (x >= col_size) {
				x %= col_size;
			}
			if (tree_map[y][x] == '#') {
				tree_count++;
			}
			x += 3;
			y += 1;
		}

		return tree_count;
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
