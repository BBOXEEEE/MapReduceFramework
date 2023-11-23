/*
 * @copyright 한국기술교육대학교 컴퓨터공학부 데이터베이스시스템
 * @version 2023학년도 2학기
 * @author 10조(김요셉, 박세현, 원현섭, 조승대)
 * WordCount.cpp
 */

#include "../MapReduceFramework/MapReduceFramework.h"
#include "../WordCount/WordCountMapper.cpp"
#include "../WordCount/WordCountReducer.cpp"

#include <iostream>
#include <vector>

int main(int argc, char* argv[]) {
	WordCountMapper mapper;
	WordCountReducer reducer;
	MapReduceFramework framework(&mapper, &reducer);

	framework.run(argv[1], argv[2]);
}
