#include <iostream>
using namespace std;


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
        temp3 = NULL;
        

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

node* BST::rr(node *temp)
{
    temp1 = temp -> left;
    temp2 = temp1 -> right;

    temp1-> right = temp;
    temp -> left = temp2;
    

    
        
    return temp1;



}
node* BST::rl(node *temp)
{
    temp1 = temp -> right;
    temp2 = temp1 -> left;

    temp1 -> left = temp;
    temp -> right = temp2;


    return temp1;

    

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




void BST::insert(node *temp , int key)
{
    

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

    if(key > temp -> info)
    {
        insert(temp -> right ,key);
    }

    //cases

    int bf ;

    
    
        

    
    if(temp -> left != NULL)
    {
        //non root cases
        
        bf = bfac(temp -> left);

        if(bf > 1 ) //left left case
        {
            if( key < temp -> left ->left -> info)
            {
                temp -> left = rr(temp -> left);
                return;

            }


        }

        if(bf > 1  ) //left right case
        {
            if( key > temp -> left -> left -> info)
            {
                temp -> left -> left = rl(temp -> left -> left);
                temp -> left = rr(temp -> left);
                return;

            }


        }
    }


    if(temp -> right != NULL)
    {


        bf = bfac(temp -> right);

        if(bf < -1 ) 
        {
            if(key > temp -> right -> right -> info)//right right case
            {
                temp -> right = rl(temp -> right);
                return;

            }


        }

    
        if(bf < -1 )
        {
            if(key < temp -> right -> right -> info)
            {
                temp -> right -> right = rr(temp -> right -> right);
                temp -> right = rl(temp -> right);
                return;

            }
        
        }
    }

    if(temp != root)
    {
        return;
    }

    //root cases
    // if(temp -> left != NULL && temp -> right != NULL)
    // {
        // if(temp == root && bfac(temp -> left) <= 1 && bfac(temp -> right) >= -1 )
        // {
            bf = bfac(root);

            if(bf > 1)
            {
                if(key < root -> left -> info) //ll case
                {
                    root = rr(root);
                    return;

                }

                if(key > root -> left -> info) //lr case
                {
                    root -> left = rl(root -> left);
                    root = rr(root);
                    return;

                }
            }

            if(bf < -1)
            {
                if(key > root -> right -> info) //rr case
                {
                    root = rl(root);
                    return;
                    
                }

                if(key < root -> right-> info) //rl case
                {
                    root -> right = rr(root -> right);
                    root = rl(root);
                    return;


                }

            }
        // }
    // }

    

  
   

    
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

    obj.insert(obj.root,1);
    obj.insert(obj.root,2);
    obj.insert(obj.root,3);
    obj.insert(obj.root,4);
    obj.insert(obj.root,5);
    obj.insert(obj.root,6);
    obj.insert(obj.root,7);
    obj.insert(obj.root,16);
    obj.insert(obj.root,15);
    obj.insert(obj.root,14);
    obj.insert(obj.root,13);
    

    obj.inorder(obj.root); 
    cout<<endl;

    cout<<obj.root-> info<<endl;

   

 





    


    

}