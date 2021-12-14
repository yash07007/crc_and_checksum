# CRC-and-Checksum

This repository has C++ implementation of CRC (Cyclic Redundancy Check) and Checksum.

<br/>

## Project Details

**Author:** Yash Solanki

**Project Description:** This project implements CRC (Cyclic Redenduncy Check) Algorithm and 1 Byte Checksum Algorithm. It compares how both the algorithms performs with different errors. Description of structure of files is as follows

-   `crc_rx.cpp` : This file implements CRC sender side which takes data bit binary input from file and prints corrosponding CRC bits.
-   `crc_tx.cpp` : This file implements CRC reciever side which takes codeword bits from the file and print if they pass the crc error check or not.
-   `crc_vs_checksum.cpp` : This file reads data bits and error masks from files and computes checksum and crc, introduce error and the again compute checksum and crc. It prints results from both checksum and crc for comparision of performance.
-   `MakeFile` : Implements commands to run all the files.
    - `make all` : Complile and run all files.
    - `make complie` : Complie all files.
    - `make run` : Run all files.
    - `make clean` : Delete all executeables.  
<br/>
