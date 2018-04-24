#include <bits/stdc++.h>

using namespace std;

string NYTcode="",charCode="";
int op,m,r,e,flag=-1;
string charset,seq,encodedAns;
char decPresent;
map<char,int> frq;



/// Function for making binary code of num k in (e) bits
string getBinary(int k, int e){
    string code;
    while(e--){
        code+=(k%2)?"1":"0";
        k/=2;
    }
    reverse(code.begin(), code.end());
    return code;
}
/// Node Class
class Node{

    public:
        Node* left=NULL;
        Node* right=NULL;
        int weight=0;
        char name='N';

};
/// Haffman Tree Class
class hafTree{
    public :
    Node* root;

    ///class Constructor
    hafTree(){
        Node *nyt=new Node;
        nyt->name='N';
        root=nyt;
    }
    ///Function that calculated the NYT code
    void getNYT(Node* cur,string code){
        // cout << cur->name <<", ";
        if(cur->left==NULL){
                if(cur->name=='N'){
                    NYTcode=code;
                }
                return;
        }
        getNYT(cur->left, code+"0");
        getNYT(cur->right, code+"1");
        return;
    }

    ///Function that calculated the Character code
    void getCharCode(Node* cur,string code,char ch){
        //cout << cur->name <<", ";
        if(cur->left==NULL){
                if(cur->name==ch){
                    charCode=code;

                }

                return;
        }
        getCharCode(cur->left, code+"0", ch);
        getCharCode(cur->right, code+"1", ch);
     //   cout<<endl<<"ahmed ";
        return;
    }
    ///Function that Check the code have been come before or not in (DECODING)
    void checkCode(Node* cur,string codeCheck,string code){

        //cout << cur->name <<", ";
        if(cur->left==NULL){
                if(cur->name!='N' && codeCheck==code){
                    //cout<<endl<<cur->name<<" "<<code<<endl;
                    decPresent=cur->name;
                    flag = 1;///Flag that it's code of Char

                }else if(cur->name == 'N' && codeCheck==code){
                     flag = 2;///flag that it's code of NYT
                }

                return;
        }
        checkCode(cur->left,codeCheck, code+"0");
        checkCode(cur->right,codeCheck, code+"1");

        return;
    }

    ///Function that Displays the tree
    void display(Node* node){
        if(node->left == NULL){
            cout <<"\n"<< node->weight << "  " << node->name;
            return;
        }
        display(node->left);
        cout <<"\n"<< node->weight << "  " << node->name;
        display(node->right);

    }

    ///Function that Insert a node then update the tree weight also balance the tree if needed
    void insertNode(Node* &node, char data, int ind){
     //   cout << node->name << ", ";
        if(node->name == 'N'){
       //     cout <<"create node nyt:" << NYTcode << endl;
            node->name = 'L';

            Node* newNode = new Node;
            newNode->name = data;
            newNode->weight = 1;
            newNode->left = NULL;
            newNode->right = NULL;

            Node* newNYT = new Node;
            newNYT->name = 'N';
            newNYT->weight = 0;
            newNYT->left = NULL;
            newNYT->right = NULL;


            node->left = newNYT;
            node->right = newNode;
            node->weight = 1;
           // display(root);
            return;
        }

        node->weight++;
        if(NYTcode[ind]=='0'){
            insertNode(node->left, data, ind+1);
        }else if(NYTcode[ind] == '1'){
            insertNode(node->right, data, ind+1);
        }

        ///balance the tree if needed
        if(node->left->weight > node->right->weight){
            Node* temp=node->left;
            node->left = node->right;
            node->right = temp;
        }

    }
    ///Function that Updates the tree & also balance it if needed
    void updateTree(Node* &node, int ind){
        if(ind == charCode.size()){
                node->weight++;
                return;
        }
        if(charCode[ind]=='0'){
            updateTree(node->left, ind+1);
        }else if(charCode[ind] == '1'){
            updateTree(node->right, ind+1);
        }

        node->weight++;

        if(node->left->weight > node->right->weight){
            Node* temp=node->left;
            node->left = node->right;
            node->right = temp;
        }
    }
};

///change the string binary code to a number again for decoding
int getNewCode(string str){
    reverse(str.begin(), str.end());
    int temp=0;
    for(int i=0;i<str.size();i++){
        if(str[i]=='1'){
            temp += pow(2,i);
        }
    }
    return temp;
}

///return the character from the charSet
char findChar(int curCode){
    for(int i=0;i<charset.size();i++){
        if(i==curCode)return charset[i];
    }
}

int main()
{
    // freopen("in.txt", "r", stdin);
    // freopen("out.txt", "w", stdout);
    hafTree tree;

    cout<<"press --> 1 for encode Haffman sequence \n press --> 2 for decode Haffman Code :  ";
    cin>>op;
    if(op==1){

                    ///encoding Code here ^_^

        cout<<"Please input the character set that you will use for encoding :"<<endl;
        cin>>charset;
        cout<<"Please input the sequence you want to encode it :"<<endl;
        cin>>seq;
        cout << "\n answer of encoding : \n";
        m=charset.size();
        e=log2(m);
        r=m-pow(2,e);


      for(int i=0;i<seq.size();i++){

            cout<<endl<<seq[i]<<endl;
           // tree.display(tree.root);

           if(frq[seq[i]]){
            //    cout << "hiiiiiiiiiii\n\n";
                tree.getCharCode(tree.root,"",seq[i]);
                cout<<"charCode : "<<charCode<<endl;
                tree.updateTree(tree.root,0);
             //   tree.display(tree.root);
           }else{
                frq[seq[i]]=1;
                //cout << seq[i] << "\ngetting NYT: " << " ";
                tree.getNYT(tree.root,"");
                //cout <<"NYT CODE " << NYTcode << " ";

                int k;
                for(int j=0; j<charset.size(); ++j){
                    if(charset[j]==seq[i]){
                        k = j;
                        break;
                    }
                }
                if(k<2*r){
                    cout <<"NYT CODE + " <<"Binary code : "<< NYTcode << " "<< getBinary(k, e+1);
                }else{
                    cout <<"NYT CODE + " <<"Binary code : "<< NYTcode << " "<< getBinary(k-r, e);
                }
                //cout << "\nbefor insert: ";
                tree.insertNode(tree.root, seq[i], 0);
               // tree.display(tree.root);
           }

           cout << endl;
      }

    }else{
    ///  Decoding Code for HaffMan

        cout<<"Please input the character set that you will use for decoding :"<<endl;
        cin>>charset;
        cout<<"Please input the character code that you want to decode it :"<<endl;
        cin>>seq;

        cout<<"\nThe Result of decoding :"<<endl;
       m=charset.size();
       e=log2(m);
       r=m-pow(2,e);


       int indx=0,curCode,en=1;
       char ch;


                curCode = getNewCode(seq.substr(indx,e));
                //cout<<curCode<<endl;
                if(curCode<r){
                    curCode = getNewCode(seq.substr(indx,e+1));
                    indx+=e+1;
                    ch = findChar(curCode);
                    tree.getNYT(tree.root,"");
                    tree.insertNode(tree.root,ch,0);
                //    cout<<curCode<<endl;
                    cout<< ch <<" ";
                }else{
                    indx+=e;
                    ch = findChar(curCode+r);
                    tree.getNYT(tree.root,"");
                    tree.insertNode(tree.root,ch,0);
              //      cout<<curCode<<endl;
                 cout<< ch <<" ";
                }


        while(indx < seq.size()){
            en=1;
            flag=-1;

            while(flag == -1){
                tree.checkCode(tree.root,seq.substr(indx,en),"");
                en++;
            }
            //cout<<indx<<" "<<en<<endl;

            if(flag==1){
                cout<<endl;
                indx+=en-1;
                ch = decPresent;

                tree.getCharCode(tree.root,"",ch);
                tree.updateTree(tree.root,0);

                cout<< ch <<" ";
                //cout<<indx<<" "<<en<<" "<<curCode<<endl;



            }else if(flag==2){
                cout<<endl;
                indx+=en;
                indx--;
                curCode = getNewCode(seq.substr(indx,e));
                //cout<<indx<<" "<<en<<" "<<curCode<<endl;

                if(curCode<r){
                    curCode = getNewCode(seq.substr(indx,e+1));
                    indx+=e+1;
                    ch = findChar(curCode);
                    tree.getNYT(tree.root,"");
                    tree.insertNode(tree.root,ch,0);
                    cout<<ch <<" ";
                  /*  cout<<endl;
                    tree.display(tree.root);
                    cout<<endl;
                */
                }else{
                    indx+=e;
                    ch = findChar(curCode+r);
                    tree.getNYT(tree.root,"");
                    tree.insertNode(tree.root,ch,0);
                    cout<< ch <<" ";
                /*    cout<<endl;
                    tree.display(tree.root);
                    cout<<endl;
                    */
                }

            }
            /*else{
                cout<<endl;
                curCode = getNewCode(seq.substr(indx,e));
               // cout<<curCode<<endl;
                if(curCode<r){
                    curCode = getNewCode(seq.substr(indx,e+1));
                    indx+=e+1;
                    ch = findChar(curCode);
                    tree.getNYT(tree.root,"");
                    tree.insertNode(tree.root,ch,0);
                 //   cout<<curCode<<endl;
                    cout<< ch <<" ";
                }else{
                    indx+=e;
                    ch = findChar(curCode+r);
                    tree.getNYT(tree.root,"");
                    tree.insertNode(tree.root,ch,0);
                   // cout<<curCode<<endl;
                    cout<< ch <<" ";
                }
            }*/
        }

    }

    cout<<endl<<endl;
    cout<<"The Final tree is : ";
    tree.display(tree.root);
    cout<<endl;
    return 0;
}
