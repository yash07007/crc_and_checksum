all: compile run

compile: 
	g++ -o crc_tx crc_tx.cpp
	g++ -o crc_rx crc_rx.cpp
	g++ -o crc_vs_checksum crc_vs_checksum.cpp
	
run:
	./crc_tx
	./crc_rx
	./crc_vs_checksum

clean:
	rm -f crc_tx
	rm -f crc_rx
	rm -f crc_vs_checksum
	rm -f ee*

build: clean
	tar cvf ee450_PA1_ysolanki.tar crc* Make* README*
	gzip ee450_PA1_ysolanki.tar