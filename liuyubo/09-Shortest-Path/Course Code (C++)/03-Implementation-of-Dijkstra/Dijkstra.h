//
// Created by liuyubobobo on 9/28/16.
//

#ifndef INC_03_IMPLEMENTATION_OF_DIJKSTRA_DIJKSTRA_H
#define INC_03_IMPLEMENTATION_OF_DIJKSTRA_DIJKSTRA_H

#include <iostream>
#include <vector>
#include <stack>
#include "Edge.h"
#include "IndexMinHeap.h"

using namespace std;

// Dijkstra算法求最短路径
template<typename Graph, typename Weight>
class Dijkstra{

private:
    Graph &G;                   // 图的引用
    int s;                      // 起始点
    // distTo[i]存储从起始点s到i的最短路径长度/权值
    Weight *distTo;
    // 标记数组, 在算法运行过程中标记节点i是否被访问             
    bool *marked; 
    // 不仅要找到最短路径的权值，还要找到具体是哪一条路径
    // from[i]记录最短路径中, 到达i点的边是哪一条
    // (也就是从哪一个顶点到达i)
    // 可以用来恢复整个最短路径              
    vector<Edge<Weight>* > from; 
                                

public:
    // 构造函数, 使用Dijkstra算法求最短路径
    Dijkstra(Graph &graph, int s):G(graph){

        // 算法初始化
        assert( s >= 0 && s < G.V() );
        this->s = s;
        distTo = new Weight[G.V()];
        marked = new bool[G.V()];
        for( int i = 0 ; i < G.V() ; i ++ ){
            //由于不知道具体的数据类型，所以此处使用的是
            //模板类型Weight的默认构造函数
            distTo[i] = Weight();
            marked[i] = false;
            from.push_back(NULL);
        }

        // 使用索引堆记录当前找到的到达每个顶点的最短距离
        IndexMinHeap<Weight> ipq(G.V());

        // 对于起始点s进行初始化
        // 如果是int double就会被初始化为0
        distTo[s] = Weight();
        from[s] = new Edge<Weight>(s, s, 0);
        //将s加入最小索引堆中
        ipq.insert(s, distTo[s] );
        marked[s] = true;
        while( !ipq.isEmpty() ){
            //找到最小索引堆中存在的元素中
            //离原点最近的节点
            int v = ipq.extractMinIndex();

            // distTo[v]就是s到v的最短距离
            marked[v] = true;

            // 对v的所有相邻节点进行更新
            // 松弛操作
            typename Graph::adjIterator adj(G, v);
            for( Edge<Weight>* e = adj.begin() ; !adj.end() ; e = adj.next() ){
                int w = e->other(v);
                // 如果从s点到w点的最短路径还没有找到
                if( !marked[w] ){
                    // 如果w点以前没有访问过,
                    // 或者访问过, 但是通过当前的v点到w点距离更短, 则进行更新
                    if( from[w] == NULL || distTo[v] + e->wt() < distTo[w] ){
                        distTo[w] = distTo[v] + e->wt();
                        //w这个点是通过e这个边达到的
                        from[w] = e;
                        if( ipq.contain(w) )
                            ipq.change(w, distTo[w] );
                        else
                            ipq.insert(w, distTo[w] );
                    }
                }
            }
        }
    }

    // 析构函数
    ~Dijkstra(){
        delete[] distTo;
        delete[] marked;
        delete from[0];
    }

    // 返回从s点到w点的最短路径长度
    Weight shortestPathTo( int w ){
        assert( w >= 0 && w < G.V() );
        assert( hasPathTo(w) );
        return distTo[w];
    }

    // 判断从s点到w点是否联通
    bool hasPathTo( int w ){
        assert( w >= 0 && w < G.V() );
        return marked[w];
    }

    // 寻找从s到w的最短路径, 将整个路径经过的边存放在vec中
    void shortestPath( int w, vector< Edge<Weight> > &vec ){

        assert( w >= 0 && w < G.V() );
        assert( hasPathTo(w) );

        // 通过from数组逆向查找到从s到w的路径, 存放到栈中
        stack<Edge<Weight>*> s;
        Edge<Weight> *e = from[w];
        //e->v()返回的是第一个顶点
        while( e->v() != this->s ){
            //将from中存储的边以倒叙的形式存放在栈中
            s.push(e);
            e = from[e->v()];
        }
        s.push(e);

        // 从栈中依次取出元素, 获得顺序的从s到w的路径
        while( !s.empty() ){
            e = s.top();
            vec.push_back( *e );
            s.pop();
        }
    }

    // 打印出从s点到w点的路径
    void showPath(int w){

        assert( w >= 0 && w < G.V() );
        assert( hasPathTo(w) );

        vector<Edge<Weight> > vec;
        shortestPath(w, vec);
        for( int i = 0 ; i < vec.size() ; i ++ ){
            cout<<vec[i].v()<<" -> ";
            if( i == vec.size()-1 )
                cout<<vec[i].w()<<endl;
        }
    }
};

#endif //INC_03_IMPLEMENTATION_OF_DIJKSTRA_DIJKSTRA_H
