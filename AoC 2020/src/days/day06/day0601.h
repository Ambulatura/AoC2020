#pragma once

#include "utils.h"

class Day0601
{
public:
    static void Run()
    {
		std::cout << "Day 06, answer 1: " << YesQuestions() << std::endl;
	}

private:
    static const uint32_t YesQuestions()
    {
		uint32_t sum_of_yes_questions = 0;
		const auto& groups = Read("day06_input.txt");
		for (const std::string_view group : groups) {
			std::string answered_questions;
			for (const std::string_view yes_questions : split_string(group, "\n")) {
				for (const std::uint8_t yes_question : yes_questions) {
					if (std::find(answered_questions.begin(), answered_questions.end(), yes_question) == answered_questions.end()) {
						answered_questions += yes_question;
						sum_of_yes_questions++;
					}
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
