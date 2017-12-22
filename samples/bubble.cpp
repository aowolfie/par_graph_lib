#include <iostream>
#include <sstream>
#include <list>
#include <map>

namespace depgraph {

  struct variableaccess {
    std::string var;
    enum access{
      READ,
      WRITE
    } ac;
  };
  
  std::list<std::string> tasklist;

  std::map<std::string, std::list<variableaccess> > accessmap;

  
  
  void newtask(const std::string& name) {
    tasklist.push_back(name);
  }
  
  void readwrite(const std::string& name) {
    //assume tasklist is not empty

    variableaccess va1 = {name, variableaccess::access::READ};
    accessmap[*(--(tasklist.end()))].push_back(va1);
    variableaccess va2 = {name, variableaccess::access::WRITE}; 
    accessmap[*(--(tasklist.end()))].push_back(va2);
  }

  void listall() {
    for (auto& ta : tasklist) {
      std::cout<<"task "<<ta<<std::endl;

      for (auto& p : accessmap[ta]) {
	std::cout<<"  use var "<<p.var<<" "<<(p.ac==variableaccess::access::READ?"R":"W")<<std::endl;
      }
    }
  }
}

void bubblesort(int* A, int n) {
  for (int i=0; i<n; ++i) {
    for (int j=1; j<n; ++j) {

      {
	std::stringstream ss;
	ss<<"("<<i<<","<<j<<")";
	depgraph::newtask (ss.str());
      }
            
      
      {
	std::stringstream ss;
	ss<<"A["<<j<<"]";
	depgraph::readwrite (ss.str());
      }

            
      {
	std::stringstream ss;
	ss<<"A["<<j-1<<"]";
	depgraph::readwrite (ss.str());
      }
      if (A[j] < A[j-1]) {
        int temp = A[j];
        A[j] = A[j-1];
        A[j-1] = temp;
      }
    }
  }
}

#define SIZE 10
int arr[SIZE];

int main () {

  for (int i=0; i<SIZE; ++i) {
    arr[i] = i*134+3542445%223;
  }

  bubblesort(arr, SIZE);

  depgraph::listall();
  
  return 0;
}