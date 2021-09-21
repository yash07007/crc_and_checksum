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
	rm crc_tx
	rm crc_rx
	rm crc_vs_checksum