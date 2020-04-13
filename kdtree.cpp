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

template <typename T>
class KdTree {
public:
  typedef vector<T> container_t; 
  
  KdNode<T> *root;
  int k;
  
  KdTree(int _k):root(nullptr), k(_k) {
  }

  ~KdTree() {
  }

  bool cmpNode(KdNode<T> *a, KdNode<T> *b) {
    return (a->point == b->point);
  }

  bool searchR(KdNode<T> *node, KdNode<T> *_root) {
    if (_root == nullptr) return false;
    if (cmpNode(_root, node)) return true;

    int dim = _root->level % k;

    if (node->point[dim] < _root->point[dim])
      return searchR(node, _root->left);

    return searchR(node, _root->right);
  }

  bool search(container_t _point) {
    KdNode<T> *node = new KdNode<T>(_point);
    
    return searchR(node, root);
  }

  bool insertR(KdNode<T> *node, KdNode<T> *_root) {
    int dim = _root->level % k;
    node->level++;
    
    if (node->point[dim] < _root->point[dim]) {
      if (_root->left == nullptr) {
        _root->left = node;
        return true;
      } else
        insertR(node, _root->left);
    } else {
      if (_root->right == nullptr) {
        _root->right = node;
        return true;
      } else 
        insertR(node, _root->right);
    }
    return false;
  }

  bool insert(container_t _point) {
    if (root == nullptr) {
      root = new KdNode<T>(_point);
      return true;
    } 
    
    KdNode<T> *tmp = new KdNode<T>(_point);
      
    return insertR(tmp, root);
  }

  void printTreeR(KdNode<T> *root, int space) {
    if (root == nullptr) return;
    
    space += 10;
    
    printTreeR(root->right, space);
    
    cout << endl;
    for (int i = 5; i < space; i++)
      cout << " ";
    cout << root << endl;

    printTreeR(root->left, space);

  }

  void printTree() {
    printTreeR(root, 0);
  }
};

int main() 
{
  // initialize kdtree with k = 2
  KdTree<int> tree(2); 

  // initialize points
  vector<int> v{1,2};
  vector<int> v2{5,6};
  vector<int> v3{-2,6};
  vector<int> v4{9,6};
  
  // insert points
  tree.insert(v); 
  tree.insert(v2); 
  tree.insert(v3);

  // display search function 
  cout << tree.search(v) << endl;
  cout << tree.search(v2) << endl;
  cout << tree.search(v3) << endl;
  cout << tree.search(v4) << endl;
  
  tree.printTree();
  return 0;
}
