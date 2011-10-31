//
//  shortestPathFirst.cpp
//  graphConstruction
//
//  Created by Vince Mansel on 10/31/11.
//  Copyright (c) 2011 Wave Ocean Software. All rights reserved.
//

#include <iostream>

#include "shortestPathFirst.h"

typedef Stack<nodeT *>  PathStackT;
typedef PQueueT<PathStackT> PathKeeperT;

bool IsSame(nodeT * goal, nodeT * current);

int CompareShortestPath(PathStackT path1, PathStackT path2) {
    double one = path1.size();
    double two = path2.size();  
    if (one == two) return 0;
	if (one > two) return -1;
	return 1; // ShortestPath
}

Stack<nodeT *> ShortestPathFirst(nodeT *node1, nodeT *node2) {
    
    //cout << "SPF: IN" << endl;
    
    PQueueT<PathStackT> qStore(CompareShortestPath);
    PathStackT paths;
    Set<nodeT *> visited;
    
    nodeT * current = node1;
    nodeT * goal = node2;
    
    paths.push(current);
    qStore.enqueue(paths);
    
    PathStackT currentPath;
    
    while (true) {
        if (qStore.isEmpty()) {
            cout << "Store is Empty" << endl;
            cout << "Previous current path:" << endl;
            
            break;
        }
        PathStackT path = qStore.dequeue();
        currentPath = path;
        current = path.pop();
        
        if (IsSame(goal, current)) {
            cout << "Reached Goal" << endl;
            break;
        }
        
        if (!visited.contains(current)) {
            visited.add(current);
            
            Set<arcT *>::Iterator itr = current->connected.iterator();
            
            while (itr.hasNext()) {
                nodeT * neighbor = itr.next()->end;
                PathStackT newPath = currentPath;
                newPath.push(neighbor);
                qStore.enqueue(newPath);
            }
        }
    }    
    //cout << "SPF: OUT" << endl;
    return currentPath;
}

bool IsSame(nodeT * goal, nodeT * current) {
    bool result = false;
    
    if (goal->name == current->name) {
        result = true;
    }
    return result;
}
