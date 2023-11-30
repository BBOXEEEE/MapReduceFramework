/*
 * @copyright 한국기술교육대학교 컴퓨터공학부 데이터베이스시스템
 * @version 2023학년도 2학기
 * @author 10조(김요셉, 박세현, 원현섭, 조승대)
 * WordCountMapper.cpp
 */

#include "../MapReduceFramework/Mapper.h"

#include <sstream>
#include <iostream>
#include <vector>

class WordCountMapper : public Mapper {
private:
	std::wstring word;
	int one = 1;
public:
	void map(const std::wstring& input, std::vector<std::pair<std::wstring, int>>& output) {
		std::wistringstream iss(input);
		while (iss >> word) {
			output.push_back({word, one}); // @suppress("Invalid arguments")
		}
	}
};
