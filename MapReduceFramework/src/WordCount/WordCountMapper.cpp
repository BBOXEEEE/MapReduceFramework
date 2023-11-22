/*
 * @copyright 한국기술교육대학교 컴퓨터공학부 데이터베이스시스템
 * @version 2023학년도 2학기
 * @author 10조(김요셉, 박세현, 원현섭, 조승대)
 * WordCountMapper.cpp
 */

#include "../MapReduceFramework/Mapper.h"

#include <sstream>
#include <iostream>

class WordCountMapper : public Mapper {
public:
	void map(const std::string& input, std::vector<std::pair<std::string, int>>& output) {
		// TODO : map 메소드 수정 -> 구분자를 통해 split, 단어별 <key, value> 쌍으로 output.push_back
		std::istringstream iss(input);
		std::string word;
		while (iss >> word) {
			output.push_back({word, 1});
		}
	}
};

