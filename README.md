# HLS memory performance tester
This IP core should be used to test memory performance from the FPGA. It performs random read accesses to the memory and parses memory content as next address. In order for this IP to work the memory content must be initialized with ramdom values reflecting address offsets. It returns the sum of all tested addresses to cross check against a CPU if data got lost. 

## Software Requirements
* Linux host machine for make
* Vivado/Vitis 2020.1

## How to build ip core
* make

## How to use ip core
* Set the correct clock and device in file script.tcl
* Initialize memory contents with a CPU for the HLS ip core to perform read transactions
* Set start address offset and size by using the axi slave control port
* Use return value checksum to cross check against CPU value to see if data got lost