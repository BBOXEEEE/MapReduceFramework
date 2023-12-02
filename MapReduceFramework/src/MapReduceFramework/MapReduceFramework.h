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
    MapReduceFramework(Mapper* mapper, Reducer* reducer) : mapper(mapper), reducer(reducer) {} ;
    void run(char* inputPath, char* outputPath);

private:
    Mapper* mapper;
    Reducer* reducer;
    std::mutex m;
    std::vector<std::thread> mapWorkers;
    std::vector<std::thread> reduceWorkers;
    std::vector<std::pair<std::string, int>> mapOutput;
    std::unordered_map<std::string, std::vector<int>> shuffledOutput;

    void mapWorker(const std::vector<std::string>& lines, std::vector<std::pair<std::string, int>>& mapOutput) {
    	for (const auto& line : lines) {
    			{
    				std::lock_guard<std::mutex> lock(m);
    				mapper->map(line, mapOutput);
    			}
    		}
    }

    void reduceWorker(const std::unordered_map<std::string, std::vector<int>>& shuffledResults, long start, long end, std::vector<std::pair<std::string, int>>& output) {
    	long count = 0;

    	for (const auto& entry : shuffledResults) {
    		if (count >= start && count < end) {
    			const std::string& key = entry.first;
    			const std::vector<int>& values = entry.second;

    			int reducedValue = 0;
    			reducer->reduce(key, values, reducedValue);
    			{
    				std::lock_guard<std::mutex> lock(m);
    				output.push_back({key, reducedValue}); // @suppress("Invalid arguments")
    			}
    		}
    		++count;
    	}
    }
};

#endif /* MAPREDUCEFRAMEWORK_H_ */
