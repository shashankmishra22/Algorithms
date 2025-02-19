# include <iostream>
# include <fstream>
# include <vector>
# include <algorithm>
# include <unordered_map>
# include <climits>
using namespace std;
struct edge{
    int start;
    int end;
    int weight;
};
struct heap_struct {
    int vertex;
    int key;
};
struct Comp {
    bool operator()(const heap_struct& h1, const heap_struct& h2) {
        return h1.key > h2.key;
    }
};
unordered_map<int, vector<edge>> u_graph;
void store_file(string);
void print_all(void);
long prim(void);
int main(int argc, char** argv) {
    store_file("/Users/shashankmishra/Desktop/edges.txt");
//  print_all();
    long cost = prim();
    cout << "Cost: " << cost << endl;
    return 0;
}
void store_file(string filename) {
    ifstream infile;
    infile.open(filename, ios::in);
    int vertices;
    int edges;
    infile >> vertices >> edges;
    int s, e;
    int w;
    while (edges > 0) {
        infile >> s >> e >> w;
        if (u_graph.find(s) == u_graph.end())
            u_graph.insert(pair<int, vector<edge>>(s, vector<edge>()));
        if (u_graph.find(e) == u_graph.end())
            u_graph.insert(pair<int, vector<edge>>(e, vector<edge>()));
        edge e1 = {s, e, w};
        edge e2 = {e, s, w};
        u_graph[s].push_back(e1);
        u_graph[e].push_back(e2);
        --edges;
    }
    infile.close();
}
void print_all(void) {
    for (auto it = u_graph.begin(); it != u_graph.end(); ++it) {
        cout << it->first << ": ";
        for (int i = 0; i < it->second.size(); ++i)
            cout << "(" << it->second[i].start << ", " << it->second[i].end << ", "
                << it->second[i].weight << ")";
        cout << endl;
    }
}
long prim(void) {
    vector<heap_struct> min_heap(u_graph.size(), heap_struct());
    auto it = u_graph.begin();
    heap_struct h = {it->first, 0};
    min_heap[0] = h;
    ++it;
    int i = 1;
    for (; it != u_graph.end(); ++it, ++i) {
        h = {it->first, INT_MAX};
        min_heap[i] = h;
    }
    make_heap(min_heap.begin(), min_heap.end(), Comp());
    long cost = 0;
    while (!min_heap.empty()) {
        int ver = min_heap[0].vertex;
//      cout << min_heap[0].key << endl;
        cost += min_heap[0].key;
        pop_heap(min_heap.begin(), min_heap.end(), Comp());
        min_heap.pop_back();
        for (int i = 0; i < u_graph[ver].size(); ++i) {
            int target = u_graph[ver][i].end;
            for (auto iter = min_heap.begin(); iter != min_heap.end(); ++iter) {
                if (iter->vertex == target) {
                    if (iter->key > u_graph[ver][i].weight) {
                        iter->key = u_graph[ver][i].weight;
                        make_heap(min_heap.begin(), min_heap.end(), Comp());
                    }
                }
            }
        }
    }
    return cost;
}
