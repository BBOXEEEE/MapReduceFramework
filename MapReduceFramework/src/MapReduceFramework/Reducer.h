/*
 * @copyright 한국기술교육대학교 컴퓨터공학부 데이터베이스시스템
 * @version 2023학년도 2학기
 * @author 10조(김요셉, 박세현, 원현섭, 조승대)
 * Reducer.h
 */

#ifndef REDUCER_H_
#define REDUCER_H_

#include <string>
#include <vector>

template <typename MapOutputKey, typename MapOutputValue, typename OutputKey, typename OutputValue>
class Reducer {
public:
	virtual ~Reducer() = default;
	virtual void reduce(const std::string& key, const std::vector<int>& values, int& output) = 0;
};

#endif /* REDUCER_H_ */
