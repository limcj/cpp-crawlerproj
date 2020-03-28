#pragma once

using namespace std;


//parent graph class that will render summary of faults and maintenance graph
class graph {
protected:
    int fault = 0;
    int maintenance = 0;
public:
    graph();
    void renderGraph();
};


//child graph class that inherits from parent class graph
//this graph is used to show qty of diff types of faults
//inherits the faults and maintenance variables from the parent graph and adds
//its own variable ints of fault categories
class graphTFT : public graph {
private:
    int track = 0;
    int power = 0;
    int door = 0;
    int signal = 0;
    int train = 0;
public:
    graphTFT();

    //defines its own method of renderGraph() diff from parent class
    void renderGraph();
};


//child graph class that inherits from parent class graph
//this graph is used to show number of faults by line
//inherits the faults and maintenance variables from the parent graph and adds
//its own variable ints of fault categories
class graphFBL : public graph {
private:
    int nsl = 0;
    int nel = 0;
    int ewl = 0;
    int ccl = 0;
public:
    graphFBL();

    //defines its own method of renderGraph() diff from parent class
    void renderGraph();
};


