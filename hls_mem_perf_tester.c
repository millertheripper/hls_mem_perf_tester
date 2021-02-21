#include "hls_mem_perf_tester.h"
#include <stdint.h>
#include <string.h>

const int m_axi_depth = TEST_SIZE;

uint64_t hls_mem_perf_tester(volatile uint32_t *addr, uint32_t size)
{
#pragma HLS INTERFACE m_axi depth=m_axi_depth offset=slave port=addr bundle=MASTER
#pragma HLS INTERFACE s_axilite port=size bundle=SLAVE_ARG

	uint32_t next = 0;
	uint64_t sum = 0;

	for (uint32_t i=0; i<size/sizeof(uint32_t); i++) {
#pragma HLS PIPELINE
		next = addr[next];
		sum = sum+next;
	}

	return sum;
}
