OBJECTIVE:
 To understand the working of a scalar pipelined processor by simulating the different components of software level.

RUN AND EXECUTE THE CODE IN WINDOWS
 commands : g++ .\main.cpp 
 commands : ./a.exe --dcache FILE_DIRECTORY_OF_DCACHE --icache FILE_DIRECTORY_OF_ICACHE --rf FILE_DIRECTORY_OF_RF
 Then,
         Both DCache.txt file,output.txt will contain the expected results.These files will be newly formed or overwritten if previously exists.If you want to pass these files names use flags --dcacheout and --out respectively.
         
     FOR EXAMPLE:
       g++ .\main.cpp
       ./a.exe --dcache .\DCache.txt --icache .\ICache.txt --rf .\RF.txt

Directory Structure :
1) input
   1) ICache.txt
      This file contains the contexts of Instruction Cache.
   2) DCache.txt
      This file contains the contents of Data Cache.
   3) RF.txt 
      This file contains the contents of Register File.

2) output
   1) DCache.txt
      This file contains of Data Cache reflecting all changes applied during execution.
   2) Output.txt
      This file contains of information like number of instructions executed, number of instructions of each type(Arithmetic,Logical,Shitf,Memory,Control and Halt Instructions),CPI(clock cycles per instruction),number of stalls,number of stalls of each type(Data and Control stalls).

3) main.cpp
