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

int main() {
	WordCountMapper mapper;
	WordCountReducer reducer;
	MapReduceFramework framework(&mapper, &reducer);

	/*
	* TODO : WordCount 예제를 실행하도록 MapReduceFramework.run() 메소드 호출
	* 1) Input File Path & Output File Path 입력
	* 2) MapReduceFramework.run()
	*/

}
