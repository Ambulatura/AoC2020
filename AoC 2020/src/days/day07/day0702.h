#pragma once

#include "utils.h"

class Day0702
{
public:
    static void Run()
    {
		std::cout << "Day 07, answer 2: " << BagsInsideShinyGoldBag() << std::endl;
	}

private:
    static const uint32_t BagsInsideShinyGoldBag()
    {
		const auto& input = Read("day07_input.txt");
		std::unordered_map<std::string, std::vector<std::tuple<uint8_t, std::string>>>& bags_graph = ParseRules(input);

		const uint32_t bags_inside_shiny_gold_bag = CountBags("shinygold", bags_graph);

		return bags_inside_shiny_gold_bag;
	}

	static uint32_t CountBags(const std::string& contain,
							  std::unordered_map<std::string, std::vector<std::tuple<uint8_t, std::string>>>& bags_graph)
	{
		uint32_t counter = 0;
		for (const auto& [number, contained] : bags_graph[contain]) {
			counter += number - '0';
			counter += (number - '0') * CountBags(contained, bags_graph);
		}
		return counter;
	}

	static std::unordered_map<std::string, std::vector<std::tuple<uint8_t, std::string>>> ParseRules(const std::vector<std::string>& input)
	{
		std::unordered_map<std::string, std::vector<std::tuple<uint8_t, std::string>>> bags_graph;

		for (const auto& rule : input) {
			auto& words = split_string(rule, "contain");
			std::string& contain = words[0];
			std::string& containeds = words[1];
			replace_substring(contain, "bags", "");
			remove_character(contain, ' ');

			auto& containeds_splitted = split_string(containeds, ", ");
			for (uint32_t i = 0; i < containeds_splitted.size(); i++) {
				std::string& contained = containeds_splitted[i];
				replace_substring(contained, "bags?", "");
				remove_character(contained, ' ');
				if (i == containeds_splitted.size() - 1)
					remove_character(contained, '.');
				if (contained[0] == 'n')
					contained[0] = '0';

				bags_graph[contain].push_back(std::make_tuple(contained[0], contained.substr(1)));
			}
		}
		return bags_graph;
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

			while (std::getline(file, line)) {
				if (!line.empty())
					input.push_back(std::move(line));
			}
		}
		return input;
	}
};
