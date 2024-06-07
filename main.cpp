#include <bits/stdc++.h>
#include <fstream>

using namespace std;

int icache[256],dcache[256],rf[16];
bool reg[16];
bool flag = false;
int PC=0;
int t_ins=0,arith_ins=0,log_ins=0,shift_ins=0,mem_ins=0,load_ins=0,cont_ins=0,halt_ins=0,ncycles=0,nstalls=0,data_stls=0,cont_stls=0;
bool canfetch=true,halt=false;

class instruction{
    private:
    int opcode,RD,RS1,RS2,storePC;
    int rs1,rs2,imm,ALUoutput;
    int LMD;
    bool isstall=false;

    public:
    int stagecount=0;

    bool check(int &x,int regid){
        if(reg[regid]){
            isstall=false;
            x = rf[regid];
        }
        else{
            isstall = true;
        }
        return isstall;
    }
    
    void IF(){
        opcode = (icache[PC]>>4)&15;
        RD = (icache[PC])&15;
        RS1 = (icache[PC+1]>>4)&15;
        RS2 = (icache[PC+1])&15;
        PC = PC +2;
        storePC = PC;
        stagecount=1;
    }

    void ID(){
        if(opcode==0){              
            if(check(rs1,RS1) ==false && check(rs2,RS2)==false){
            reg[RD] = false;
            }else{
                return;
            }
        }
        else if(opcode==1){              
            if(check(rs1,RS1) ==false && check(rs2,RS2)==false){
            reg[RD] = false;
            }else{
                return;
            }
        }
        else if(opcode==2){              
            if(check(rs1,RS1) ==false && check(rs2,RS2)==false){
            reg[RD] = false;
            }else{
                return;
            }
        }
        else if(opcode==3){                                     
            if(check(rs1,RD)==false){
            reg[RD] = false;
            }else{
                return;
            }
        }
        else if(opcode==4){              
            if(check(rs1,RS1) ==false && check(rs2,RS2)==false){
            reg[RD] = false;
            }else{
                return;
            }
        }
        else if(opcode==5){              
            if(check(rs1,RS1) ==false && check(rs2,RS2)==false){
            reg[RD] = false;
            }else{
                return;
            }
        }
        else if(opcode==6){              
            if(check(rs1,RS1) ==false && check(rs2,RS2)==false){
            reg[RD] = false;
            }else{
                return;
            }
        }
        else if(opcode==7){                                     
            if(check(rs1,RD)==false){
            reg[RD] = false;
            }else{
                return;
            }
        }
        else if(opcode==8){                                     
            if(check(rs1,RS1)==false){
            imm = RS2;
            reg[RD] = false;
            }else{
                return;
            }
        }
        else if(opcode==9){                                     
            if(check(rs1,RS1)==false){
            imm = RS2;
            reg[RD] = false;
            }else{
                return;
            }
        }
        else if(opcode==10){                                     
            imm = (RS1<<4)+RS2;
            reg[RD] = false;
        }
        else if(opcode==11){                                     
            if(check(rs1,RS1)==false){
            imm = RS2;
            reg[RD] = false;
            }else{
                return;
            }
        }
        else if(opcode==12){                                     
            if(check(rs1,RD)==false && check(rs1,RS1)==false){
            imm = RS2;
            }else{
                return;
            }
        }
        else if(opcode==13){                                     
            imm = (RD<<4)+RS1;
            canfetch=false;
        }
        else if(opcode==14){
            if(check(rs1,RD)==false){
                imm = (RS1<<4)+RS2;
                canfetch = false;
            }else{
                return;
            }
        }
        else if (opcode==15){
            halt=true;
        }
        stagecount++;
    }

    void EX(){
        if(opcode == 0){
            ALUoutput = rs1 + rs2;
            reg[RD] = false;
        }
        else if (opcode == 1){
            ALUoutput = rs1  - rs2;
            reg[RD]= false;
        }
        else if (opcode == 2){
            ALUoutput = rs1*rs2;
            reg[RD]= false;
        }
        else if (opcode == 3){
            ALUoutput = rs1+1;
            reg[RD]= false;
        }
        else if (opcode == 4){
            ALUoutput = rs1 & rs2;
            reg[RD]= false;
        }
        else if (opcode == 5){
            ALUoutput = rs1 | rs2;
            reg[RD]= false;
        }
        else if (opcode == 6){
            ALUoutput = rs1^rs2;
            reg[RD]= false;
        }
        else if (opcode == 7){
            ALUoutput = ~rs1;
            reg[RD]= false;
        }
        else if (opcode == 8){
            ALUoutput = rs1 << imm;
            reg[RD]= false;
        }
        else if (opcode == 9){
            ALUoutput = rs1 >> imm;
            reg[RD]= false;
        }
        else if (opcode == 10){
            ALUoutput = imm;
            reg[RD]= false;
        }
        else if (opcode == 11){
            ALUoutput = rs1 + imm;
            reg[RD]= false;
        }
        else if (opcode == 12){
            ALUoutput = rs1+ imm ;
        }
        else if (opcode == 13){
            if(imm<128)ALUoutput = storePC + 2*imm;
            else ALUoutput = storePC - (256-imm)*2;
            PC = ALUoutput;
            canfetch = false;
            flag = true;
        }
        else if (opcode == 14){
            if(imm<128)ALUoutput = storePC + 2*imm;
            else ALUoutput = storePC - (256-imm)*2;
            if(!rs1){
                PC = ALUoutput;
            }
            canfetch = false;
            flag = true;
        }
        else if (opcode == 15){

        }
        stagecount++;
    }

    void MEM(){
        if(opcode == 10){
            LMD = imm;
        }
        else if(opcode == 11){
            LMD = dcache[ALUoutput];
        }
        else if (opcode == 12){
            dcache[ALUoutput] = rf[RD];
        }
        stagecount++;
    }
    
    void WB(){
        if(opcode<10){
            rf[RD] = ALUoutput;
            reg[RD] = true;
        }
        else if (opcode<12 && opcode >=10){
            rf[RD] = LMD;
            reg[RD] =true;
        }
        stagecount++;

        if(opcode < 4){
            arith_ins++;
        }
        else if (opcode < 8){
            log_ins++;
        }
        else if (opcode < 10){
            shift_ins++;
        }
        else if(opcode ==10){
            load_ins++;
        }
        else if (opcode < 13){
            mem_ins++;
        }
        else if (opcode <15){
            cont_ins++;
        }
        else {
            halt_ins++;
        }
    }

    bool post_stage(){
        if(stagecount == 1){
            ID();
        }
        else if (stagecount == 2){
            EX();
        }
        else if (stagecount == 3){
            MEM();
        }
        else if (stagecount == 4){
            WB();
        }
        return isstall;
    }
};

int main(){
    queue <instruction> Q;
    instruction ins;
    int a,b=0;
    string str;
    ifstream ifile1;
    ifstream ifile2;
    ifstream ifile3;
    ifile1.open("input/ICache.txt");
    for(int i=0;i<256;i++){
        ifile1 >> std::hex >>str;
        icache[i]=stoi(str,nullptr,16);
    }
    ifile1.close();

    ifile2.open("input/DCache.txt");
    for(int i=0;i<256;i++){
        ifile2 >> std::hex >>a;
        dcache[i]=a;
    }
    ifile2.close();

    ifile3.open("input/RF.txt");
    for(int i=0;i<16;i++){
        ifile3 >> std::hex >>a;
        rf[i]=a;
    }
    ifile3.close();

    for(int i=0;i<16;i++){
        reg[i] = true;
    }

    do{
        int stalls = 0;
        ncycles++;
        unsigned long n = Q.size();
        for (int i = 0; i < n; i++) {
            ins = Q.front();
            stalls += ins.post_stage();
            Q.pop();
            if (ins.stagecount < 5) {
                Q.push(ins);
            }
        }
        if (!canfetch) {
            nstalls++;
            cont_stls++;
            if(flag){
                flag = false;
                canfetch = true;
            }
        }
        else if (stalls) {
            nstalls++;
            data_stls++;
        }
        else if(!halt){
            t_ins++;
            ins.IF();
            Q.push(ins);
        }

    }while (!Q.empty());

    ofstream ofile;

    ofile.open("output/Output.txt");

    ofile << "Total number of instructions executed: " << t_ins <<endl;
    ofile << "Number of instructions in each class     " << endl;
    ofile << "Arithmetic instructions              : " << arith_ins << endl;
    ofile << "Logical instructions                 : " << log_ins << endl;
    ofile << "Shift instructions                   : " << shift_ins << endl;
    ofile << "Memory instructions                  : " << mem_ins << endl;
    ofile << "Load immediate instructions          : " << load_ins << endl;
    ofile << "Control instructions                 : " << cont_ins << endl;
    ofile << "Halt instructions                    : " << halt_ins << endl;
    ofile << "Cycles Per Instruction               : " << (double)(1.0*ncycles/t_ins) << endl;
    ofile << "Total number of stalls               : " << nstalls << endl;
    ofile << "Data stalls (RAW)                    : " << data_stls << endl;
    ofile << "Control stalls                       : " << cont_stls << endl;
    ofile.close();

    ofile.open("output/DCache.txt");
    for(int i=0;i<256;i+=1){
        int temp = (dcache[i]&0xff);
        if(dcache[i] >= 16)ofile<<std::hex<<temp<<endl;
        else ofile<<"0"<<std::hex<<temp<<endl;
    }
    ofile.close();
}
