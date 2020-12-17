#pragma once

#include "utils.h"

class Day0602
{
public:
    static void Run()
    {
		std::cout << "Day 06, answer 2: " << YesQuestions() << std::endl;
	}

private:
    static const uint32_t YesQuestions()
    {
		uint32_t sum_of_yes_questions = 0;
		const auto& groups = Read("day06_input.txt");
		for (const std::string_view group : groups) {
			uint32_t people_in_group = 0;
			std::unordered_map<uint8_t, uint32_t> answered_questions;
			for (const std::string_view yes_questions : split_string(group, "\n")) {
				if (yes_questions.empty()) continue;
				people_in_group++;
				for (const std::uint8_t yes_question : yes_questions)
					answered_questions[yes_question] += 1;
			}
			for (const auto& answered_question : answered_questions) {
				if (answered_question.second == people_in_group) {
					sum_of_yes_questions++;
				}
			}
		}
		return sum_of_yes_questions;
	}

	static const std::vector<std::string> Read(const std::string& file_path)
    {
		std::ifstream file(file_path);
		std::vector<std::string> input;

		if (!file.is_open()) {
			std::cout << "Failed to open file!" << std::endl;
		}
		else {
			std::string text;
			std::string line;

			while (std::getline(file, line)) {
				text += line + '\n';
				if (line.empty()) {
					input.push_back(text);
					text.clear();
				}
			}
		}
		return input;
    }
};
