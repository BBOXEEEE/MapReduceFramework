/*
 * @copyright 한국기술교육대학교 컴퓨터공학부 데이터베이스시스템
 * @version 2023학년도 2학기
 * @author 10조(김요셉, 박세현, 원현섭, 조승대)
 * MapReduceFramework.h
 */
#pragma once
#include "../MapReduceFramework/Mapper.h"
#include "../MapReduceFramework/Reducer.h"

#include <vector>

class MapReduceFramework {
public:
    MapReduceFramework(Mapper* mapper, Reducer* reducer);
    void run(char* inputPath, char* outputPath);
    // TODO : run 메소드의 인자 수정
private:
    Mapper* mapper;
    Reducer* reducer;
};
