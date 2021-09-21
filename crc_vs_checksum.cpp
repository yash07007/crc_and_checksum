#include<iostream>
#include <fstream>
#include<string>
#include<cstdlib>
#include<cmath>

using namespace std;

// Utility function for doing XOR between teo equal length bit strings.
string XOR(string a, string b) {

    string result = "";
    int a_n, b_n;

    a_n = a.length(); 
    b_n = b.length();

    if (a_n == b_n) {
        for (int i = 0; i < a_n; i++)
        {
            if(a[i] == b[i]) {
                result += '0';
            }
            else {
                result += '1';
            }
        }
    }
    else {
        cout << "Incomatible bit size XOR operation a: " << a << " and b: " << b;
        exit(0);
    }

    return result;
}

// Function to perform a mudulo 2 divide, given two divident (data bits) and divisor (generator bits) bit strings.
string divideMod2(string data, string generator = "1100000001111") {
    
    string remiander;

    // Appending data with (genrator length - 1) zeros. 
    string appended_data = (data + string(generator.length() - 1, '0'));

    // i is window start index for a generator size window.
    // j is window end index for a generator size window.
    int i = 0;
    int j = generator.length();

    // Initial generator.length() bits
    string segment = appended_data.substr(i,j);

    // Until window bounds are within the data bits
    while (j < appended_data.length()) {
        
        // If MSB of data is 1 then xor divisor with divident segment and bring one bit down
        if (segment[0] == '1')
        {
            // XORing genrator length segment to genrator (divisor) and
            // bringing one bit down
            segment = XOR(segment,  generator) + appended_data[j];
            
        } 
        else 
        {
            // If MSB of data is 0 then just bring one bit down
            segment = segment + appended_data[j];
        }
        
        // Removing the MSB of segment+data sum as it is always 0
        segment = segment.substr(1,j);

        // Incrementing window end to move further.
        j += 1;
    }

    // Last XOR of remainder if MSB of remainder segment is 1
    if (segment[0] == '1')
        segment = XOR(segment, generator);

    // Again removing the MSB of segment+data sum as it is always 0
    remiander = segment.substr(1,j);

    return remiander;
}

// Utility funtion to convert a binary bit string to int.
int binToInt(string binString) {
    
    int decimal = 0;
    int pos = 0;
    for(int i = binString.length()-1; i>=0; i--){

        if(binString[i] == '1'){
            decimal += pow(2, pos);
        }
        pos++;

    }

    return decimal;
}

// Utility funtion to convert int to a binary bit string.
string intToBin(int decimal) {

    string binString = "";
    int mask = 1;
    for(int i = 0; i < 8; i++)
    {
        if((mask&decimal) >= 1)
            binString = "1" + binString;
        else
            binString = "0" + binString;
        mask<<=1;
    }

    return binString;
}

// Funtion to perform a 1 Byte checksum for giving binary bit stream in string form.
string checksum(string data) {

    int Q, R, sum = 0, checksum;

    // Take 8 bits => 1 byte at a time, 
    // convert one byte to int (decimal) & 
    // sum all obtained decimals.
    for (int i = 0; i < data.length(); i=i+8)
    {   
        int d;

        string binaryString = data.substr(i,8);

        d = binToInt(binaryString);

        sum += d;
    }

    // Clip remainder to 0-255.
    // Q = sum / 255;
    R = sum % 255;

    while(R > 255) {
        // Q = (Q + R) / 256;
        // R = (Q + R) % 256;
        R = R % 256;
    }

    // Take one's complement of clipped remainder.
    checksum = 255 - R;

    // Convert int back to binary string form and return.
    return intToBin(checksum);
    
}

int main() {

    ifstream myfile;
    string line, data_bits, error_bits;
    // CRC_12 Generator
    string generator = "1100000001111";
    
    myfile.open("dataVs.txt");

    if (myfile.is_open()) {

        while ( getline(myfile, line) )
        {
            
            // Divide data bits and error bits from  input file in to respective variables
            for (int i = 0; i < line.length(); i++)
            {
                if(line[i] == ' ') {
                    data_bits = line.substr(0, i);
                    error_bits = line.substr(i+1, line.length() - i);
                    break;
                }
            }


            // Sender Side

            string crc, chksum;
            string chksum_codeword, crc_codeword;

            // Calculate Checksum.
            chksum = checksum(data_bits);

            // Calculate CRC.
            crc = divideMod2(data_bits, generator);

            // Creating codewords.
            chksum_codeword = data_bits + chksum;
            crc_codeword = data_bits + crc;

            

            // Transfering through channel.
            //............
            
            // Masking errors bits from the file to codewords while in transmission medium.
            string transit_chksum_codeword, transit_crc_codeword;
            transit_chksum_codeword = XOR(chksum_codeword, error_bits);
            transit_crc_codeword = XOR(crc_codeword, error_bits + "0000");

            //............


            // Reciever Side.
            string rcvd_chksum_codeword, rcvd_crc_codeword;
            
            rcvd_chksum_codeword =  transit_chksum_codeword;
            rcvd_crc_codeword = transit_crc_codeword;

            // Checking if crc detects errors which were introduced.
            string new_crc, crc_result = "pass";
            
            // Computing if recieved codeword is divisible by generator.
            // New crc thus obtaned should be all 0s if its divisible.
            new_crc = divideMod2(rcvd_crc_codeword, generator);

            for (int i = 0; i < new_crc.length(); i++)
            {
                if(new_crc[i]  == '1') {
                    crc_result = "not pass";
                    break;
                }
            }

            // Checking if checksum detects errors which were introduced.
            string new_chksum, chksum_result = "pass";
            string recv_data, recv_checksum;

            // Spliting recieved checksum codeword into data and checksum
            recv_data = rcvd_chksum_codeword.substr(0, rcvd_chksum_codeword.length() - 8);
            recv_checksum = rcvd_chksum_codeword.substr(rcvd_chksum_codeword.length() - 8, 8);

            // Calculating new checksum
            new_chksum = checksum(recv_data);

            // Checking if new checksum is equal to recieved checksum
            if(new_chksum != recv_checksum) {
                chksum_result = "not pass";
            }

            // Printing Comparision
            cout << "crc : " << crc << "  result: " << crc_result <<"\n";
            cout << "checksum: " << chksum << "  result: " << chksum_result <<"\n";
            cout << endl;
        }
        myfile.close();
    }
    else {
        cout << "Unable to open file \n";
    }
	
    return 0;
}