/*
 * @copyright 한국기술교육대학교 컴퓨터공학부 데이터베이스시스템
 * @version 2023학년도 2학기
 * @author 10조(김요셉, 박세현, 원현섭, 조승대)
 * MapReduceFramework.h
 */

#ifndef MAPREDUCEFRAMEWORK_H_
#define MAPREDUCEFRAMEWORK_H_

#include "../MapReduceFramework/Mapper.h"
#include "../MapReduceFramework/Reducer.h"

#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <unordered_map>

class MapReduceFramework {
public:
    MapReduceFramework(Mapper* mapper, Reducer* reducer);
    void run(char* inputPath, char* outputPath);

private:
    void worker(char* inputPath, long start, long end, std::vector<std::pair<std::wstring, int>>& mapOutput);
    void reduceThread(const std::unordered_map<std::wstring, std::vector<int>>& shuffledResults, long start, long end, std::vector<std::pair<std::wstring, int>>& output);

    Mapper* mapper;
    Reducer* reducer;

    std::mutex m;
    std::mutex shuffledResultsMutex;
    std::condition_variable cv;
    std::vector<std::thread> mapWorkers;
    std::vector<std::thread> reduceWorkers;
    std::vector<std::pair<std::wstring, int>> mapOutput;
    std::unordered_map<std::wstring, std::vector<int>> shuffledResults;
};

#endif /* MAPREDUCEFRAMEWORK_H_ */
