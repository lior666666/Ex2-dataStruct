#ifndef AVL_TREE_H_
#define AVL_TREE_H_
#include <iostream>
template<class T>
class AvlTree
    {
        T data;
        AvlTree<T>* right;
        AvlTree<T>* left;
        AvlTree<T>* next;
        AvlTree<T>* parent;
        AvlTree<T>* min_node;
        AvlTree<T>* max_node;
        int node_height; 
        int left_nodes_number;
        int right_nodes_number;
        int size;
        int index_counter;  
        // internal function to free and delete all the tree nodes 
        void cleanTree(AvlTree<T>* node)
        {
            if(node == NULL)
                return; 
            this->cleanTree(node->left);
            this->cleanTree(node->right);   
            delete node; 
        }
        int updatedRanks(AvlTree<T>* node)
        {
            if(node == NULL)
                return -1;
            node->left_nodes_number =  updatedRanks(node->left) + 1;
            node->right_nodes_number =  updatedRanks(node->right) + 1;
            return node->left_nodes_number + node->right_nodes_number;
        }
        // internal function, gets the balance factor of the node. 
        int getBalanceFactor(AvlTree<T>* tree_node)
        {
            int left_hight;
            int right_hight;
            if(tree_node->left!=NULL)
               left_hight = tree_node->left->node_height; 
            else
               left_hight = -1;    
            if(tree_node->right!=NULL)
               right_hight = tree_node->right->node_height; 
            else
                right_hight = -1; 

            return  left_hight - right_hight;
        }
        //internal function, updates the height of a certain node. 
        void updateHeight()
        {
            int left_hight;
            int right_hight;
            if(this->left!=NULL)
               left_hight = this->left->node_height; 
            else
               left_hight = -1;    
            if(this->right!=NULL)
               right_hight = this->right->node_height; 
            else
                right_hight = -1; 

            if(left_hight > right_hight)
                this->node_height = left_hight + 1;
            else
               this->node_height = right_hight + 1; 
        }
        // internal function, making rotation right to balance the tree. 
        AvlTree<T>* rotateRight()
        {
            AvlTree<T>* left_to_top_pointer = this->left; 
            // update right_nodes_number and left_nodes_number
            this->left_nodes_number = left_to_top_pointer->right_nodes_number; 
            left_to_top_pointer->right_nodes_number = left_to_top_pointer->right_nodes_number + this->right_nodes_number + 1; 
            AvlTree<T>* right_to_left_pointer = left_to_top_pointer->right;

            left_to_top_pointer->right = this;
            this->left = right_to_left_pointer;
            this->parent = left_to_top_pointer;
            if(right_to_left_pointer != NULL)
                right_to_left_pointer->parent = this; 
            this-> updateHeight();
            left_to_top_pointer-> updateHeight();

            return left_to_top_pointer;
        }

        // internal function, making rotation right to balance the tree. 
        AvlTree<T>* rotateLeft()
        {
            AvlTree<T>* right_to_top_pointer = this->right; 
            // update right_nodes_number and left_nodes_number
            this->right_nodes_number = right_to_top_pointer->left_nodes_number; 
            right_to_top_pointer->left_nodes_number = right_to_top_pointer->left_nodes_number + this->left_nodes_number + 1; 
            AvlTree<T>* left_to_right_pointer = right_to_top_pointer->left;

            right_to_top_pointer->left = this;
            this->right = left_to_right_pointer;
            this->parent = right_to_top_pointer;
            if(left_to_right_pointer != NULL)
                left_to_right_pointer->parent = this; 
            this-> updateHeight();
            right_to_top_pointer-> updateHeight();
            return right_to_top_pointer;
        }

        AvlTree<T>* findMostLeftNode(AvlTree<T>* tree_node)
        {
            if(tree_node == NULL)
                return NULL;
            if(tree_node->left == NULL)
                return tree_node;
            return findMostLeftNode(tree_node->left);
        }

        AvlTree<T>* findMostRightNode(AvlTree<T>* tree_node)
        {
            if(tree_node == NULL)
                return NULL;
            if(tree_node->right == NULL)
                return tree_node;
            return findMostRightNode(tree_node->right);
        }

        // internal function, creating and allocating a new node with data. 
        AvlTree<T>* createNewTreeNode(T data)
        {
             AvlTree<T>* newTreeNode = new AvlTree<T>;
                        newTreeNode->data = data; 
                        newTreeNode->left = NULL;
                        newTreeNode->right = NULL;
                        newTreeNode->next = NULL;
                        newTreeNode->parent = NULL; 
                        newTreeNode->node_height = 0;  
                        newTreeNode->size = 0; 
                        newTreeNode->left_nodes_number = 0;
                        newTreeNode->right_nodes_number = 0;
                        return newTreeNode; 
        }
         // internal function, helping us to insert properlly new data to our tree and keeping it balanced. 
        AvlTree<T>* insert(T data, AvlTree<T>* tree_node)
        {

            if(tree_node == NULL)
             {
                return createNewTreeNode(data); 
             }

            if(data < tree_node->data)
            {
                tree_node->left_nodes_number = tree_node->left_nodes_number + 1; 
                tree_node->left = this->insert(data, tree_node->left);
                tree_node->left->parent = tree_node;
            }

            else if(data > tree_node->data)
            {
                tree_node->right_nodes_number = tree_node->right_nodes_number + 1; 
                tree_node->right = this->insert(data, tree_node->right);
                tree_node->right->parent = tree_node;
            }                

            tree_node->updateHeight();

                // LL
                if(getBalanceFactor(tree_node)>1 && data < tree_node->left->data)
                {
                    return tree_node->rotateRight();
                }
                //LR
                if(getBalanceFactor(tree_node)>1 && data > tree_node->left->data)
                {
                    tree_node->left = tree_node->left->rotateLeft();
                    tree_node->left->parent = tree_node;
                    return tree_node->rotateRight();
                }
                //RR
                if(getBalanceFactor(tree_node)<-1 && data > tree_node->right->data)
                {
                    return tree_node->rotateLeft();
                }
                //RL
                if(getBalanceFactor(tree_node)<-1 && data < tree_node->right->data)
                {
                    tree_node->right = tree_node->right->rotateRight();
                    tree_node->right->parent = tree_node; 
                    return tree_node->rotateLeft();
                }

                return tree_node; 
        }
        // internal function, helps us to remove data from the tree and keep it as a balanced AVL tree. 
        AvlTree<T>* removeNode(T data, AvlTree<T>* tree_node)
        {
            if(tree_node == NULL)
            {
                return NULL; 
            }

            if(data < tree_node->data)
            {
                tree_node->left_nodes_number = tree_node->left_nodes_number - 1;
                tree_node->left = this->removeNode(data, tree_node->left);
                if(tree_node->left !=NULL)
                    tree_node->left->parent = tree_node; 
            }

            else if(data > tree_node->data)
            {
                tree_node->right_nodes_number = tree_node->right_nodes_number - 1;
                tree_node->right = this->removeNode(data, tree_node->right);
                if(tree_node->right !=NULL)
                    tree_node->right->parent = tree_node;
            }

            else
            {
                if(tree_node->left == NULL || tree_node->right == NULL)
                {
                    AvlTree<T>* temp_node; 
                    if(tree_node->left != NULL)
                        temp_node = tree_node->left; 
                    else
                        temp_node = tree_node->right;      
                    if(temp_node == NULL)
                    // no child
                    {
                        temp_node = tree_node;
                        tree_node = NULL; 
                    }     
                    else
                    {
                        // one child 
                        // make a copy node function(?)
                        tree_node->data = temp_node->data;
                        tree_node->left = NULL;
                        tree_node->right = NULL;
                        tree_node->node_height = 0;
                        tree_node->right_nodes_number = 0;
                        tree_node->left_nodes_number = 0;
                        tree_node->size = 0;
                    } 
                    delete temp_node;     
                }
                else
                {
                    AvlTree<T>* temp_node = findMostLeftNode(tree_node->right);
                    // make copy node function(?)
                   tree_node->data = temp_node->data;
                   tree_node->right_nodes_number = tree_node->right_nodes_number -1;
                   tree_node->right = removeNode(tree_node->data, tree_node->right); // this will delete the node that we just switched with our's.   

                }
            }
            if(tree_node == NULL)
                return NULL; 

            tree_node->updateHeight();

            // LL
                if(getBalanceFactor(tree_node)>1 && getBalanceFactor(tree_node->left)>=0)
                {
                    return tree_node->rotateRight();
                }
                //LR
                if(getBalanceFactor(tree_node)>1 && getBalanceFactor(tree_node->left)<0)
                {
                    tree_node->left = tree_node->left->rotateLeft();
                    if (tree_node->left!=NULL)
                    {
                        tree_node->left->parent = tree_node;
                    }
                    return tree_node->rotateRight();
                }
                //RR
                if(getBalanceFactor(tree_node)<-1 && getBalanceFactor(tree_node->right)<=0)
                {
                    return tree_node->rotateLeft();
                }
                //RL
                if(getBalanceFactor(tree_node)<-1 && getBalanceFactor(tree_node->right)>0)
                {
                    tree_node->right = tree_node->right->rotateRight();
                    if (tree_node->right!=NULL)
                    {
                        tree_node->right->parent = tree_node;
                    }
                    return tree_node->rotateLeft();
                }

                return tree_node;

        }

        // internal function to print all the data inOrder. 
        void printTr()
        {
            if(this->left!=NULL)
                this->left->printTr();
            std::cout << this->data <<" " <<"Right: "<<this->right_nodes_number <<"Left:" <<this->left_nodes_number  << std::endl; 
            if(this->right!=NULL)
                this->right->printTr();     
        }
        AvlTree<T>* buildTree(T* array,  int left, int right)
        {
            if(left == right)
            {
                return createNewTreeNode(array[left]);
            }
            if(left+1 == right)
            {
                AvlTree<T>* new_node = createNewTreeNode(array[left]);
                new_node->right = createNewTreeNode(array[right]);
                new_node->right->parent = new_node; 
                new_node->updateHeight(); 
                return new_node; 
            }

            int middle = (right-left)/2 + left; 
            AvlTree<T>* new_node = createNewTreeNode(array[middle]);
            new_node->right = buildTree(array, middle + 1, right);
            new_node->right->parent = new_node;
            new_node->left = buildTree(array, left, middle - 1);
            new_node->left->parent = new_node;
            new_node->updateHeight(); 
            return new_node; 
        }
         // internal function to find a node as the data. returns NULL if there is no node like that. 
        AvlTree<T>* findNode(T data, AvlTree<T>* tree_node)
        {
            if(tree_node ==NULL)
                return NULL; // change to NULL; 
            else if(data == tree_node->data)
                return tree_node;
            else if (tree_node->data < data)   
                return findNode(data, tree_node->right);
            else  
                return findNode(data, tree_node->left);            
        }
        AvlTree<T>* getNumberNode(AvlTree<T>* tree_node, int i, int sum)
        {
            if(tree_node == NULL)
                return NULL;
            if(i < 1 + tree_node->left_nodes_number + sum)
                tree_node = getNumberNode(tree_node->left, i, sum); 
            else if(i > 1 + tree_node->left_nodes_number + sum) 
            {
                int new_sum = sum + tree_node->left_nodes_number +1;
                tree_node = getNumberNode(tree_node->right, i, new_sum); 
            }
            return tree_node;  
        }

    public:

        AvlTree<T>(): data(), right(), left(), next(), parent(), min_node(), node_height(0), left_nodes_number(0), right_nodes_number(0), size(0), index_counter(0) {}

        AvlTree<T>(T* array, int size_of_tree): data(), right(), left(), next(), parent(), min_node(), node_height(0),left_nodes_number(0), right_nodes_number(0), size(size_of_tree+1), index_counter(0) // building AVL tree from a sorted array, O(n) compleccity. 
        {
            this->next = buildTree(array, 0, size_of_tree );
            this->min_node = findMinNode(); 
            this->max_node = findMaxNode();
            updatedRanks(this->next);// make the tree ranked tree; 
        }

        ~AvlTree<T>()
        {  
            this->cleanTree(this->next);   
        }
        // insert the data to the tree and keep it balanced. returns false if this data is already inside the tree and true if it's not and it put it now.
        bool insertElement(T data)
        {
            //add condition to check if it's already in! 
            if(this->next == NULL) // MAKE INTERNAL FUNC
            {
                AvlTree<T>* newTreeNode = createNewTreeNode(data); 
                this->next = newTreeNode; 
                this->next->parent = NULL; 
                this->min_node = findMinNode(); 
                this->max_node = findMaxNode();
                size ++;
                return true;
            }
            else
            {
                if(findNode(data, this->next) != NULL)
                    return false; 
                this->next = this->insert(data, this->next); 
                this->next->parent = NULL; 
                this->min_node = findMinNode();
                this->max_node = findMaxNode();
                size++;
                return true;   
            }   
        }
        // remove a data from the tree and keep it balanced. 
        bool removeElement(T data)
        {
            AvlTree<T>* node = findNode(data, this->next);
            if(node ==NULL)
            {
                return false; 
            }
            this->next = removeNode(data, this->next); 
            if(this->next!=NULL)
                this->next->parent = NULL;      
            this->min_node = findMinNode();
            this->max_node = findMaxNode();
            size--;
            return true; 
        }
        // gets the size the the tree 
        int getTreeSize()
        {
            return size; 
        }
        // prints all the data in the tree by order from the smallest key to the biggest one. 
        void printTree()
            {
                if(this->next!=NULL)
                {
                    this->next->printTr();
                } 
                else // NEED TO SEE WHAT SOULD WE PRINT WHEN TREE IS EMPTY 
                {
                  std::cout <<  " " << std::endl;   
                }   
            }
        void printNode()
        {
            std::cout << this->data << std::endl; 
        } 
        AvlTree<T>* getNext()
        {
            return this->next;
        }  
        AvlTree<T>* getLeft()
        {
            return this->left;
        }
        AvlTree<T>* getRight()
        {
            return this->right;
        }
        AvlTree<T>* getParent()
        {
            return this->parent;
        }
        // gets the height of the tree. (maybee we won't need that one.)    
        int getHeight()
        {
            return this->next->node_height; 
        }  
        void moveToArray(T* array, AvlTree<T>* tree)
        {
            if(tree == NULL)
               return ;  
            moveToArray(array, tree->left);
            array[index_counter] = tree->data; 
            index_counter++;
            moveToArray(array, tree->right);
        }
        AvlTree<T>* merge(AvlTree<T>* tree2)
        {
            T* array1 = new T[this->size];
            T* array2 = new T[tree2->size];
            index_counter = 0; 
            this->moveToArray(array1, this->next);
            index_counter = 0; 
            tree2->moveToArray(array2, tree2->next);
            if(this->isEmpty() && tree2->isEmpty())
            {
                delete[] array1; 
                delete[] array2; 
                return new AvlTree<T>(); 
            }
            if(this->isEmpty()) 
            {
                delete[] array1; 
                delete[] array2; 
                return new AvlTree<T>(array2, tree2->size-1);
            }
            if(tree2->isEmpty()) 
            {
                delete[] array1; 
                delete[] array2; 
                return new AvlTree<T>(array1, this->size-1); 
            }         
            //merge between 2 arrays into one sorted array. 

            T* new_array = new T[this->size + tree2->size];  
            int i = 0; 
            int j = 0; 
            int k = 0;
            while(k<this->size + tree2->size)
            {
                if(j>=tree2->size)
                {
                    new_array[k] = array1[i];
                    //std::cout << new_array[k] << std::endl; 
                    i++;
                    k++;
                }
                else if(i>=this->size)
                {
                    new_array[k] = array2[j];
                    //std::cout << new_array[k] << std::endl; 
                    j++;
                    k++;
                }
                else
                {
                    if(array1[i]<array2[j])
                    {
                       new_array[k] = array1[i];
                     //  std::cout <<  array1[i] << std::endl; 
                      // std::cout << new_array[k] << std::endl; 
                        i++; 
                        k++;
                    }
                    else
                    {
                        new_array[k] = array2[j];
                      //   std::cout <<array2[j] << std::endl; 
                      //  std::cout << new_array[k] << std::endl; 
                        j++;
                        k++;
                    }    
                }
            }
            AvlTree<T>* new_tree = new AvlTree<T>(new_array, this->size + tree2->size-1);
            delete[] array1;
            delete[] array2;
            delete[] new_array; 
            return new_tree;       
        }
        AvlTree<T>* getNode(T data)
        {
            AvlTree<T>* node = findNode(data, this->next);  
            return node;      
        } 
        // returns the data of the actual object we need. (maybee we won't need that one.) 
        T* getNodeData(T data)
        {
            AvlTree<T>* node = findNode(data, this->next);  
            if(node == NULL)
                return NULL;
            return &(node->data);      
        } 
        T getData()
        {
            return (this->data);      
        } 
        T* getDataPointer()
        {
            return &(this->data);      
        } 
        // insert data to a left son of a specific node in the tree. (usfull when we are building a tree from scratch node by node.)
        void insertLeftSon(T data, AvlTree<T>* tree_node)
        {
            tree_node->left = createNewTreeNode(data);
        }
        // insert data to a right son of a specific node in the tree. (usfull when we are building a tree from scratch node by node.)
        void insertRightSon(T data, AvlTree<T>* tree_node)
        {
            tree_node->right = createNewTreeNode(data);
        }
        // insert data to first node of the tree. (usfull when we are building a tree from scratch node by node.)
        void insertTopFather(T data)
        {
            this->next = createNewTreeNode(data);
        }
        void clearTree()
        {
            cleanTree(this->next); 
            this->next = NULL;
        }

        AvlTree<T>* findMinNode() // log(n)
        {
            return findMostLeftNode(this->next);
        }

        AvlTree<T>* findMaxNode() // log(n)
        {
            return findMostRightNode(this->next);
        }

        AvlTree<T>* getMinNode() // log(n)
        {
            return min_node;
        }
        
        AvlTree<T>* getMaxNode() // log(n)
        {
            return max_node;
        }
        bool isEmpty()
        {
            return this->next == NULL; 
        }
        int getLeftNodesNumber()
        {
            return this->left_nodes_number; 
        }
        int getRightNodesNumber()
        {
            return this->right_nodes_number; 
        }
        AvlTree<T>* getNumber(int i)
        {
            return getNumberNode(this->next, i, 0);
        }
        int getSize()
        {
            return size; 
        }
    };            
#endif