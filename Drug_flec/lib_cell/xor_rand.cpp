#include "xor_rand.hpp"
#include <stdint.h>

xor_rand::xor_rand(unsigned int seed, unsigned int id) {

	reset(seed, id);
}

double xor_rand::gen_rand() {
	unsigned int t = (xx ^ (xx << 11));
	xx = yy;
	yy = zz;
	zz = ww;
	return ( ww = (ww ^ (ww >> 19)) ^ (t ^ (t >> 8)) ) / (double)(UINT_MAX);
}

unsigned int xor_rand::gen_rand_uint() {
	unsigned int t = (xx ^ (xx << 11));
	xx = yy;
	yy = zz;
	zz = ww;
	return ( ww = (ww ^ (ww >> 19)) ^ (t ^ (t >> 8)) );
}

void xor_rand::reset(unsigned int seed, unsigned int id) {

	xx = 123456789 + id + seed;
	yy = 362436069 + id * 100 + seed * 10;
	zz = 521288629 + id * 1000 + seed * 100;
	ww = 88675123 + id * 10000 + seed * 1000;

	for (int i = 0; i < 1000; i++)
		gen_rand();
}

xor_rand256::xor_rand256(uint64_t seed, uint64_t id) {
	// MAX_U_INT_64 = std::numeric_limits<uint64_t>::max();
	reset(seed, id);
}

double xor_rand256::gen_rand() {

	double a = gen_rand_uint() / double(0xFFFFFFFFFFFFFFFF);
	// std::cout << a;
	return a;
}

uint64_t xor_rand256::gen_rand_uint() {
	const uint64_t result = rotl(s[0] + s[3], 23) + s[0];

	const uint64_t t = s[1] << 17;

	s[2] ^= s[0];
	s[3] ^= s[1];
	s[1] ^= s[2];
	s[0] ^= s[3];

	s[2] ^= t;

	s[3] = rotl(s[3], 45);

	return result;
}

inline uint64_t next(uint64_t x) {
	uint64_t z = (x += 0x9e3779b97f4a7c15);
	z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
	z = (z ^ (z >> 27)) * 0x94d049bb133111eb;
	return z ^ (z >> 31);
}

void xor_rand256::reset(uint64_t seed, uint64_t id) {
	// initialize s[0-3] with defined values;
	
	uint64_t x = seed * 1000000 + id * 100;

	s[0] = next(x);
	s[1] = next(s[0]);
	s[2] = next(s[1]);
	s[3] = next(s[2]);

	for (int i = 0; i < 1000; i++)
		gen_rand_uint();
}

void xor_rand256::long_jump(void) {
	static const uint64_t LONG_JUMP[] = { 0x76e15d3efefdcbbf, 0xc5004e441c522fb3, 0x77710069854ee241, 0x39109bb02acbe635 };

	uint64_t s0 = 0;
	uint64_t s1 = 0;
	uint64_t s2 = 0;
	uint64_t s3 = 0;
	for (int i = 0; i < sizeof LONG_JUMP / sizeof * LONG_JUMP; i++)
		for (int b = 0; b < 64; b++) {
			if (LONG_JUMP[i] & UINT64_C(1) << b) {
				s0 ^= s[0];
				s1 ^= s[1];
				s2 ^= s[2];
				s3 ^= s[3];
			}
			gen_rand();
		}

	s[0] = s0;
	s[1] = s1;
	s[2] = s2;
	s[3] = s3;
}
