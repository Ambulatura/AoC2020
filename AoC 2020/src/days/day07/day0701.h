#pragma once

#include "utils.h"

class Day0701
{
public:
    static void Run()
    {
		std::cout << "Day 7, answer 1: " << ShinyGoldBags() << std::endl;
	}

private:
    static const uint32_t ShinyGoldBags()
    {
		const auto& input = Read("day07_input.txt");
		std::unordered_map<std::string, std::vector<std::tuple<uint8_t, std::string>>> bags_graph = ParseRules(input);
		std::unordered_map<std::string_view, std::vector<std::string_view>> flattened_graph;
		uint32_t shiny_gold_bags = 0;
		
		for (const auto& bags : bags_graph) {
			flatten_graph(bags.first, bags.first, bags_graph, flattened_graph);
		}
		
		for (const auto& bags : flattened_graph) {
			for (const auto& contained : bags.second) {
				if (contained == "shinygold") {
					shiny_gold_bags++;
				}
			}
		}
		
		return shiny_gold_bags;
	}

	static void flatten_graph(const std::string& contain, const std::string& root_bag,
							  std::unordered_map<std::string, std::vector<std::tuple<uint8_t, std::string>>>& bags_graph,
							  std::unordered_map<std::string_view, std::vector<std::string_view>>& flattened_graph)
	{
		for (const auto& [number, contained] : bags_graph[contain]) {
			if (std::find(flattened_graph[root_bag].begin(),
						  flattened_graph[root_bag].end(),
						  contained) != flattened_graph[root_bag].end()) { continue; }
			flattened_graph[root_bag].push_back(contained);
			flatten_graph(contained, root_bag, bags_graph, flattened_graph);
		}
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
				
				if (contained[0] == 'n') {
					bags_graph[contain].push_back(std::make_tuple(0, ""));
				} else {
					bags_graph[contain].push_back(std::make_tuple(contained[0], contained.substr(1)));
				}

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
