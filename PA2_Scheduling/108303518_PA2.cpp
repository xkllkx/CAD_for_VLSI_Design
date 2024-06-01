#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <ctime>
// #include <algorithm>

using namespace std; //可以不用打std

template<class T>
int vector_find(vector<T> find_vector,T temp){
    for(unsigned int i=0;i<find_vector.size();i++){
        if(find_vector[i] == temp){
            return i;
        }
    }
    return -1;
}

template<class T>
void vector_show(vector<T> show_vector){
    for (unsigned int i=0;i<show_vector.size();i++){
        cout << show_vector[i] << " ";
    }
    cout << endl;
}

// -------------------------------------------------------------------------------------------------

// 宣告結構
struct node{
    int order;
    char mode; // 模式
    vector<int> input,output;
};

struct pipeline{
    int add_num,mul_num;
    vector<int> node;
};

// -------------------------------------------------------------------------------------------------

void node_show(vector<struct node> &NODE){
    for(unsigned int i=0;i<NODE.size();i++){
        cout << "node: " << NODE[i].order << endl;
        cout << "mode: " << NODE[i].mode << endl;

        cout << "input: ";
        vector_show(NODE[i].input);

        cout << "output: ";
        vector_show(NODE[i].output);

        if(i < NODE.size()-1) cout << "-------------" << endl;
    }
}

int node_index_find(vector<struct node> &NODE,int order){
    for(unsigned int i=0;i<NODE.size();i++){
        if(NODE[i].order == order) return i;
    }
    return -1;
}

void node_split(vector<struct node> &NODE,string input_temp,vector<int> &ready){ // 2 i 5 4 6
    size_t blank = 0;
    int IO = 0,order = 0,node_index = 0,node_index1 = 0;

    order = stoi(input_temp.substr(0,input_temp.find(" "))); // node order
    // cout << "node: " << order << endl;
    input_temp = input_temp.substr(input_temp.find(" ")+1);

    if((node_index = node_index_find(NODE,order)) == -1){ // node不存在，創建node
        struct node node_temp;

        node_temp.order = order;

        node_temp.mode = input_temp.substr(0,input_temp.find(" "))[0]; // node mode // [0]:轉char
        // cout << "mode: " << node_temp.mode << endl;
        input_temp = input_temp.substr(input_temp.find(" ")+1);

         // 將input往前提
        if(node_temp.mode == 'i') ready.push_back(order);

        while((blank = input_temp.find(" ")) != string::npos){
            IO = stoi(input_temp.substr(0,blank));
            node_temp.output.push_back(IO); // output
            input_temp = input_temp.substr(blank+1);

            if((node_index1 = node_index_find(NODE,IO)) == -1){ // node不存在，創建node
                struct node node_temp1;

                node_temp1.order = IO;
                node_temp1.input.push_back(order); // input

                NODE.push_back(node_temp1);
            }
            else{
                NODE[node_index1].input.push_back(order); // input
            }
        }

        NODE.push_back(node_temp);

        // cout << "output: ";
        // vector_show(node_temp.output);
    }
    else{ // node存在，更新node
        NODE[node_index].order = order;

        NODE[node_index].mode = input_temp.substr(0,input_temp.find(" "))[0]; // node mode
        // cout << "mode: " << NODE[node_index].mode << endl;
        input_temp = input_temp.substr(input_temp.find(" ")+1);

         // 將input往前提
        if(NODE[node_index].mode == 'i') ready.push_back(order);

        while((blank = input_temp.find(" ")) != string::npos){
            IO = stoi(input_temp.substr(0,blank));
            NODE[node_index].output.push_back(IO); // output
            input_temp = input_temp.substr(blank+1);

            if((node_index1 = node_index_find(NODE,IO)) == -1){
                struct node node_temp1; // node不存在，創建node

                node_temp1.order = IO;
                node_temp1.input.push_back(order); // input

                NODE.push_back(node_temp1);
            }
            else{
                NODE[node_index1].input.push_back(order); // input
            }
        }

        // cout << "output: ";
        // vector_show(NODE[node_index].output);
    }

    // cout << "-------------" << endl;
}

int pipeline_order_find(vector<struct pipeline> &PIPELINE,int order){ // 回傳order在pipline的哪一層
    for(int i=PIPELINE.size()-1;i>-1;i--){
        for(int j=0;j<PIPELINE[i].node.size();j++){
            if(PIPELINE[i].node[j] == order) return i;
        }
    }
    return -1;
}

void pipeline_show(vector<struct pipeline> &PIPELINE){
    for(unsigned int i=0;i<PIPELINE.size();i++){
        cout << i << " " << PIPELINE[i].add_num << " " << PIPELINE[i].mul_num << endl;
        vector_show(PIPELINE[i].node);
        cout << "-----" << endl;
    }

    cout << "-------------" << endl;
}

bool ready_check(vector<int> &ready,vector<int> input){ // input有沒有在ready裡
    bool flag = 0;

    for(unsigned int i=0;i<input.size();i++){
        flag = 0;

        for(unsigned int j=0;j<ready.size();j++){
            if(input[i] == ready[j]){
                flag = 1;
                break;
            }
        }
        
        if(flag == 0) return 0;
    }

    return 1;
}

void waiting_arrangement(vector<struct node> &NODE,vector<struct pipeline> &PIPELINE,vector<int> &ready,vector<int> &waiting){
    int node_index = 0,order = 0;
    int pipeline_layer = 0,flag = 0,pipeline_layer_temp = 0;

    char mode;

    cout << "waiting_finish: ";

    // 檢查warning
    for(unsigned int i=0;i<waiting.size();i++){ 
        node_index = node_index_find(NODE,waiting[i]);
        order = NODE[node_index].order;
        mode = NODE[node_index].mode;
        
        if(ready_check(ready,NODE[node_index].input)){
            pipeline_layer = 0;
            flag = 0;
            
            for(unsigned int j=0;j<NODE[node_index].input.size();j++){
                pipeline_layer_temp = pipeline_order_find(PIPELINE,NODE[node_index].input[j]);
                if(pipeline_layer_temp != -1 && flag == 0) flag = 1;
                // cout << pipeline_layer_temp << endl;
                if(pipeline_layer < pipeline_layer_temp) pipeline_layer = pipeline_layer_temp;
            }

            if(flag) pipeline_layer++;
            // cout << flag << endl;
            // cout << pipeline_layer << endl;
            
            if(mode == '+'){
                PIPELINE[pipeline_layer].node.push_back(order);
                PIPELINE[pipeline_layer].add_num++;

                ready.push_back(order); // 添加ready
                cout << order << " ";

                waiting.erase(waiting.begin() + i); // 刪除waiting
            }
            else{
                for(unsigned int j=0;j<3;j++){
                    PIPELINE[pipeline_layer+j].node.push_back(order);
                    PIPELINE[pipeline_layer+j].mul_num++;
                }
                ready.push_back(order); // 添加ready
                cout << order << " ";

                waiting.erase(waiting.begin() + i); // 刪除waiting
            }
        }
    }

    cout << endl;
}

void pipeline_arrangement(string input_temp,vector<struct node> &NODE,vector<struct pipeline> &PIPELINE,vector<int> &ready,vector<int> &waiting){
    int node_index = 0,order = 0,waiting_index = 0;
    int pipeline_layer = 0,flag = 0,pipeline_layer_temp = 0;

    char mode;

    size_t blank = 0;

    order = stoi(input_temp.substr(0,input_temp.find(" "))); // node order
    cout << "node: " << order << endl;
    input_temp = input_temp.substr(input_temp.find(" ")+1);

    mode = input_temp.substr(0,input_temp.find(" "))[0]; // node mode
    // cout << "mode: " << mode << endl;
    input_temp = input_temp.substr(input_temp.find(" ")+1);

    node_index = node_index_find(NODE,order);
    cout << "input: ";
    vector_show(NODE[node_index].input);

    // 檢查warning
    waiting_arrangement(NODE,PIPELINE,ready,waiting);

    if(mode != 'i'){
        if(mode != 'o'){
            node_index = node_index_find(NODE,order);
            
            if(ready_check(ready,NODE[node_index].input)){
                pipeline_layer = 0;
                flag = 0;
                
                for(unsigned int i=0;i<NODE[node_index].input.size();i++){
                    pipeline_layer_temp = pipeline_order_find(PIPELINE,NODE[node_index].input[i]);
                    if(pipeline_layer_temp != -1 && flag == 0) flag = 1;
                    // cout << pipeline_layer_temp << endl;
                    if(pipeline_layer < pipeline_layer_temp) pipeline_layer = pipeline_layer_temp;
                }

                if(flag) pipeline_layer++;
                // cout << flag << endl;
                // cout << pipeline_layer << endl;
                
                if(mode == '+'){
                    PIPELINE[pipeline_layer].node.push_back(order);                
                    PIPELINE[pipeline_layer].add_num++;

                    ready.push_back(order); // 添加ready
                }
                else{
                    for(unsigned int i=0;i<3;i++){
                        PIPELINE[pipeline_layer+i].node.push_back(order);                    
                        PIPELINE[pipeline_layer+i].mul_num++;
                    }
                    ready.push_back(order); // 添加ready
                }
            }
            else{
                waiting.push_back(order);
            }
        }
    }
    else{
        if(vector_find(ready,order) == -1) ready.push_back(order); // 添加ready
    }

    cout << "ready: ";
    vector_show(ready);

    cout << "waiting: ";
    vector_show(waiting);

    cout << "-------------" << endl;
}

// -------------------------------------------------------------------------------------------------

// ./checker testcase1 testcase1.out
// ./checker testcase1 testcase1_SampleOutput.out

// make all
// make run Testcase=testcase1
// make clean

// -------------------------------------------------------------------------------------------------

int main(int argc,char *argv[]){
    for(int i=0;i<argc;i++){
        cout << argv[i] << endl;
    }

    double START = clock(),END = 0.;

    vector<struct node> NODE; // 儲存node資訊

    string input_temp; // 逐行讀檔暫存
    int Latency = 0; // 儲存Latency constrain

    vector<struct pipeline> PIPELINE; // 儲存CLK週期(數量由Latency constrain)
    vector<int> ready,waiting; // ready：放置已執行運算的node、waiting：待執行運算的node

    // 檔名宣告 ------------------------------------------------------------
    ifstream input_file(argv[1], ios::in);
    if (!input_file){

		cerr << "input file could not be opened" << endl;
		exit(EXIT_FAILURE);
	}

    ofstream output_file(argv[2], ios::out);
	if (!output_file){
		cerr << "output file could not be opened" << endl;
		exit(EXIT_FAILURE);
	}

    // input讀檔 ------------------------------------------------------------

    getline(input_file, input_temp); // # Testcase 1
    cout << input_temp << endl;

    getline(input_file, input_temp); // Latency constrain: 5
    Latency = stoi(input_temp.substr(input_temp.rfind(" ")+1));
    cout << "Latency constrain: " << Latency << endl;

    getline(input_file, input_temp); // 空行
    getline(input_file, input_temp); // # Test data

    // cout << "------------- NODE -------------" << endl;

    while (getline(input_file, input_temp)){ // 逐行讀取node
        node_split(NODE,input_temp,ready); // 以後面的node作為主要參考

        // if(input_file.eof()) input_file.seekg(0);
    }

    cout << "----------- NODE SHOW -----------" << endl;

    node_show(NODE);

    // 重新讀檔 ------------------------------------------------------------
    input_file.close();
    input_file.open(argv[1], ios::in);
    // input_file.seekg(0); // 回到讀取文檔開頭 // 文章到底無法跳轉

    
    for(unsigned int i=0;i<4;i++){ // 跳到node位置
        getline(input_file, input_temp);
    }

    // 排序 ---------------------------------------------------------------

    cout << "----------- PIPELINE -----------" << endl;

    for(unsigned int i=0;i<Latency;i++){ // pipeline格子限制
        struct pipeline pipeline_temp;
        pipeline_temp.add_num = 0;
        pipeline_temp.mul_num = 0;
        PIPELINE.push_back(pipeline_temp);
    }

    while(getline(input_file, input_temp)){ // 逐行讀取node
        // cout << input_temp << endl;
        pipeline_arrangement(input_temp,NODE,PIPELINE,ready,waiting);
        // pipeline_show(PIPELINE);
    }

    // 將waiting跑完
    while(waiting.size() > 0){
        waiting_arrangement(NODE,PIPELINE,ready,waiting);
    }

    cout << "----------- OUTPUT -----------" << endl;

    // 計算add_max、mul_max
    int add_max = 0,mul_max = 0;

    for(unsigned int i=0;i<PIPELINE.size();i++){
        if(PIPELINE[i].add_num > add_max) add_max = PIPELINE[i].add_num;
        if(PIPELINE[i].mul_num > mul_max) mul_max = PIPELINE[i].mul_num;
    }

    cout << "add_max: " << add_max << endl;
    cout << "mul_max: " << mul_max << endl;

    cout << "-----" << endl;
    pipeline_show(PIPELINE);

    // output寫入 ------------------------------------------------------------

    output_file << add_max << endl; // add_max
    output_file << mul_max << endl; // mul_max

    for(unsigned int i=0;i<PIPELINE.size();i++){
        for(unsigned int j=0;j<PIPELINE[i].node.size();j++){
            output_file << PIPELINE[i].node[j];
            if(j < PIPELINE[i].node.size()-1) output_file << " ";
        }
        if(i < PIPELINE.size()-1) output_file << endl;
    }

    input_file.close();
    output_file.close();

    END = clock();
    cout << "process_time: " << (END - START) / CLOCKS_PER_SEC << " s" << endl;
}