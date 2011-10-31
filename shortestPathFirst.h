//
//  shortestPathFirst.h
//  graphConstruction
//
//  Created by Vince Mansel on 10/31/11.
//  Copyright (c) 2011 Wave Ocean Software. All rights reserved.
//

#ifndef graphConstruction_shortestPathFirst_h
#define graphConstruction_shortestPathFirst_h

#include <iostream>
#include "genlib.h"
#include "simpio.h"
#include "set.h"
#include "map.h"
#include "stack.h"
#include "vector.h"
#include "strutils.h"
#include "pqueueT.h"

//Forward declaration for the struct nodeT
struct arcT;

struct nodeT {
    string name;
    Set<arcT *> connected;
};
struct arcT {
    nodeT * start;
    nodeT * end;
};
struct graphT {
    Set<nodeT *> allNodes;
};

Stack<nodeT *> ShortestPathFirst(nodeT *node1, nodeT *node2);


#endif
