```mermaid
%% ---
%% title: main
%% ---
flowchart TD
%% 不能有<>
%% [[]]:副函式
%% {{}}:迴圈
%% [//]:輸入輸出
%% {}:if

1["vector string  PIN,INPUT,OUTPUT,WIRE,GATE_NAME,GATE_PIN_temp,IO_temp
vector<string> GATE_PIN[8]; // and,nand,or,nor,xor,xnor,buf,not

vector<int> GATE_NUM

string input_temp,MN,gate_name,keyword_temp

size_t keyword = 0

int index = 0,temp = 0,gate_num = 0,line_num = 0,line_counter = 0,state = 0
"]---

2["enum state_name{Home,Module,Input,Output,Wire}"]-->

3["檔名宣告
ifstream inClientFile 輸入檔案
ofstream outClientFile 輸出檔案
"]-->

4{{"while(getline(inClientFile, input_temp))"}}
'''