#include<iostream>
#include <fstream>
#include<string>
#include<cstdlib>

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

int main() {

    ifstream myfile;
    string data_bits;
    // CRC_12 Generator
    string generator = "1100000001111";
    
    myfile.open("dataTx.txt");

    if (myfile.is_open()) {

        // Read data bits from the file line by line
        while ( getline(myfile,data_bits) )
        {

            string crc, codeword;

            // Obtain CRC bits by dividing data bits with generator
            crc = divideMod2(data_bits, generator);

            // Create codeword.
            codeword = data_bits + crc;

            // Print codeword and crc bits.
            cout << "codeword: " << codeword << "\n";
            cout << "crc: " << crc << "\n";

        }
        myfile.close();
    }
    else {
        cout << "Unable to open file \n";
    }
	
    return 0;
}