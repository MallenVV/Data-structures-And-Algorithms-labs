// Wilehlm Malé (wilma870)
// Oscar Jansson (Oscja211)

#include "algorithm"
#include "costs.h"
#include "queue"
#include "trailblazer.h"
#include "pqueue.h"
#include "adapter.h"
#include "cmath"

using namespace std;


vector<Node*> depthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end) {

    for (Node* n : graph.getVertexSet()){
        n->visited = false;
    }
    for (Arc* a : graph.getArcSet()){
        a->visited = false;
    }

    Stack<Node*> stack;
    Stack<Node*> noPath;
    Node* node = start;
    stack.push(node);


    while (node != end && !stack.isEmpty()){
        node = stack.pop();
        noPath.push(node);
        node->setColor(GREEN);
        node->visited = true;

        bool noAvailableNodes = true;
        for(Arc* arc : node->arcs){
            Node* n = arc->finish;
            if (!n->visited){

                noAvailableNodes = false;
                stack.push(n);
                n->setColor(YELLOW);
                n->previous = node;

            }
        }
        if (noAvailableNodes && node != end){
            Node* temp;
            while (noPath.top() != stack.top()->previous){
                temp = noPath.pop();
                temp->setColor(GRAY);
            }
        }
    }
    vector<Vertex*> path;

    if (stack.isEmpty()){
        return path;
    }

    node = end;
    do {
        path.push_back(node);
        node = node->previous;
    }
    while(node->previous != nullptr);
    path.push_back(node);

    reverse(path.begin(), path.end());
    graph.resetData();
    return path;
}


vector<Node *> breadthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end) {
    for (Node* n : graph.getVertexSet()){
        n->visited = false;
    }
    for (Arc* a : graph.getArcSet()){
        a->visited = false;
    }

    queue<Node*> que;
    Node* node = start;
    que.push(node);

    while (node != end && !que.empty()){
        node = que.front();
        que.pop();
        node->setColor(GREEN);
        node->visited = true;

        for(Arc* arc : node->arcs){
            Node* n = arc->finish;

            if (!n->visited){

                que.push(n);
                n->setColor(YELLOW);
                n->previous = node;
            }
        }
    }
    vector<Vertex*> path;

    if (que.empty()){
        return path;
    }

    node = end;
    do {
        path.push_back(node);
        node = node->previous;
    }
    while(node->previous != nullptr);
    path.push_back(node);

    reverse(path.begin(), path.end());
    graph.resetData();
    return path;
}

vector<Node *> dijkstrasAlgorithm(BasicGraph& graph, Vertex* start, Vertex* end) {

    double inf = numeric_limits<double>::infinity();
    for (Node* n : graph.getVertexSet()){
        n->visited = false;
        n->cost = inf;
    }
    for (Arc* a : graph.getArcSet()){
        a->visited = false;
    }

    PriorityQueue<Node*> pq;
    start->cost = 0;
    Node* node = start;
    pq.enqueue(node, 0);

    while (node != end && !pq.isEmpty()){
        node = pq.dequeue();
        node->setColor(GREEN);
        node->visited = true;

        for(Arc* arc : node->arcs){
            Node* n = arc->finish;

            if (!n->visited){

                if (n->cost > node->cost + arc->cost){
                    double oldCost = n->cost;
                    n->cost = node->cost + arc->cost;
                    if (oldCost == inf){
                        pq.enqueue(n, n->cost);
                        n->setColor(YELLOW);
                    }
                    else {
                        pq.changePriority(n,n->cost);
                    }
                    n->previous = node;
                }
            }
        }
    }

    vector<Vertex*> path;

    do {
        path.push_back(end);
        end = end->previous;
    }
    while(end->previous != nullptr);
    path.push_back(end);

    reverse(path.begin(), path.end());

    graph.resetData();
    return path;
}

vector<Node *> aStar(BasicGraph& graph, Vertex* start, Vertex* end) {

    double inf = numeric_limits<double>::infinity();
    for (Node* n : graph.getVertexSet()){
        n->visited = false;
        n->cost = inf;
    }
    for (Arc* a : graph.getArcSet()){
        a->visited = false;
    }

    PriorityQueue<Node*> pq;
    start->cost = 0;
    Node* node = start;
    pq.enqueue(node, 0);

    while (node != end && !pq.isEmpty()){
        node = pq.dequeue();
        node->setColor(GREEN);
        node->visited = true;

        for(Arc* arc : node->arcs){

            Node* n = arc->finish;
            if (!n->visited){

                if (n->cost > node->cost + arc->cost){
                    double newCost = node->cost + arc->cost;

                    if (n->cost == inf){
                        pq.enqueue(n, newCost + n->heuristic(end));
                        n->setColor(YELLOW);
                    }
                    else {
                        pq.changePriority(n,newCost + n->heuristic(end));
                    }
                    n->cost = newCost;
                    n->previous = node;
                }
            }
        }
    }

    vector<Vertex*> path;

    do {
        path.push_back(end);
        end = end->previous;
    }
    while(end->previous != nullptr);
    path.push_back(end);

    reverse(path.begin(), path.end());

    graph.resetData();
    return path;
}
