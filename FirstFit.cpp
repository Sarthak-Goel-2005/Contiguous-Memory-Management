#include<bits/stdc++.h>
using namespace std;

class Node{
public:
    string id;
    int size;
    int loc;
    Node* next;

    Node(string i,int s){
        id=i;
        size=s;
        loc=0;
        next=NULL;
    }
};

Node* head;
int free_size;

void show(){                
    Node* temp=head;
    cout<<endl;
    while(temp!=NULL){
        int end=(temp->loc)+(temp->size);
        if(temp->id=="Free"){
            cout<<"[FREE, Size: "<<temp->size<<", Start: "<<temp->loc<<", End: "<<end<<"] -> ";
        }
        else cout<<"[PID: "<<temp->id<<", Size: "<<temp->size<<", Start: "<<temp->loc<<", End: "<<end<<"] -> ";
        temp=temp->next;
    }
    cout<<"NULL"<<endl<<endl;
}

void Compaction(){
    if(free_size==0){
        cout<<"Memory is full!"<<endl;
        return;
    } 
    Node* temp=head;
    Node* prev=NULL;
    while(temp!=NULL){
        if(temp->id=="Free"){
            if(temp==head){
                head=temp->next;
                delete(temp);
                if(head!=NULL) head->loc=0;
                temp=head;
            }
            else{
                prev->next=temp->next;
                delete(temp);
                temp=prev->next;
            }
        }
        else{
            if(prev==NULL) temp->loc=0;
            else temp->loc=(prev->loc)+(prev->size);
            prev=temp;
            temp=temp->next;
        }
    }
    Node* free= new Node("Free",free_size);
    prev->next=free;
    free->loc=(prev->loc)+(prev->size);
    free->next=NULL;
    show();
    cout<<"Compaction done successfully!"<<endl;
}

void first_fit(string id,int size){
    if(size>free_size){
            cout<<"Not enough space!"<<endl;
            return;
    }
    Node* temp=new Node(id,size);
    if(head->id=="Free" && (head->size)>=(temp->size)){
        temp->next=head;                        //Inserting node at beginning of Linked List!
        head->size=head->size-temp->size;
        head->loc=temp->size;
        if(head->size==0){
            temp->next=head->next;
            delete(head);
        }
        head=temp;
        temp->loc=0;
        show();
        cout<<"Memory allocated to PID: "<<id<<" successfully!"<<endl;
        free_size-=temp->size;
    }
    else{
        Node* curr=head;
        Node* prev=NULL;
        while(curr!=NULL && (curr->id!="Free" || (curr->size)<(temp->size))){
            prev=curr;
            curr=curr->next;
        }
        if(curr==NULL){
            cout<<"Need to do Compaction!"<<endl;
        }
        else{                                  //Inserting node between two nodes of Linked List!
            prev->next=temp;
            temp->next=curr;
            temp->loc=curr->loc;
            curr->size=(curr->size)-(temp->size);
            curr->loc=(temp->loc)+(temp->size);
            if(curr->size==0){
                temp->next=curr->next;
                delete(curr);
            }
            show();
            cout<<"Memory allocated to PID: "<<id<<" successfully!"<<endl;
            free_size-=size;
        }
    }
}

void Deallocate(string id){
    Node* temp=head;
    Node* prev=NULL;
    while(temp->id!=id && temp){
        prev=temp;
        temp=temp->next;
    }
    if(temp==NULL){
        cout<<"No such Program exists!"<<endl;
    }
    else{
        temp->id="Free";
        free_size+=temp->size;
        if(temp->next!=NULL && temp->next->id=="Free"){          //Combining curr and next free memory!
            temp->size=(temp->size)+(temp->next->size);
            Node* FREE=temp->next;
            temp->next=FREE->next;
            delete(FREE);
        }
        if(prev!=NULL && prev->id=="Free"){          //Combining prev and curr free memory!
            prev->size=(prev->size)+(temp->size);
            prev->next=temp->next;
            delete(temp);
        }
        show();
        cout<<"Memory deallocated successfully!"<<endl;
    }
}

int main(){
    free_size=500;
    head=new Node("Free",free_size);
    head->loc=0;
    head->next=NULL;
    cout<<"-------------------------------------------"<<endl;
    cout<<"Max Size: 500"<<endl;
    while(true){
        cout<<"-------------------------------------------"<<endl;
        cout<<"What do you want to do?"<<endl;
        cout<<"1) First fit \n2) Deallocate Memory \n3) Compaction \n4) Display Memory \n5) Exit\n";
        string choice;
        cout<<"Enter your choice: ";
        cin>>choice;
        if(choice=="1"){
            string id;
            int size;
            cout<<"Enter Program ID: ";
            cin>>id;
            cout<<"Enter size: ";
            cin>>size;
            first_fit(id,size);
        }
        else if(choice=="2"){
            string id;
            cout<<"Enter Program ID: ";
            cin>>id;
            Deallocate(id);
        }
        else if(choice=="3"){
            Compaction();
        }
        else if(choice=="4"){
            show();
        }
        else if(choice=="5"){
            break;
        }
        else{
            cout<<"Invalid Input!"<<endl;
        }
    }
    cout<<"-------------------------------------------";
    return 0;
}
