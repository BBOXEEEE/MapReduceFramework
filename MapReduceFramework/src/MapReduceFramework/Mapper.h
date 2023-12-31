/*
 * @copyright 한국기술교육대학교 컴퓨터공학부 데이터베이스시스템
 * @version 2023학년도 2학기
 * @author 10조(김요셉, 박세현, 원현섭, 조승대)
 * Mapper.h
 */

#ifndef MAPPER_H_
#define MAPPER_H_

#include <string>
#include <vector>

template <typename InputType, typename MapOutputKey, typename MapOutputValue>
class Mapper {
public:
	virtual ~Mapper() = default;
	virtual void map(const std::string& input, std::vector<std::pair<std::string, int>>& output) = 0;
};

#endif /* MAPPER_H_ */
