/**
 * Cpp implementing find median in linear time with min/max heaps
 * Yifei Yin, 2020-06-20
 */

#include <cstdlib>
#include <vector>
#include <iostream>
#include <math.h>

using namespace std;

class MinHeap {
private:
    vector<int> data;
    void swap(int a, int b) {
        int tmp = data[a];
        data[a] = data[b];
        data[b] = tmp;
    }

    void percolate(int start) {
        if (start <= 0) return;
        if (start >= data.size()) { cout << "percolate" << endl; return; }
        int parent = (start - 1) / 2;
        if (data[parent] > data[start]) {
            swap(parent, start);
            percolate(parent);
        }
    }

    void heapify(int start) {
        int left = start * 2 + 1;
        int right = left + 1;
        int min = start;
        if (left < data.size() && data[left] < data[start])
            min = left;
        if (right < data.size() && data[right] < data[min])
            min = right;
        if (min != start) {
            swap(start, min);
            heapify(min);
        }
    }

public:
    int getMin() {
        return data.empty() ? -1 : data[0];
    }

    int size() {
        return data.size();
    }

    int popMin() {
        if (data.empty())
            return -1;
        int returnValue = data[0];
        data[0] = data[data.size() - 1];
        data.pop_back();
        heapify(0);
        return returnValue;
    }

    void insert(int x) {
        data.push_back(x);
        percolate(data.size() - 1);
    }
    void inspect() {
        cout << "- ";
        for (auto a : data) {
            cout << a << ", ";
        }
        cout << " -" << endl;
    }
};

class MaxHeap {
private:
    vector<int> data;
    void swap (int a, int b) {
        int tmp = data[a];
        data[a] = data[b];
        data[b] = tmp;
    }
    void percolate(int start) {
        if (start <= 0) return;
        if (start >= data.size()) { cout << "percolate" << endl; return; }
        int parent = (start - 1) / 2;
        if (data[parent] < data[start]) {
            swap(parent, start);
            percolate(parent);
        }
    }

    void heapify(int start) {
        int left = start * 2 + 1;
        int right = left + 1;
        int max = start;
        if (left > data.size() && data[left] > data[start])
            max = left;
        if (right > data.size() && data[right] > data[max])
            max = right;
        if (max != start) {
            swap(start, max);
            heapify(max);
        }
    }

public:
    int getMax() {
        return data.empty() ? -1 : data[0];
    }

    int size() {
        return data.size();
    }

    int popMax() {
        if (data.empty())
            return -1;
        int returnValue = data[0];
        data[0] = data[data.size() - 1];
        data.pop_back();
        heapify(0);
        return returnValue;
    }

    void insert(int x) {
        data.push_back(x);
        percolate(data.size() - 1);
    }
    void inspect() {
        cout << "- ";
        for (auto a : data) {
            cout << a << ", ";
        }
        cout << " -" << endl;
    }
};


//-----------------------------------------//
// stub for the online median class        //
//-----------------------------------------//
class OnlineMedian {
private:
    MaxHeap maxHeap;
    MinHeap minHeap;
public:
    OnlineMedian(){

    }

    void insert(int x){
        if (x >= maxHeap.getMax()) {
            minHeap.insert(x);
            if (minHeap.size() - maxHeap.size() > 1) {
                maxHeap.insert(minHeap.popMin());
            }
        } else {
            maxHeap.insert(x);
            if (maxHeap.size() - minHeap.size() > 0) {
                minHeap.insert(maxHeap.popMax());
            }
        }
    }

    int getMedian(){
        return minHeap.getMin();
    }
};


//-----------------------------------------//
// reads integers, prints the median       //
//-----------------------------------------//
int main(){
    string line;
    OnlineMedian med = OnlineMedian();

    // ---------------------------
    // Testing min heap & max heap
    // ---------------------------
    // MinHeap minHeap = MinHeap();
    // minHeap.insert(99);
    // minHeap.insert(1);
    // minHeap.insert(20);
    // minHeap.insert(3);
    // minHeap.insert(23);
    // minHeap.insert(50);

    // cout << minHeap.popMin() << endl;
    // cout << minHeap.popMin() << endl;
    // cout << minHeap.popMin() << endl;
    // cout << minHeap.popMin() << endl;

    // MaxHeap maxHeap = MaxHeap();
    // maxHeap.insert(99);
    // maxHeap.insert(1);
    // maxHeap.insert(20);
    // maxHeap.insert(3);
    // maxHeap.insert(23);
    // maxHeap.insert(50);

    // cout << maxHeap.popMax() << endl;
    // cout << maxHeap.popMax() << endl;
    // cout << maxHeap.popMax() << endl;
    // cout << maxHeap.popMax() << endl;

    while(true){
        if(!getline(cin, line))
            break;
        int a = atoi(line.c_str());
        med.insert(a);
        cout << "reading: " << a << endl;
        cout << "median so far: " << med.getMedian() << endl;
    };
}
