#include <stdio.h>
#include <stdlib.h>
#include "hls_mem_perf_tester.h"

uint32_t test_data[TEST_SIZE];

uint32_t mem_init_rand(uint32_t *addr, uint32_t size, uint32_t seed)
{
	srand(seed);

	printf("Initialize memory ... \r\n");
	for (uint32_t i=0; i<size/sizeof(uint32_t); i++) {
		addr[i] = rand()%(size/sizeof(uint32_t));
		printf("  addr[%u]=%u\r\n", i, addr[i]);
	}
	printf("Done.\r\n");

	return 0;
}

uint32_t mem_init_seq(uint32_t *addr, uint32_t size)
{
	printf("Initialize memory ... \r\n");
	for (uint32_t i=0; i<size/sizeof(uint32_t); i++) {
		addr[i] = i+1;
		printf("  addr[%u]=%u\r\n", i, addr[i]);
	}

	printf("Done.\r\n");
	return 0;
}

uint64_t checksum_calc(uint32_t *addr, uint32_t size)
{
	uint32_t next = 0;
	uint64_t csum = 0;

	printf("Calculate checksum ... \r\n");
	for (uint32_t i=0; i<size/sizeof(uint32_t); i++) {
		next = addr[next];
		csum += next;
		printf("  addr[%u]=%u\r\n", next, addr[next]);
	}
	printf("Done. csum: %lld \r\n", csum);

	return csum;
}

int main(void)
{
	/* Two test szenarios: Either use sequential addressing, or random */
	//mem_init_rand(test_data, sizeof(test_data), 0x13371337);
	mem_init_seq(test_data, sizeof(test_data));

	uint64_t checksum_test = checksum_calc(test_data, sizeof(test_data));
	printf("Checksum test: %llu\r\n", checksum_test);

	uint64_t checksum_hls = hls_mem_perf_tester(test_data, sizeof(test_data));
	printf("Checksum hls : %llu\n", checksum_hls);

	if (checksum_test != checksum_hls) {
		printf("Test: FAILED!\r\n");
	}
	else {
		printf("Test: PASSED!\r\n");
	}
	
	return 0;
}





