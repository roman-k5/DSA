#include<iostream>
#include<chrono> // for time
#include<time.h> // for changin seed
#include<cstdlib> // for rng

//declaring the functions beforehand 
void mergesort(int* arr,int size);
void merge(int* arr,int* left,int* right, int leftsize,int rightsize);
int binarySearch(int* arr,int search,int size);
void preety_print(int* arr,int size);
void selectionSort(int* arr,int size);
int interpolationSearch(int* arr,int size,int search);
void reset(int* copy, int* array,int size){
    for(int i=0;i<size;i++){array[i]=copy[i];}
}

using namespace std;
int main(){
    int n,sortedFlag=-1,search,searchOut;
    chrono::time_point<std::chrono::_V2::system_clock, std::chrono::_V2::system_clock::duration> start,end; // variables to store time in low units 
    chrono::duration<double> duration;
    // asks user for array's length
    cout<<"\nEnter the size of array: ";
    cin >>n;
    int array[n];
    // makes sure random numbers are random always by using always changing seed : time(0)= seconds until now from 1970 january
    srand(time(0));
    int negRandomness;
    // also has random amount of negative numbers 
    for(int i=0;i<n;i++){
        negRandomness=(int) rand();
        array[i]=(int)rand();
        if(negRandomness%2!=0){
            array[i]-=(array[i]*2);
        }
        
    }
    // a temporary backup storage to store the initial state to rollback after sorting if you want to sort again 
    int copy[n];
    for(int i=0;i<n;i++){
        copy[i]=array[i];
    }
    
    
    // Main menu with generic switch statements , program jumps to random point in code using 'goto'
    int menuChoice,sortmenuChoice,searchmenuChoice;
    Menu:
    cout<<"\n*******MENU*******"<<endl;
    cout<<"1.Sorting."<<endl;
    cout<<"2.Searching on Sorted Array."<<endl;
    cout<<"3.Print the Array."<<endl;
    cout<<"4.Reset the array."<<endl;
    cout<<"5.Clear Screen"<<endl;
    cout<<"6.Exit."<<endl;
    cout<<"Enter your choice (1-6): ";
    cin>>menuChoice;
    switch (menuChoice)
    {
    case 1 :
        goto SortMenu;

    case 2 :
        goto SearchMenu;
        break;
    
    case 3 :
        preety_print(array,n);
        break;

    case 4 :
        reset(copy,array,n);
        break;

    case 5:
    // clears the terminal for windows type system as "cls" and linux as "clear"(bash,zsh,etc)
        #if __WIN32
            system("cls");
        #else
            system("clear");
        #endif
        break;
    case 6 :
        cout<<"\bBYE!";
        return 0; // program exit point 
    default:
        cout<<"\nInput Out of bounds!!"<<endl;
        break;
    }
    goto Menu; //retry

    // Menu for Sorting choices
    SortMenu:
    cout<<"\n*****Sorting Options******"<<endl;
    cout<<"1.Selection Sort"<<endl;
    cout<<"2.Merge Sort"<<endl;
    cout<<"3.Back"<<endl;
    cout<<"4.Exit"<<endl;
    cout<<"Enter your Choise (1-4): ";
    cin>>sortmenuChoice;
    switch (sortmenuChoice)
    {
    case 1:
    // if program is sorted already, takes it back to its initial state when it was un sorted
        if(sortedFlag==0){
            cout<<"\nArray was already sorted!, Resetting the Array!"<<endl;
            reset(copy,array,n);
            sortedFlag=-1;
        }
        // starts timer, calls sort function , stops timer and calculates the time takes
        start=chrono::high_resolution_clock::now();
        selectionSort(array,n);
        end=chrono::high_resolution_clock::now();
        duration=end-start;
        cout<<"\nTime taken by Selection Sort: "<<duration.count()<<endl;
        sortedFlag=0;
        break;
    
    case 2:
    // Same as case 1 
        if(sortedFlag==0){
            cout<<"\nArray was already sorted!, Resetting the Array!"<<endl;
            reset(copy,array,n);
            sortedFlag=-1;
        }
        start=chrono::high_resolution_clock::now();
        mergesort(array,n);
        end=chrono::high_resolution_clock::now();
        duration=end-start;
        cout<<"\nTime taken by Merge Sort: "<<duration.count()<<endl;
        sortedFlag=0;
        break;

    case 3:
        goto Menu; //main menu

    case 4:
        return 0; // program exit point
    default:
        cout<<"\nInvalid Choice!!. Retry"<<endl;
        break;
    }
    goto SortMenu; // retry

    // Search algorithm choices menu
    SearchMenu:
    cout<<"\n*****Searching Options******"<<endl;
    cout<<"1.Binary Search"<<endl;
    cout<<"2.Interpolation Search"<<endl;
    cout<<"3.Back"<<endl;
    cout<<"4.Exit"<<endl;
    cout<<"Enter your Choise (1-4): ";
    cin>>searchmenuChoice;
    switch (searchmenuChoice)
    {
    case 1:
    // if the array is'nt sorted, sorts it first then only asks for a value to search
        if(sortedFlag!=0){
            cout<<"\nArray isn't sorted!, sorting first!"<<endl;
            mergesort(array,n);
            sortedFlag=0;
        }
        cout<<"\nEnter a value to search: "<<endl;
        cin>>search;
        // starts a timer, runs the algorithm, stops the timer and calculate duration
        start=chrono::high_resolution_clock::now();
        searchOut=binarySearch(array,search,n);
        end=chrono::high_resolution_clock::now();
        duration=end-start;
        // result can be -1 for value not found and >=0 for index value
        if(searchOut<=0){
            cout<<"\nValue Not found!"<<endl;
        }
        else{
            cout<<"\n"<<search<<" is at index "<<searchOut<<endl;
        }
        cout<<"\nTime taken by Binary Search: "<<duration.count()<<endl;
        break;
    
    case 2:
    //same as case 1
        if(sortedFlag!=0){
            cout<<"\nArray isn't sorted!, sorting first!"<<endl;
            mergesort(array,n);
            sortedFlag=0;
        }
        cout<<"\nEnter a value to search: "<<endl;
        cin>>search;
        start=chrono::high_resolution_clock::now();
        searchOut=interpolationSearch(array,n,search);
        end=chrono::high_resolution_clock::now();
        duration=end-start;
        if(searchOut<=0){
            cout<<"\nValue Not found!"<<endl;
        }
        else{
            cout<<"\n"<<search<<" is at index "<<searchOut<<endl;
        }
        cout<<"\nTime taken by Interpolation Search: "<<duration.count()<<endl;
        break;

    case 3:
        goto Menu; //main menu

    case 4:
        return 0; //program exit point
    default:
        cout<<"\nInvalid Choice!!. Retry"<<endl;
        break;
    }
    goto SearchMenu; // retry

    return 0; // main function return , program exit point
}

// function that takes array and prints all of it contents from first to last index i.e. 0-n
void preety_print(int* arr,int size){
    for(int i=0;i<size;i++){
        cout<<"\nElement no "<<i+1<<": "<<arr[i];
    }
    cout<<"\n";
}

// Sorts an array using mergesort algorithm, takes in array and its size
void mergesort(int* arr,int size){
    if (size<2){return;} // return if array has only 1 element or none sincee it is already sorted

    // calculate pointer to the middle of the array as 'mid'
    // allocated memory of mid*sizeof(int) bytes for left and (size-mid)*sizeof(int) as 'left' and 'right' pointer of array for head and tail
    int mid=size/2;
    int* left=new int[mid];
    int* right=new int[size-mid];

    // copies the left side element to newly allocation pointer 'left'
    for(int i=0;i<mid;i++){
        left[i]=arr[i];
    }

    // copies the right side element to newly allocation pointer 'right'
    for(int i=mid;i<size;i++){
        right[i-mid]=arr[i];
    }
    mergesort(left,mid);// recursively calls itself to sort the left side first
    mergesort(right,(size-mid)); // recursively calls itself to sort the right side 

    merge(arr,left,right,mid,size-mid);// merge the left and right side 

    // free the memory 
    delete[] left;
    delete[] right;
}

// function called by mergesort to merge two array
void merge(int* arr,int* left,int* right, int leftsize,int rightsize){
    int i=0,j=0,k=0;

    // loop runs until the left index is lower than left array size and right index is lower than right array size
    // makes sure index is never out of bound 
    while(i<leftsize && j<rightsize){
        if(left[i]<right[j]){ // if left side's value at index 'i' is lower copy the value to main array at index 'k' otherwise copy value of right array's index 'j'  
            arr[k++]=left[i++];
        }
        else{
            arr[k++]=right[j++];
        }
    }
    // copy the leftover values of left array to main array if any
    while(i<leftsize){
        arr[k++]=left[i++];
    }
    // copy the leftover values of right array to main array if any
    while(j<rightsize){
        arr[k++]=right[j++];
    }

}

//function using selection sort algorithm, uses loop
void selectionSort(int* arr,int size){
    int swap;
    // remmebers the increasing pointer of main array pointing to its index from left to right
    // on each increment of main index pointer, loops through the array to find the smallest element
    // swaps the value of that element with element at current index pointer
    for(int left=0;left<size;left++){
        int temp=left;
        for(int i=left;i<size;i++){
            if(arr[i]<arr[temp]){
                temp=i;
            }
        }
        swap=arr[temp];
        arr[temp]=arr[left];
        arr[left]=swap;
    }
}

//function to binary search an element, uses loop
int binarySearch(int* arr,int search,int size){
    // initialize left , right and middle pointer for the array
    int left=0,right=size-1,mid;
    mid=(right/2)+left;
    // loops until the left pointer goes further than mid (to end) or right pointer comes more closer than mid (to start)
    while(left<=mid && right>=mid){
        if(search==arr[mid]){return mid;} // if foundd 
        else if(search<arr[mid]){ // if the element is smaller than the element at current index, cut the right half of the array, else cut the left half
            right=mid-1;
        }
        else{
            left=mid+1;
        }
        mid=((right-left)/2)+left;
    }
    return -1; //if not found
}

// function for interpolation search, uses loop
int interpolationSearch(int* arr,int size,int search){
    int low=0,high=size-1;
    int probe=(high-low)/2+low; // probe is calculated as the guess or estimated value on where an element could be 
    while(search>=arr[low]&&search<=arr[high]&&low<=high){// loops until the value exists in the array and left pointer is smaller or equal than right pointer
        probe=low+(((high-low)*(search-arr[low]))/(arr[high]-arr[low]));
        if(arr[probe]==search){return probe;} // if found
        else if(search<arr[probe]){ // if probe's value is greater than the required value, cut the part between probe to high, else cut the part between low to probe
            high=probe-1;
            continue;
        }
        low=probe+1;
    }
    return -1; // if not found
}