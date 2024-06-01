```mermaid
%% ---
%% title: main
%% ---

%% 不能有<>
%% [[]]:副函式
%% {{}}:迴圈
%% [//]:輸入輸出
%% {}:if

flowchart LR;
1["vector<struct node> NODE; // 儲存node資訊

    string input_temp; // 逐行讀檔暫存
    int Latency = 0; // 儲存Latency constrain

    vector<struct pipeline> PIPELINE; // 儲存CLK週期(數量由Latency constrain)
    vector<int> ready,waiting; // ready：放置已執行運算的node、waiting：待執行運算的node
"]-->

2["檔名宣告
ifstream inClientFile 輸入檔案
ofstream outClientFile 輸出檔案
"]-->

3["儲存Latency constrain"]-->

4["第一次讀檔 // 逐行讀取node"]-->

5{{"是否讀完檔案"}}-->

|no|5_1["node_split(NODE,input_temp,ready) // 分割與紀錄node的各項資訊"]-->5
5-->|yes|6["node_show(NODE) // 顯示所有node"]-->7

7["重新讀檔並跳到node位置"]-->

8["根據Latency constrain創立CLK週期數(PIPELINE)
並將各層Adder、Multiplier的數量歸零
"]-->

9{{"是否讀完檔案"}}-->

|no|9_1["waiting_arrangement(NODE,PIPELINE,ready,waiting) // 將未計算的node進行放置"]-->9_2["pipeline_arrangement(input_temp,NODE,PIPELINE,ready,waiting) // 安排node在CLK週期位置"]-->9
9-->|yes|10["waiting_arrangement(NODE,PIPELINE,ready,waiting) // 將未計算的node進行放置"]-->11

11["輪巡各CLK週期並紀錄Adder、Multiplier最大數量"]-->

12["輸出Adder、Multiplier最大數量"]-->

13["輸出各層CLK週期"]-->

14["關閉讀入檔案、輸出檔案"]
