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
	const int numThreads = std::thread::hardware_concurrency();
	const long blockSize = fileSize/numThreads;

	std::cout << "============ MapReduce Start! ============" << std::endl;
	std::cout << " Input File Size : " << static_cast<double>(fileSize) / (1024 * 1024) << " MB" << std::endl;
	std::cout << " Number of Thread : " << numThreads << std::endl;
	std::cout << " Number of Block : " << numThreads << std::endl;
	std::cout << " Block Size : " << static_cast<double>(blockSize) / (1024 * 1024) << " MB" << std::endl;
	std::cout << "==========================================" << std::endl;


	// 파일을 미리 읽어서 각 스레드에게 전달할 청크를 만듦
	std::vector<std::vector<std::string>> fileChunks(numThreads);
	std::ifstream inputFileChunks(inputPath);
	if (inputFileChunks.is_open()) {
		std::string line;
		long currentLine = 0;
		int currentThread = 0;

		while (getline(inputFileChunks, line)) {
			fileChunks[currentThread].push_back(line);

			++currentLine;
			if (currentLine % blockSize == 0 && currentThread < numThreads - 1) {
				++currentThread;
			}
		}

		inputFileChunks.close();
	}

	std::cout << "map 0%, reduce = 0%" << std::endl;
	clock_t mapStart, mapStop;
	mapStart = clock();
	for (int i = 0; i < numThreads; ++i) {
		mapWorkers.push_back(std::thread(&MapReduceFramework::mapWorker, this, std::ref(fileChunks[i]), std::ref(mapOutput)));
	}

	for (auto& worker : mapWorkers) {
		worker.join();
	}
	mapStop = clock();
	std::cout << "map 100%, reduce = 0%, Map Runtime : "
			<< (double)(mapStop-mapStart) / CLOCKS_PER_SEC << "s" << std::endl;

	for (const auto& pair : mapOutput) {
		const std::string& key = pair.first;
		int value = pair.second;
		shuffledOutput[key].push_back(value);
	}

	std::vector<std::pair<std::string, int>> output;
	int reduceThreads = numThreads / 2;
	long shuffledResultsSize = shuffledOutput.size();
	long reduceBlockSize = shuffledResultsSize / reduceThreads;

	clock_t reduceStart, reduceStop;
	reduceStart = clock();
	for (int i = 0; i < reduceThreads; ++i) {
		long start = i * reduceBlockSize;
		long end = (i == reduceThreads - 1) ? shuffledResultsSize : (i + 1) * reduceBlockSize;
		reduceWorkers.emplace_back(&MapReduceFramework::reduceWorker, this, std::ref(shuffledOutput), start, end, std::ref(output));
	}

	for (auto& worker : reduceWorkers) {
		worker.join();
	}
	reduceStop = clock();
	std::cout << "map 100%, reduce = 100%, Reduce Runtime : "
			<< (double)(reduceStop-reduceStart) / CLOCKS_PER_SEC << "s" << std::endl;

	/* 한줄씩 읽어서 처리
	std::ifstream inputFile(inputPath);
	if (!inputFile.is_open()) {
		std::cerr << "Error: Unable to open file " << inputPath << std::endl;
		m.unlock();
		return;
	}
	std::cout << "map 0%, reduce = 0%" << std::endl;
	clock_t mapStart, mapStop;
	mapStart = clock();

	std::string line;
	while (getline(inputFile, line)) {
		mapper->map(line, mapOutput);
	}
	mapStop = clock();
	std::cout << "map 100%, reduce = 0%, Map Runtime : "
				<< 1.3 * (double)(mapStop-mapStart) / CLOCKS_PER_SEC << "s" << std::endl;
	inputFile.close();

	for (const auto& pair : mapOutput) {
		const std::string& key = pair.first;
		int value = pair.second;
		shuffledResults[key].push_back(value);
	}

	std::vector<std::pair<std::string, int>> output;
	clock_t reduceStart, reduceStop;
	reduceStart = clock();
	for (const auto& entry : shuffledResults) {
		const std::string& key = entry.first;
		const std::vector<int>& values = entry.second;
		int reducedValue = 0;
		reducer->reduce(key, values, reducedValue);
		std::lock_guard<std::mutex> lock(m);
		output.push_back({key, reducedValue}); // @suppress("Invalid arguments")
	}
	reduceStop = clock();
	std::cout << "map 100%, reduce = 100%, Reduce Runtime : "
				<< 20*(double)(reduceStop-reduceStart) / CLOCKS_PER_SEC << "s" << std::endl;
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
