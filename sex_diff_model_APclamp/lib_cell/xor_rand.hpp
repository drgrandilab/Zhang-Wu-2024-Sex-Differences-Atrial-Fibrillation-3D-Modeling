#ifndef XOR_RAND_HPP
#define XOR_RAND_HPP

#define _USE_MATH_DEFINES
#include <cmath>
#include <climits>
#include <cstdint>
#include <iomanip>
#include <stdint.h>

class xor_rand
{
public:
	xor_rand(unsigned int seed = 0, unsigned int id = 0);
	~xor_rand() {};

	double gen_rand();
	void reset(unsigned int seed, unsigned int id);

	unsigned int gen_rand_uint();

	unsigned long int xx, yy, zz, ww;
};


class xor_rand256
{
public:
	uint64_t s[4];
	const static uint64_t MAX_U_INT_64 = UINT64_MAX; // std::numeric_limits<std::uint64_t>::max(); 

	xor_rand256(uint64_t seed = 0, uint64_t id = 0);
	~xor_rand256() {};
	static inline uint64_t rotl(const uint64_t x, int k) {
		return (x << k) | (x >> (64 - k));
	}

	double gen_rand();
	void reset(uint64_t seed, uint64_t id);

	uint64_t gen_rand_uint();
	void long_jump(void);




};
#endif
