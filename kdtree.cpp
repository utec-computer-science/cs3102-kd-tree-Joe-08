#include <iostream>
#include <vector>
#include <cstdio>
using namespace std;

template <typename T>
class KdNode {
  public:
    typedef vector<T> container_t; 

    container_t point;
    int level;
    
    KdNode* left;
    KdNode* right;

    KdNode() :level(0), left(nullptr), right(nullptr) {
    }
    
    KdNode(container_t _point) :level(0), left(nullptr), right(nullptr) {
      point = _point;
    }

    ~KdNode() {
    }

    friend ostream& operator<<(ostream &out,KdNode<T> *node) {
      if (node != nullptr){
        out << "(";
        for (int i = 0; i < node->point.size(); i++) {
          if (i != node->point.size() - 1) 
            out << node->point[i]<< ",";
          else
            out << node->point[i];
        }
       out << ")"; 
      }
      return out;
    }
};

int main() 
{

  return 0;
}
