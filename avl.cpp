#include <iostream> 
using namespace std;

/*  bf = height of left subtree - height of right subtree


                       (this is a right left rotation case)
                       4
                     /    \                                         
                   2        8  (bf = -2 at 8) (second rotate 8 towards left)
                  / \        \                
                 1   3        10 (first rotate 10 towards right)
                             /                
                            9    

Above is the bst we are working with and is unbalanced


                       4
                     /    \                                         
                   2        9    
                  / \       / \               
                 1   3     8   10 (after right left rotation this is a balanced tree)
                                           
                               
                             thus with left rotation at 8 we get a balanced tree  
                  


*/

struct node 
{
    int info;
    node *right, *left;

};

class BST  // avl
{
    node  *temp, *temp1 , *temp2,*temp3;
    int h;
    

    public:
    node *root;

    BST()
    {
        root = NULL;
        temp = NULL;
        temp1 = NULL;
        temp2 = NULL;
        

    }

    void insert(node * , int);
    bool search(node *, int);
    void del(node * , int);
    void inorder(node *);
    void in_successor(node *);
    void in_predecessor(node *, int);

    int height(node *);
    int bfac(node *);
    node* rr(node *);
    node* rl(node *);


};

bool BST::search(node *temp, int key)
{
    if(key < temp -> info)
    {
        if(temp -> left != NULL)
        {
            return search(temp-> left, key);
        }

    }

    if(key > temp -> info)
    {
        if(temp -> right != NULL)
        {
            return search(temp -> right,key);
        }
    }

    if(temp -> info == key)
    {
        
        return 1;
    }

    
        return 0;
    

    
}



int BST::height(node *temp)
{
    int lh = 0;
    int rh = 0;
    
   

    if(temp -> left != NULL)
    {
        
        lh++;
        lh = height(temp -> left) +lh;
    }

    if(temp -> right != NULL)
    {
        
        rh++;
        rh = height(temp->right) + 1;
    }

    
    
    if(temp -> right == NULL && temp -> left == NULL)
    {

        return 0;
    }

   

    if(lh> rh)
    {
        h = lh;
        return h;

    }
    if(rh > lh)
    {
        h =rh;
        return h;

    }

    if(lh == rh)
    {
        h = lh;
        h = rh;
        return h;
    }

    return h;

    


     
    

}

int BST::bfac(node *temp)
{
    int lh = 0;
    int rh = 0;

    if(temp -> left != NULL)
    {
        lh = height(temp -> left) +1;
    }

    if(temp -> right != NULL)
    {
        rh = height(temp->right) +1;
    }

    int bf = lh - rh;
    return bf;


}

node* BST::rr(node *temp)
{
    

    
        if(temp -> left -> right == NULL)
        {
            temp1 = temp -> left;
            temp -> left = NULL;
            temp1 -> right = temp;
            return temp1;
        }

        if(temp -> left -> right != NULL)
        {
            temp1 = temp -> left;
            temp -> left = NULL;
            temp2 = temp1 -> right;
            temp1 -> right = temp;
            temp -> left = temp2;
            
            return temp1;
        }

        return temp1;



}

node* BST::rl(node *temp)
{
    if(temp -> right -> left == NULL)
    {
        temp1 = temp -> right;
        temp -> right = NULL;
        temp1 -> left = temp;
        return temp1;
    }

    if(temp -> right -> left != NULL)
    {
        temp1 = temp -> right;
        temp2 = temp1 -> left;
        temp -> right  = NULL;
        temp1 -> left = temp;
        temp -> right = temp2;
        
        return temp1;

    }

    return temp1;

    

}





void BST::inorder( node *r)
{
    if(r != NULL)
    {
        inorder(r->left);
        cout<<r -> info<<" ";
        inorder(r -> right);
    }
    return;

}



void BST::insert(node *temp , int key)
{
    int bf;
    

    if(root == NULL)
    {
        root = new node;

        root -> info = key;
        root -> left = NULL;
        root -> right = NULL;

        return;

    }

    if(key < temp -> info && temp-> left == NULL)
    {
        temp -> left = new node;
        temp -> left -> info = key;
        temp-> left -> right = NULL;
        temp -> left -> left = NULL;
        return;
        

    }

   



    if(key > temp->info && temp -> right == NULL)
    {
        temp -> right = new node;
        temp -> right -> info = key;
        temp ->right -> left = NULL;
        temp -> right -> right = NULL;
        return;
    }

    

    



    if(key < temp -> info)
    {
        insert(temp -> left , key);

    }

     // rotation portion

     //rotation for left left and left right cases when bf > 1
    if(temp -> left != NULL)
    {
        if(temp == root) //root case where bf is disturbed at the root
        {
            bf = bfac(root);
            if(bf > 1 && bfac(root -> left) <= 1)
            {
                if(search(root -> left -> left,key))
                {
                    root = rr(root);
                    return;

                }

                if(search(root -> left -> right, key))
                {
                    root -> left = rl(root -> left);
                    root = rr(root);
                    return;
                }

                
                
            }
            
        }
        //non root case:
       
        bf = bfac(temp -> left);

        if(bf > 1) // the insertion was done in left child of current node
        {
            //two cases for left child  case

            //ll:
            if(search(temp -> left -> left ->left,key))
            {
                temp -> left = rr(temp -> left);


                return;
            }

            //lr:
            if(search(temp -> left -> left -> right,key))
            {
                temp -> left -> left = rl(temp -> left -> left);
                temp -> left = rr(temp -> left);
                return;
            }

           

        }

        

    }

    if(key > temp -> info)
    {
        insert(temp -> right ,key);
    }

    //rotation portion for right right and right left cases

    if(temp -> right != NULL)
    { //root case
        if(temp == root)
        {
            bf = bfac(root);

            if(bf < -1 && bfac(root -> right) >= -1)
            {
                root = rl(root);
                return;
            }

           


        }

        //non root case

        bf = bfac(temp -> right);
        if(bf < -1)
        {
            if(search(temp -> right -> right ->right, key))
            {
                temp -> right = rl(temp -> right);
                return;

            }

            if(search(temp -> right -> right -> left,key))
            {
                temp -> right -> right = rr(temp -> right -> right);
                temp -> right = rl(temp -> right);
                return;
            }
            

        }

       

    }


   

    
}

void BST::in_successor(node *r)
{
    
    r = r -> right;

    

    while( r ->  left != NULL)
    {
        r = r -> left;
    }
    temp2 = r;
     
    return;
}


void BST::del(node *r, int key)
{
    
        temp = r;
    
  
    
    
    //leaf node

   

    if(temp -> left != NULL ) // to prevent segmentation fault core dump error
    {
        if(temp -> left -> info == key)
        {
            if((temp -> left -> left == NULL) && temp -> left -> right == NULL)
            {
                delete temp -> left;
                temp -> left = NULL;
                
                return;

            }
        }
        
    }

    if(temp -> right != NULL)
    {
        if(temp -> right -> info == key)
        {
            if(temp ->right -> left == NULL && temp -> right -> right == NULL)
            {
                delete temp -> right ;
                temp -> right = NULL;
                return;

            }
        }
    }


    //one child


    if(temp -> left  != NULL) // to prevent segmentation fault core dump error
    {
        if(temp -> left -> info == key) 
        {
            if(temp -> left -> left != NULL && temp -> left -> right == NULL)
            {
                temp1 = temp -> left ;
                temp -> left = temp1-> left;
                delete temp1;
                temp1 = NULL;
                return;
                

            }

            if(temp -> left -> left == NULL && temp -> left -> right != NULL)
            {
                temp1 = temp -> left;
                temp -> left = temp1 -> right;
                delete temp1;
                temp1 = NULL;
                return;


            }

        }
        
    }

    if(temp -> right != NULL)
    {
        if(temp -> right -> info == key)
        {
            if(temp -> right -> left != NULL && temp -> right -> right == NULL)
            {
                temp1 = temp -> right;
                temp -> right = temp1 -> left;
                delete temp1;
                temp1 = NULL;
                return;

            }

            if(temp -> right -> left == NULL && temp -> right -> right != NULL)
            {
                temp1 = temp -> right;
                temp -> right = temp1 -> right;
                delete temp1;
                temp1 = NULL;
                return;

            }

        }

    }

    // two children
 

    if(temp -> left != NULL)
    {
        if(temp -> left -> info == key)
        {

            if(temp -> left -> left != NULL && temp -> left -> right != NULL)
            {
                temp1 = temp-> left;
                

                //finding inorder successor
                in_successor(temp->left);

                temp1 -> info = temp2 -> info;
                del(temp1 ,temp2->info);
                return;



                


            }

        }
       

       

    }


    if(temp -> right != NULL)
    {
        if(temp -> right -> info == key)
        {
            if(temp -> right -> left != NULL && temp -> right -> right != NULL)
            {
                temp1 = temp-> right;
                

                //finding inorder successor
                in_successor(temp1);
                

                temp1 -> info = temp2 -> info;
                del(temp1 ,temp2->info); //not temp1 -> right because we are already standing one node before the node we are about to delete
                return;               

            }
        }
        

    }

    if(key < temp->info)
    {
        del(temp -> left,key);
        return;
    }

    if(key > temp->info)
    {
        del(temp -> right,key);
        return;
    }






    
    
    
   

    



}

int main()
{
    BST obj;

    //checking insert function

    // obj.insert(obj.root, 5);
    // obj.insert(obj.root, 2);
    // obj.insert(obj.root,1);
    // obj.insert(obj.root, 4);
    // obj.insert(obj.root, 0);
    // obj.insert(obj.root, -1); 

    obj.insert(obj.root, 4); 
    obj.insert(obj.root, 5); 
    obj.insert(obj.root, 6); 
    obj.insert(obj.root, 7);
    obj.insert(obj.root, 8);






    obj.inorder(obj.root); 
    cout<<endl;

    

    



    cout<<obj.root -> right->right-> info ;
    cout<<endl;

   

    // int v = obj.bfac(obj.root );
    // cout<<v;
    // cout<<endl;

    // cout<<obj.root -> info;
    // cout<<endl;

    // cout<<obj.root -> left -> info;
    // cout<<endl;

    // cout<<obj.root -> right -> info;
    // cout<<endl;





    

    // bool b = obj.search(obj.root, 15);
    // cout<<b<<endl;

    //checking balance factor function
    // int bf;
    // bf = obj.bfac(obj.root);
    // cout<<"Balance factor of "<<obj.root ->info<<" is : "<<bf<<endl;

    // bf = obj.bfac(obj.root -> left);
    // cout<<"Balance factor of "<<obj.root->left ->info<<" is : "<<bf<<endl;

    // bf = obj.bfac(obj.root->right);
    // cout<<"Balance factor of "<<obj.root->right ->info<<" is : "<<bf<<endl;

    // bf = obj.bfac(obj.root -> left -> left);
    // cout<<"Balance factor of "<<obj.root->left ->left ->info<<" is : "<<bf<<endl;

    // bf = obj.bfac(obj.root-> right -> left);
    // cout<<"Balance factor of "<<obj.root-> right -> left ->info<<" is : "<<bf<<endl;



    //testing height funtion

    // int t = obj.height(obj.root);
    // cout<<"height of tree with root " <<obj.root -> info<<" is "<<t<<endl;

    // t = obj.height(obj.root->right);
    // cout<<"height of tree with root " <<obj.root ->right-> info<<" is "<<t<<endl;

    // t = obj.height(obj.root->left);
    // cout<<"height of tree with root " <<obj.root ->left-> info<<" is "<<t<<endl;

    // t = obj.height(obj.root->left->left);
    // cout<<"height of tree with root " <<obj.root ->left-> left ->info<<" is "<<t<<endl;

    //testing delete function

    //checks for first case

    // obj.del(obj.root, 1);
    // cout<<endl;
    // obj.inorder(obj.root);
    

    // obj.del(obj.root, 3);
    // cout<<endl;
    // obj.inorder(obj.root);

    // obj.del(obj.root, 9);
    // cout<<endl;
    // obj.inorder(obj.root);
    

    // // obj.del(obj.root, 20);
    // // cout<<endl;
    // // obj.inorder(obj.root);

    // // obj.del(obj.root, 15);
    // // cout<<endl;
    // // obj.inorder(obj.root);

    // obj.del(obj.root, 10);
    // cout<<endl;
    // obj.inorder(obj.root);

    // obj.del(obj.root, 8);
    // cout<<endl;
    // obj.inorder(obj.root);

    // obj.del(obj.root, 2);
    // cout<<endl;
    // obj.inorder(obj.root);

    //checks for second case

    // obj.del(obj.root, 10);
    // cout<<endl;
    // obj.inorder(obj.root);

    // obj.del(obj.root, 8);
    // cout<<endl;
    // obj.inorder(obj.root);

    // obj.del(obj.root, 3); // deleting 3 so that 2 can have 1 child
    // cout<<endl;
    // obj.inorder(obj.root);

    // obj.del(obj.root, 2); //now 2 has 1 child so deleting 2
    // cout<<endl;
    // obj.inorder(obj.root);

    //checking for third case

    // obj.in_successor(obj.root -> left);

    // obj.del(obj.root, 2); 
    // cout<<endl;
    // obj.inorder(obj.root);
    

    // obj.del(obj.root, 10); 
    // cout<<endl;
    // obj.inorder(obj.root);





    


    

}