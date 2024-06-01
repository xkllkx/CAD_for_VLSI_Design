```mermaid
%% ---
%% title: main
%% ---
flowchart LR
%% 不能有<>
%% [[]]:副函式
%% {{}}:迴圈
%% [//]:輸入輸出
%% {}:if

24{{"while(getline(inClientFile, input_temp))"}}-->

25{"此行是否有endmodule"}-->|yes|26_1["break"]-->30
25-->|no|26_2["擷取GATE名稱"]

26_2--> 27["除了buf，將其他名稱轉成大寫，
buf轉為BUFF"]-->28[["GATE_PIN_temp = parentheses_disassemble(input_temp)"]]-->
29["寫入gate與pin腳"]-->24
'''