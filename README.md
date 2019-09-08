# 28874Decoder
A small utility written in C code that aims to decode the NV item 00028874.
The NV item 00028874 is used in the last Qualcomm modems to specify the supported carrier aggregations.

This is one of the tools used to get the data you can find on my own site [smartphonecombo.it](https://smartphonecombo.it) and [cacombos.com](https://cacombos.com).  
If the data you have obtained thanks to this tool are not on either of the two sites, [contact me](mailto:handymenny@outlook.com) or [the administrators of cacombos.com](https://mt-tech.fi/en/contact/). Thanks :)

# Build Instructions
```bash
git clone https://github.com/HandyMenny/28874Decoder
cd 28874Decoder/src
make
```
 
 # Run Instructions
 Before running 28874Decoder you have to decompres yours 00028874. There are several ways to do this, below you will find some:  
 * `$ binwalk -e 00028874`
 * `$ openssl zlib -d -in 00028874 -out unpacked`
 * `$ printf "\x1f\x8b\x08\x00\x00\x00\x00\x00" | cat - 00028874 | gzip -dc > unpacked`  
 
 Most likely in the future 28874Decoder will be able to decompress automatically.  
   
 After decompression just run:  
`./src/28874Decoder [path_to_unpacked_00028874]`  
  
# How to interpret the output
The Carrier Aggregation Combos are written in a format similar to that used by Qualcomm in the carrier_policy.xml.  
For each combo there is a list of bands separated by a dash.  
For each bands the first number indicates the lte band, the first letter the Bandwidth Class DL, the second number the Supported MIMO Capability DL, the second letter the Bandwidth Class UL (if absent this band is not used for UL).
At the end of each combo there is a number indicating the maximum number of DL streams and a possible asterisk which if present indicates the presence of Upload Carrier Aggregation.  

Further information about carrier aggregations: [3GPP](https://www.3gpp.org/technologies/keywords-acronyms/101-carrier-aggregation-explained "3GPP - Carrier Aggregation Explained") and [nivuk](http://niviuk.free.fr/lte_ca_band.php "nivuk - LTE Carrier Aggregation")


# License
Licensed under the MIT license - See [LICENSE](../LICENSE) for details.

