#include <iostream>

using namespace std;

int additn = 0;

//Function has 2 purposes
//First, Function is used to check whether a set of edges contains a loop or not.(When int Q = 0)
//Later, it is used to deduce the K and L part from the tree chosen by code(When int Q != 0)
bool loop(int tree[][2], int number, int sum_of_edges , int Q , int tree_a[][2], int tree_k[][2])
{
    int occ[sum_of_edges];
    for(int i = 0 ; i < sum_of_edges ; i++)
        occ[i] = 0;

    for (int s = 0 ; s < number ; s++)
    {
        occ[tree[s][0]]++;
        occ[tree[s][1]]++;
    }

int counter = 0;
for(int i = 0 ; i < sum_of_edges ; i++)
    {
        if(occ[i] == 1)
        {
            counter++;
            for (int k = 0 ; k < number ; k++)
        {
                if((tree[k][0] == i) || (tree[k][1] == i))
                {
                    tree[k][0] = -1;
                    tree[k][1] = -1;
                }
            }
        }
    }
    if (counter > 0)
    {
        bool ans;
        ans = loop(tree, number, sum_of_edges, Q , tree_a, tree_k );
        return ans;
    }
    else
    {
        if (Q == 0)
        {
            for(int j = 0 ; j < number ; j++)
            {
                if(tree[j][0] != -1)
                    return true;
            }
            return false;
        }

        else
        {
            int Y = additn;
            int K = additn;
            int same = 0;
            for(int h = 0 ; h < Q ; h++)
            {
                if((occ[tree_a[h][0]]==2) && (occ[tree_a[h][1]]==2))
                {
                    for(int x = 0 ; x < Y ; x++)
                    {
                        if((tree_k[x][0] == tree_a[h][0]) && (tree_k[x][1] == tree_a[h][1]))
                        {
                            same = 1;
                            K++;
                            break;
                        }
                    }
                    if(same == 0)
                    {
                        tree_k[Y][0]=tree_a[h][0];
                        tree_k[Y][1]=tree_a[h][1];
                        Y++;
                        K++;
                    }
                }
                same = 0;
            }
            if(additn == K)
                return false;
            else
            {
                additn = Y;
                return true;
            }

        }
    }
}

int main(){

//initializing array for part A and B
int Na;
cout<<"How many edges of A are there: ";
cin >> Na;
int a[Na][2];

int Nb;
cout<<"How many edges of B are there: ";
cin >> Nb;
int b[Nb][2];


int tree_a[Na][2];//array for tree for A
int tree_k[Na][2];//array for tree for K
int tree_b[Nb][2];//array for tree for B
int co_tree_b[Nb][2];//array for co-tree for B
int tree[Na + Nb][2];//array for net tree of graph extended into B from tree of A


int number_of_elements_in_tree = 0;//number of elements in tree
int co_tree= 0;//number of elements in co-tree of B

for(int i = 0 ; i < Na ; i++)
{
    tree_a[i][0] = -1;
    tree_a[i][1] = -1;
    tree_k[i][0] = -1;
    tree_k[i][1] = -1;
}

for(int i = 0 ; i < Nb ; i++)
{
    tree_b[i][0] = -1;
    tree_b[i][1] = -1;
    co_tree_b[i][0] = -1;
    co_tree_b[i][1] = -1;
}

for(int i = 0 ; i < Na + Nb ; i++)
{
    tree[i][0] = -1;
    tree[i][1] = -1;
}

//Inputting the edges corresponding to part A and B
cout<<"Note: Numbering of nodes should start from number 0"<< endl;
cout<<"Please enter the edges of A in the format x y where x,y are nodes of the edge"<<endl;
for(int i = 0 ; i < Na ; i++)
{
    cout << "The " << i+1 << " edge of A is :";
    cin >> a[i][0] >> a[i][1];
    tree[number_of_elements_in_tree][0] = a[i][0];
    tree[number_of_elements_in_tree][1] = a[i][1];
    number_of_elements_in_tree++;

    int copied[number_of_elements_in_tree][2];
    for(int i = 0 ; i < number_of_elements_in_tree ; i++)
    {
        copied[i][0] = tree[i][0];
        copied[i][1] = tree[i][1];
    }
    //finding whether a new edge of A added forms a loop with existing tree or not
    //if not, add that edge to existing tree else don't add
    if(loop(copied, number_of_elements_in_tree , Na + Nb ,  0 , tree_a, tree_k ) == false)
    {
        tree_a[number_of_elements_in_tree - 1][0] = a[i][0];
        tree_a[number_of_elements_in_tree - 1][1] = a[i][1];
    }
    else
    {
        tree[number_of_elements_in_tree][0] = -1;
        tree[number_of_elements_in_tree][1] = -1;
        number_of_elements_in_tree--;
    }
}

//Q is number of elements in tree of A.. Will now extend this tree into part B of graph
int Q = number_of_elements_in_tree;

cout<<"Please enter the edges of B: ";
for(int i = 0 ; i < Nb ; i++)
{
    cout << "The " << i+1 << " edge of B is: ";
    cin >> b[i][0] >> b[i][1];
    tree[number_of_elements_in_tree][0] = b[i][0];
    tree[number_of_elements_in_tree][1] = b[i][1];
    number_of_elements_in_tree++;

    int copied[number_of_elements_in_tree][2];
    for(int i = 0 ; i < number_of_elements_in_tree ; i++)
    {
        copied[i][0] = tree[i][0];
        copied[i][1] = tree[i][1];
    }
//again checking if loop formed or not by edge of B as earlier
    if(loop(copied, number_of_elements_in_tree , Na + Nb , Q , tree_a,tree_k) == false)
    {
        tree_b[number_of_elements_in_tree - Q - 1][0] = b[i][0];
        tree_b[number_of_elements_in_tree - Q - 1][1] = b[i][1];

    }
    else
    {
        co_tree_b[co_tree][0] = b[i][0];
        co_tree_b[co_tree][1] = b[i][1];
        co_tree++;
        tree[number_of_elements_in_tree][0] = -1;
        tree[number_of_elements_in_tree][1] = -1;
        number_of_elements_in_tree--;
    }
}

//Now, the tree is ready!
cout<< "Tree " << endl;
for(int k = 0 ; k < number_of_elements_in_tree ; k++)
    cout<< tree[k][0] << " "<< tree[k][1]<<endl;

//initializing and finding part L denoted by array tree_l
//Also, with adding each edge of L, graph will find corresponding edges K forming a f-circuit with the corresponding edge of L
int tree_l[co_tree][2];
for(int l = 0 ; l < co_tree ; l++)
{
    tree_l[co_tree][0] = -1;
    tree_l[co_tree][1] = -1;
}
int l_add = 0;

for(int m = 0 ; m < co_tree ; m++)
{
    int copied[number_of_elements_in_tree + 1][2];
    for(int i = 0 ; i < number_of_elements_in_tree ; i++)
    {
        copied[i][0] = tree[i][0];
        copied[i][1] = tree[i][1];
    }
    copied[number_of_elements_in_tree][0] = co_tree_b[m][0];
    copied[number_of_elements_in_tree][1] = co_tree_b[m][1];

    if(loop(copied , number_of_elements_in_tree + 1 , Na + Nb ,Q , tree_a, tree_k ))
    {
        tree_l[l_add][0]=co_tree_b[m][0];
        tree_l[l_add][1]=co_tree_b[m][1];
        l_add++;
    }
}
cout<<endl;

//outputting L
cout<<" L "<< endl;
for(int u = 0 ; u < l_add ; u++)
{
    cout<< tree_l[u][0] << " "<< tree_l[u][1] <<endl;
}
cout<<endl;

//outputting K
cout<<" K "<< endl;
for(int u = 0 ; u < additn ; u++)
{
    cout<< tree_k[u][0] << " "<< tree_k[u][1]<<endl;
}

}


