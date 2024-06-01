#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std; //可以不用打std

int vector_find(std::vector<string> function_and,string temp){
    for(unsigned int i=0;i<function_and.size();i++){
        if(function_and[i] == temp){
            return i;
        }
    }
    return -1;
}

template<class T>
void vector_show(std::vector<T> show_vector){
    for (unsigned int i=0;i<show_vector.size();i++){
        cout << show_vector[i] << " ";
    }
    cout << endl;
}

string module_name(string input_temp){
    size_t LP = 0;
    string MN;

    input_temp.erase(std::remove(input_temp.begin(),input_temp.end(),' '),input_temp.end()); // 去除空格

    if((LP = input_temp.find("(")) != string::npos) MN = input_temp.substr(0,LP);

    cout << "MN:" << MN << endl;
    return MN;
}

void IO(string input_temp,std::vector<string> &IO){ // output N22,N23;
    size_t comma = 0;

    input_temp.erase(std::remove(input_temp.begin(),input_temp.end(),' '),input_temp.end()); // 去除空格
    
    if ((comma = input_temp.rfind(";")) != string::npos) input_temp = input_temp.substr(0,comma);
    else input_temp = input_temp.substr(0,input_temp.rfind(","));
    // cout << input_temp << endl;

    while((comma = input_temp.find(",")) != string::npos){
        IO.push_back(input_temp.substr(1,comma-1)); // 不保留標頭1
        input_temp = input_temp.substr(comma+1);
    }

    IO.push_back(input_temp.substr(1)); // 最後一PIN 不保留標頭

    // vector_show(IO);
}

std::vector<string> parentheses_disassemble(string input_temp){ // NAND2_1 (N10, N1, N3);
    size_t LP = 0,comma = 0;
    vector<string> PIN;

    input_temp = input_temp.substr(0,input_temp.rfind(")")); // 保留)之前,工作站讀檔還會有\n
    input_temp.erase(std::remove(input_temp.begin(),input_temp.end(),' '),input_temp.end()); // 去除空格

    // cout << input_temp << endl;

    if((LP = input_temp.find("(")) != string::npos){
        input_temp = input_temp.substr(LP+1);

        // input_temp.erase(std::remove(input_temp.begin(),input_temp.end(),' '),input_temp.end()); // 去除空格

        while((comma = input_temp.find(",")) != string::npos){
            PIN.push_back(input_temp.substr(1,comma-1)); // 不保留標頭1
            input_temp = input_temp.substr(comma+1);
        }

        PIN.push_back(input_temp.substr(1)); // 最後一PIN 不保留標頭
    }

    // vector_show(PIN);
    return PIN;
}

// g++ -std=c++11 108303518_PA1.cpp -o test
// g++ -std=c++11 108303518_PA1.cpp -o 108303518_PA1.out
// ./test c17.v c17.bench
// ./108303518_PA1.out c17.v c17.bench

// g++ -Wall 108303518_PA1.cpp

// /home/CAD112/abc-master/abc
// cec c17.bench c17_ans.bench

int main(int argc,char *argv[]){

    for(int i=0;i<argc;i++){
        cout << argv[i] << endl;
    }

    vector<string> INPUT,OUTPUT,WIRE,GATE_NAME,GATE_PIN_temp;
    // INPUT：記錄所有輸入node、OUTPUT：記錄所有輸出node、WIRE：記錄其他node
    // GATE_NAME：與GATE_NUM配對，記錄出現的GATE種類名稱
    // GATE_PIN_temp：暫存運算PIN結果
    // 根據ISCAS’85規則,有八種GATE：and,nand,or,nor,xor,xnor,buf,not

    vector<int> GATE_NUM; // 與GATE_NAME配對，記錄GATE種類分別的數量

    string input_temp,MN,gate_name,keyword_temp;
    // input_temp：暫存讀檔讀行結果、MN：module名稱、gate_name：暫存GATE種類名稱、keyword_temp：暫存find關鍵字
    size_t keyword = 0; // keyword：暫存find關鍵字位置

    int index = 0,temp = 0,gate_num = 0,line_num = 0,line_counter = 0,state = 0;
    // index：暫存關鍵字在vector的位置、temp：暫存INPUT、OUTPUT vector長度、gate_num：紀錄GATE總數
    // line_num：紀錄讀了幾行(讀行計數器)、line_counter：關閉讀行計數器、state：暫存讀檔狀態

    enum state_name{Home,Module,Input,Output,Wire}; // state_name：標示state狀態

    // 檔名宣告 ------------------------------------------------------------
    ifstream inClientFile(argv[1], ios::in);
    if (!inClientFile){
		cerr << "input file could not be opened" << endl;
		exit(EXIT_FAILURE);
	}

    ofstream outClientFile(argv[2], ios::out);
	if (!outClientFile){
		cerr << "output file could not be opened" << endl;
		exit(EXIT_FAILURE);
	}

    // input讀檔 ------------------------------------------------------------

    while (getline(inClientFile, input_temp)){ // 逐行讀取
        if(!line_counter) line_num += 1; // 讀行計數器

        // cout << input_temp << endl;

        if((keyword = input_temp.find("endmodule")) != string::npos){ // endmodule
            inClientFile.seekg(0); // 回到讀取文檔開頭
            break;
        }

        if(input_temp.length() > 1){ // 不為空行
            // cout << "state:" << state << endl;
            switch(state){
            case Module:
                if((keyword = input_temp.find(";")) != string::npos){
                    state = Home;
                }

                break;
            
            case Input:
                IO(input_temp,INPUT);

                if((keyword = input_temp.find(";")) != string::npos){
                    cout << "INPUT|" << INPUT.size() << "|:"; // 顯示vector元素數
                    vector_show(INPUT);

                    state = Home;
                }

                break;

            case Output:
                IO(input_temp,OUTPUT);

                if((keyword = input_temp.find(";")) != string::npos){
                    cout << "OUTPUT|" << OUTPUT.size() << "|:"; // 顯示vector元素數
                    vector_show(OUTPUT);

                    state = Home;
                }

                break;

            case Wire:
                IO(input_temp,WIRE);

                if((keyword = input_temp.find(";")) != string::npos){
                    cout << "WIRE|" << WIRE.size() << "|:"; // 顯示vector元素數
                    vector_show(WIRE);

                    state = Home;
                }

                break;

            default:
                if((keyword = input_temp.find("module")) != string::npos){ // module
                    keyword_temp = "module";
                    input_temp = input_temp.substr(keyword + keyword_temp.length()); // module
                    // cout << input_temp << endl;

                    MN = module_name(input_temp);

                    if((keyword = input_temp.find(";")) == string::npos) state = Module;
                }
                else if((keyword = input_temp.find("input")) != string::npos){ // input
                    keyword_temp = "input";
                    input_temp = input_temp.substr(keyword + keyword_temp.length()); // 去掉input
                    // cout << input_temp << endl;

                    IO(input_temp,INPUT);

                    if((keyword = input_temp.find(";")) != string::npos){
                        cout << "INPUT|" << INPUT.size() << "|:"; // 顯示vector元素數
                        vector_show(INPUT);
                    }
                    else{
                        state = Input;
                    }
                }
                else if((keyword = input_temp.find("output")) != string::npos){ // output
                    keyword_temp = "output";
                    input_temp = input_temp.substr(keyword + keyword_temp.length()); // 去掉input
                    // cout << input_temp << endl;

                    IO(input_temp,OUTPUT);
                    
                    if((keyword = input_temp.find(";")) != string::npos){
                        cout << "OUTPUT|" << OUTPUT.size() << "|:"; // 顯示vector元素數
                        vector_show(OUTPUT);
                    }
                    else{
                        state = Output;
                    }
                }
                else if((keyword = input_temp.find("wire")) != string::npos){ // wire
                    keyword_temp = "wire";
                    input_temp = input_temp.substr(keyword + keyword_temp.length()); // 去掉input
                    // cout << input_temp << endl;

                    IO(input_temp,WIRE);

                    if((keyword = input_temp.find(";")) != string::npos){
                        cout << "WIRE|" << WIRE.size() << "|:"; // 顯示vector元素數
                        vector_show(WIRE);
                    }
                    else{
                        state = Wire;
                    }
                }
                else{ // GATE
                    line_counter = 1; // 關閉line_num記數

                    keyword = input_temp.find(" ");
                    gate_name = input_temp.substr(0,keyword); // 擷取GATE名稱

                    if(gate_name != "buf") transform(gate_name.begin(), gate_name.end(), gate_name.begin(),[](unsigned char c){ return toupper(c); }); // 轉大寫
                    else gate_name = "buffer";

                    // cout << gate_name << endl;

                    if((index = vector_find(GATE_NAME,gate_name)) != -1){
                        GATE_NUM[index] += 1;
                    }
                    else{
                        GATE_NAME.push_back(gate_name);
                        GATE_NUM.push_back(1);
                    }
                }

                break;
            }
        }
    }

    cout << endl;

    // 計算Gate總數並顯示
    cout << "GATE:";
    for (unsigned int i=0;i<GATE_NAME.size();i++){
        cout << GATE_NAME[i] << "|" << GATE_NUM[i] << "| ";
        gate_num += GATE_NUM[i];
    }
    cout << endl;

    // output寫入 ------------------------------------------------------------

    outClientFile << "# " << MN << endl; // 寫入檔名

    // input_total
    if((temp = INPUT.size()) > 1) outClientFile << "# " << temp << " inputs" << endl;
    else outClientFile << "# " << temp << " input" << endl;
    
    // output_total
    if((temp = OUTPUT.size()) > 1) outClientFile << "# " << temp << " outputs" << endl;
    else outClientFile << "# " << temp << " output" << endl;

    // inverter_total
    if((temp = vector_find(GATE_NAME,"NOT")) != -1){
        if(GATE_NUM[temp] > 1) outClientFile << "# " << GATE_NUM[temp] << " inverters" << endl;
        else outClientFile << "# " << GATE_NUM[temp] << " inverter" << endl;

        gate_num -= GATE_NUM[temp];

        GATE_NAME.erase(GATE_NAME.begin() + temp);
        GATE_NUM.erase(GATE_NUM.begin() + temp);
    }
    else{
        outClientFile << "# 0 inverter" << endl;
    }

    // gate_total
    if(gate_num > 1) outClientFile << "# " << gate_num << " gates ( ";
    else outClientFile << "# " << gate_num << " gate ( ";

    for(unsigned int i=0;i<GATE_NAME.size();i++){
        outClientFile << GATE_NUM[i] << " " << GATE_NAME[i];
        if(GATE_NUM[i] > 1) outClientFile << "s";

        if(i<GATE_NAME.size()-1) outClientFile << " + ";
    }

    outClientFile << " )" << endl << endl;

    // input
    for(unsigned int i=0;i<INPUT.size();i++){
        outClientFile << "INPUT(" << INPUT[i] << ")" << endl;
    }
    outClientFile << endl;

    // output
    for(unsigned int i=0;i<OUTPUT.size();i++){
        outClientFile << "OUTPUT(" << OUTPUT[i] << ")" << endl;
    }
    outClientFile << endl;

    // gate

    // 跳到line_num位置
    // cout << line_num << endl;
    for(int i=0;i<line_num-1;i++){
        getline(inClientFile, input_temp);
    }

    while(getline(inClientFile, input_temp)){
        // cout << input_temp << endl;
        if(input_temp.length() > 1){
            if((keyword = input_temp.find("endmodule")) != string::npos){ // endmodule
                break;
            }
            else{ // GATE
                keyword = input_temp.find(" ");
                gate_name = input_temp.substr(0,keyword); // 擷取GATE名稱
                
                if(gate_name != "buf") transform(gate_name.begin(), gate_name.end(), gate_name.begin(),[](unsigned char c){ return toupper(c); }); // 轉大寫
                else gate_name = "BUFF";

                input_temp = input_temp.substr(keyword);
                GATE_PIN_temp = parentheses_disassemble(input_temp);

                outClientFile << GATE_PIN_temp[0] << " = " << gate_name << "(";
                for(unsigned int i=1;i<GATE_PIN_temp.size();i++){
                    outClientFile << GATE_PIN_temp[i];

                    if(i<GATE_PIN_temp.size()-1) outClientFile << ",";
                }
                outClientFile << ")" << endl;
            }
        }
    }

    inClientFile.close();
    outClientFile.close();
}