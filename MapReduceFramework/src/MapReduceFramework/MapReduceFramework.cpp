/*
 * @copyright 한국기술교육대학교 컴퓨터공학부 데이터베이스시스템
 * @version 2023학년도 2학기
 * @author 10조(김요셉, 박세현, 원현섭, 조승대)
 * MapReduceFramework.cpp
 */

#include "../MapReduceFramework/MapReduceFramework.h"

MapReduceFramework::MapReduceFramework(Mapper* m, Reducer* r) : mapper(m), reducer(r) {}

void MapReduceFramework::run(const std::vector<std::string>& input, std::vector<std::pair<std::string, int>>& output) {
    // TODO: MapReduce Framework 실행 로직 구현
}