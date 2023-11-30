/*
 * @copyright 한국기술교육대학교 컴퓨터공학부 데이터베이스시스템
 * @version 2023학년도 2학기
 * @author 10조(김요셉, 박세현, 원현섭, 조승대)
 * MapReduceFramework.cpp
 */

#include "../MapReduceFramework/MapReduceFramework.h"

#include <iostream>
#include <mutex>
#include <thread>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <unordered_map>
#include <ctime>

MapReduceFramework::MapReduceFramework(Mapper* m, Reducer* r) : mapper(m), reducer(r) {}


void MapReduceFramework::worker(char* inputPath, long start, long end, std::vector<std::pair<std::string, int>>& output) {
	std::ifstream inputFile(inputPath);
	if (!inputFile.is_open()) {
		std::cerr << "Error: Unable to open file " << inputPath << std::endl;
		return;
	}

	inputFile.seekg(start);
	std::string line;
	long currentLine = 0;
	while (getline(inputFile, line) && currentLine < end) {
		std::lock_guard<std::mutex> lock(m);
		mapper->map(line, output);
		++currentLine;
	}

	inputFile.close();
}

void MapReduceFramework::reduceThread(const std::unordered_map<std::string, std::vector<int>>& shuffledResults, std::vector<std::pair<std::string, int>>& output) {
    for (const auto& entry : shuffledResults) {
        const std::string& key = entry.first;
        const std::vector<int>& values = entry.second;
        int reducedValue = 0;
        reducer->reduce(key, values, reducedValue);
        std::lock_guard<std::mutex> lock(m);
        output.push_back({key, reducedValue}); // @suppress("Invalid arguments")
    }
}

void MapReduceFramework::run(char* inputPath, char* outputPath) {
	clock_t start, end;
	double duration;

	start = clock();

	// 파일 읽고 파일 사이즈 구하기
	std::ifstream inputFile(inputPath, std::ios::ate);
	if (!inputFile.is_open()) {
		std::cerr << "Error: Unable to open file " << inputPath << std::endl;
		return;
	}
	long fileSize = inputFile.tellg();
	inputFile.close();

	// 사용 가능한 코어 개수 확인
	const int numThreads = std::thread::hardware_concurrency()/2;
	const long blockSize = fileSize / numThreads;

	std::cout << "============ MapReduce Start! ============" << std::endl;
	std::cout << " Input File Size : " << static_cast<double>(fileSize) / (1024 * 1024) << "MB" << std::endl;
	std::cout << " Number of Block : " << numThreads << std::endl;
	std::cout << " Block Size : " << static_cast<double>(blockSize) / (1024 * 1024) << "MB" << std::endl;
	std::cout << "==========================================" << std::endl;

	std::cout << "map 0%, reduce = 0%" << std::endl;
	for (int i=0; i<numThreads; ++i) {
		long start = i * blockSize;
		long end = (i == numThreads - 1) ? fileSize : (i + 1) * blockSize;
		mapWorkers.push_back(std::thread(&MapReduceFramework::worker, this, inputPath, start, end, std::ref(mapOutput)));
	}

	for (auto& worker : mapWorkers) {
		worker.join();
	}
	std::cout << "map 100%, reduce = 0%" << std::endl;
	std::cout << "map output size : " << mapOutput.size() << std::endl;

	for (const auto& pair : mapOutput) {
		const std::string& key = pair.first;
		int value = pair.second;
		{
			std::lock_guard<std::mutex> lock(shuffledResultsMutex);
			shuffledResults[key].push_back(value);
		}
	}
	std::cout << "shuffledResult size : " << shuffledResults.size() << std::endl;

	for (int i = 0; i < numThreads; ++i) {
		reduceWorkers.emplace_back(&MapReduceFramework::reduceThread, this, std::cref(shuffledResults), std::ref(output));
	}

	for (auto& worker : reduceWorkers) {
		worker.join();
	}
	std::cout << "map 100%, reduce = 100%" << std::endl;
	std::cout << "reduce output size : " << output.size() << std::endl;

	/* 한줄씩 읽어서 처리
	std::ifstream inputFile(inputPath);
	if (!inputFile.is_open()) {
		std::cerr << "Error: Unable to open file " << inputPath << std::endl;
		m.unlock();
		return;
	}
	std::cout << "map 0%, reduce = 0%" << std::endl;
	std::string line;
	while (getline(inputFile, line)) {
		mapper->map(line, mapOutput);
	}
	std::cout << "map 100%, reduce = 0%" << std::endl;
	std::cout << "map output size : " << mapOutput.size() << std::endl;
		inputFile.close();
	for (const auto& pair : mapOutput) {
		const std::string& key = pair.first;
		int value = pair.second;
		{
			std::lock_guard<std::mutex> lock(shuffledResultsMutex);
			shuffledResults[key].push_back(value);
		}
	}
	std::cout << "shuffledResult size : " << shuffledResults.size() << std::endl;

	for (const auto& entry : shuffledResults) {
		const std::string& key = entry.first;
		const std::vector<int>& values = entry.second;
		int reducedValue = 0;
		reducer->reduce(key, values, reducedValue);
		std::lock_guard<std::mutex> lock(m);
		output.push_back({key, reducedValue}); // @suppress("Invalid arguments")
	}
	std::cout << "map 0%, reduce = 100%" << std::endl;
	std::cout << "reduce output size : " << output.size() << std::endl;
	*/

	// 파일에 쓰기
	std::ofstream outputFile(outputPath);
	if (!outputFile.is_open()) {
	    std::cerr << "Error: Unable to open output file." << std::endl;
	    return;
	}
	for (const auto& pair : output) {
		outputFile << pair.first << "     " << pair.second << std::endl;
	}

	end = clock();
	duration = (double)(end-start) / CLOCKS_PER_SEC;
	std::cout << "MapReduce Jobs Launched!" << std::endl;
	std::cout << "Runtime : " << duration << "s" << std::endl;
}
