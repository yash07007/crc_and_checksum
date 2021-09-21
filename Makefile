all: compile run

compile: 
	g++ -o crc_tx crc_tx.cpp
	g++ -o crc_tx crc_rx.cpp
	g++ -o crc_tx crc_vs_checksum.cpp
	
run:
	./crc_tx.cpp
	./crc_rx.cpp
	./crc_vs_checksum.cpp

clean:
	rm crc_tx
	rm crc_rx
	rm crc_vs_checksum