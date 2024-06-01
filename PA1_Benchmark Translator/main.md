```mermaid
%% ---
%% title: main
%% ---

%% 不能有<>
%% [[]]:副函式
%% {{}}:迴圈
%% [//]:輸入輸出
%% {}:if

flowchart LR
1["vector string  INPUT,OUTPUT,WIRE,GATE_NAME,GATE_PIN_temp

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

4{{"while(getline(inClientFile, input_temp))"}}-->


5{"line_counter"}-->|no|5_1[line_num += 1]-->5_2
5-->|yes|5_2{"此行是否有endmodule"}

5_2-->|yes|6_1["inClientFile.seekg(0)
break"]-->9
5_2-->|no|6_2{"此行是否為空行"}

6_2-->|yes|7_1["pass"]-->4
6_2-->|no|7_2{"state == Module"}-->7_2_1{"此行是否有;"}
-->|no|7_2_2["state = Home"]-->4

6_2-->|no|7_3{"state == Input/Output/Wire"}-->7_3_1[["IO(input_temp,INPUT/OUTPUT/WIRE)"]]-->7_3_2{"此行是否有;"}-->|no|7_3_3[/"顯示INPUT/OUTPUT/WIRE"/]-->7_3_4["state = Home"]-->4

6_2-->|no|7_6["else"]


7_6-->8_1{"此行是否有module"}-->8_1_1["去掉module"]-->8_1_2[["MN = module_name(input_temp)"]]
--> 8_1_3{"此行是否有;"}-->|no|8_1_4["state = Module"]-->4

7_6-->8_2{"此行是否有input/output/wire"}-->8_2_1["去掉input/output/wire"]-->
8_2_2[["IO(input_temp,INPUT/OUTPUT/WIRE)"]]
--> 8_2_3{"此行是否有;"}-->|yes|8_2_4[/"顯示INPUT/OUTPUT/WIRE"/]-->4
8_2_3-->|no|8_2_5["state = Input/Output/Wire"]-->4


7_6-->8_5{"else"}-->8_5_1["line_counter = 1 // 關閉line_num記數"]-->8_5_2["擷取GATE名稱"]
--> 8_5_3["除了buf，將其他名稱轉成大寫，
buf轉為buffer"]-->8_5_4{"GATE名稱是否出現過"}-->|yes|8_5_5["GATE_NUM[index] += 1"]-->4
8_5_4-->|no|8_5_6["GATE_NAME.push_back(gate_name)
GATE_NUM.push_back(1)"]-->4

9[/計算Gate總數並顯示/]-->


11[/"output寫入
寫入# 名稱"/]-->
12[/"input_total
寫入# inputy總數"/]-->
13[/"output_total
寫入# output總數"/]-->
14[/"inverter_total
寫入# inverter總數"/]-->
15[/"gate_total
寫入# gate總數與分別顯示各gate名稱與數量"/]-->

16[/"寫入input、output"/]-->17[/"跳到gate的位置"/]-->


24{{"while(getline(inClientFile, input_temp))"}}-->

25{"此行是否有endmodule"}-->|yes|26_1["break"]-->30
25-->|no|26_2["擷取GATE名稱"]

26_2--> 27["除了buf，將其他名稱轉成大寫，
buf轉為BUFF"]-->28[["GATE_PIN_temp = parentheses_disassemble(input_temp)"]]-->
29["寫入gate與pin腳"]-->24
'''