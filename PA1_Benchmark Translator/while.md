```mermaid
%% ---
%% title: main
%% ---

%% {
%%   "theme": "light",
%%   "themeVariables":{"fontSize":"50px"}
%% }

flowchart TD
%% 不能有<>
%% [[]]:副函式
%% {{}}:迴圈
%% [//]:輸入輸出
%% {}:if

4{{"while(getline(inClientFile, input_temp))"}}-->

5{"line_counter"}-->|no|5_1[line_num += 1]-->5_2
5-->|yes|5_2{"此行是否有endmodule"}

5_2-->|yes|6_1["inClientFile.seekg(0)
break"]-->9
5_2-->|no|6_2{"此行是否為空行"}

6_2-->|yes|7_1["pass"]-->4
6_2-->|no|7_2{"state == Module"}-->7_2_1{"此行是否有;"}
-->|no|7_2_2["state = Home"]-->4

6_2-->|no|7_3{"state == Input"}-->7_3_1[["IO(input_temp,INPUT)"]]-->7_3_2{"此行是否有;"}-->|no|7_3_3[/"顯示INPUT"/]-->7_3_4["state = Home"]-->4

6_2-->|no|7_4{"state == Output"}-->7_4_1[["IO(input_temp,OUTPUT)"]]-->7_4_2{"此行是否有;"}-->|no|7_4_3[/"顯示OUTPUT"/]-->7_4_4["state = Home"]-->4

6_2-->|no|7_5{"state == Wire"}-->7_5_1[["IO(input_temp,WIRE)"]]-->7_5_2{"此行是否有;"}-->|no|7_5_3[/"顯示WIRE"/]-->7_5_4["state = Home"]-->4

6_2-->|no|7_6["else"]


7_6-->8_1{"此行是否有module"}-->8_1_1["去掉module"]-->8_1_2[["MN = module_name(input_temp)"]]
--> 8_1_3{"此行是否有;"}-->|no|8_1_4["state = Module"]-->4

7_6-->8_2{"此行是否有input"}-->8_2_1["去掉input"]-->8_2_2[["IO(input_temp,INPUT)"]]
--> 8_2_3{"此行是否有;"}-->|yes|8_2_4[/"顯示INPUT"/]-->4
8_2_3-->|no|8_2_5["state = Input"]-->4

7_6-->8_3{"此行是否有output"}-->8_3_1["去掉output"]-->8_3_2[["IO(input_temp,OUTPUT)"]]
--> 8_3_3{"此行是否有;"}-->|yes|8_3_4[/"顯示OUTPUT"/]-->4
8_3_3-->|no|8_3_5["state = Output"]-->4

7_6-->8_4{"此行是否有wire"}-->8_4_1["去掉wire"]-->8_4_2[["IO(input_temp,WIRE)"]]
--> 8_4_3{"此行是否有;"}-->|yes|8_4_4[/"顯示WIRE"/]-->4
8_4_3-->|no|8_4_5["state = Wire"]-->4

7_6-->8_5{"else"}-->8_5_1["line_counter = 1 // 關閉line_num記數"]-->8_5_2["擷取GATE名稱"]
--> 8_5_3["除了buf，將其他名稱轉成大寫，
buf轉為buffer"]-->8_5_4{"GATE名稱是否出現過"}-->|yes|8_5_5["GATE_NUM[index] += 1"]-->4
8_5_4-->|no|8_5_6["GATE_NAME.push_back(gate_name)
GATE_NUM.push_back(1)"]-->4

9[/計算Gate總數並顯示/]-->10("    ")
'''