#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;
class threshold{
private:
public:
    int numRows;
    int numCols;
    int minVal;
    int maxVal;
    int* thr_ary;
    int** img;
    
    threshold(int maxVal, int numRows, int numCols){
        thr_ary = new int[maxVal];
        for(int i=0; i<maxVal; i++){
            thr_ary[i] = 0;
        }//for
        
        img = new int*[numRows];
        for(int i=0; i<numRows; i++){
            img[i] = new int[numCols];
        }//for i
        
        for(int i=0; i<numRows; i++){
            for(int j=0; j<numCols; j++){
                img[i][j] = 0;
            }//for j
        }//for i
    }//constructor
    
    void computeThreshold(ofstream& outFile2, int data, int value, int numRows, int numCols){
        if(data < value){
            img[numRows][numCols] = 0;
        }//if
        else{
            img[numRows][numCols] = 1;
        }//else
    }//computeThreshold
    
    void printThreshold(ofstream& outFile2, int numRows, int numCols){
        for(int i=0; i<numRows; i++){
            for(int j=0; j<numCols; j++){
                outFile2 << img[i][j];
            }//for j
            outFile2 << "\n";
        }//for i
    }//printThreshold
    
    void prettyPrint(ofstream& outFile2, int numRows, int numCols, int minVal, int maxVal){
        outFile2 << numRows << " " << numCols << " " << minVal << " " << maxVal;
        for(int i=0; i<numRows; i++){
            outFile2 << "\n";
            for(int j=0; j<numCols; j++){
                if(img[i][j] <= 0){
                    outFile2 << " ";
                }//if
                else{
                    outFile2 << img[i][j] << " ";
                }//else
            }//for j
        }//for i
        outFile2.close();
    }//prettyPrint
};

class histogram{
private:
public:
    int* histogramAry;
    int numRows;
    int numCols;
    int minVal;
    int maxVal;
    
    histogram(int maxVal){
        histogramAry = new int[maxVal];
        for(int i=0; i<maxVal; i++){
            histogramAry[i] = 0;
        }//for
    }//constructor
    
    void computeHistogram(int data){
        histogramAry[data]++;
    }//computeHistogram
    
    void printAry(ofstream& outFile, int maxVal){
        for(int i=1; i<=maxVal;i++){
            if(histogramAry[i] >= 80){
                outFile << "(" << i << "):" << "80 +'s" << "\n";
            }//if
            else{
                outFile << "(" << i << "):" << histogramAry[i] << " ";
                for(int count=0; count<histogramAry[i]; count++){
                    outFile << "+";
                }//for
                outFile << "\n";
            }//else
        }//for
    }//printAry
};

class medianFilter{
private:
public:
    int numRows;
    int numCols;
    int minVal;
    int maxVal;
    int newMin = 9999;
    int newMax = 0;
    int** mirrorFramedAry;
    int** tempAry;
    int* neighborAry;
    int** mirrorFramed;
    int** img;
    int* histogramAry;
    
    medianFilter(){} //constructor
    
    medianFilter(int n, int c, int min, int max){
        numRows = n;
        numCols = c;
        minVal = min;
        maxVal = max;
        
        mirrorFramedAry = new int*[numRows+2];
        for(int i=0; i<numRows+2; i++){
            mirrorFramedAry[i] = new int[numCols+2];
        }//for i
        
        tempAry = new int*[numRows+2];
        for(int i=0; i<numRows+2; i++){
            tempAry[i] = new int[numCols+2];
        }//for i
        
        for(int i=0; i<numRows+2; i++){
            for(int j=0; j<numCols+2; j++){
                mirrorFramedAry[i][j] = 0;
                tempAry[i][j] = 0;
            }//for j
        }//for i
        
        neighborAry = new int[9];
        for(int i=0; i<9; i++){
            neighborAry[i] = 0;
        }//for i
    }//constructor
    
    
    void readImage(ifstream& inFile){
        int data;
        inFile >> data;
        numRows = data;
        cout << "numRows: " << data << "\n";
        inFile >> data;
        numCols = data;
        cout << "numCols: " << data << "\n";
        inFile >> data;
        minVal = data;
        cout << "minVal: " << data << "\n";
        inFile >> data;
        maxVal = data;
        cout << "maxVal: " << data << "\n";
        
        histogramAry = new int[maxVal+1];
        for(int i=0; i<maxVal+1; i++){
            histogramAry[i] = 0;
        }//for i
        
        medianFilter MF(numRows, numCols, minVal, maxVal);
        
        mirrorFramedAry = new int*[numRows+2];
        for(int i=0; i<numRows+2; i++){
            mirrorFramedAry[i] = new int[numCols+2];
        }//for i
        
        tempAry = new int*[numRows+2];
        for(int i=0; i<numRows+2; i++){
            tempAry[i] = new int[numCols+2];
        }//for i
        
        mirrorFramed = new int*[numRows+2];
        for(int i=0; i<numRows+2; i++){
            mirrorFramed[i] = new int[numCols+2];
        }//for i
        
        for(int i=0; i<numRows+2; i++){
            for(int j=0; j<numCols+2; j++){
                mirrorFramedAry[i][j] = 0;
                tempAry[i][j] = 0;
                mirrorFramed[i][j] =0;
            }//for j
        }//for i
        
        neighborAry = new int[9];
        for(int i=0; i<9; i++){
            neighborAry[i] = 0;
        }//for i
    }//readImage
    
    void loadImage(ifstream& inFile){
        int data;
            for(int i=1; i<=numRows; i++){
                for(int j=1; j<=numCols; j++){
                    while(!inFile.eof()){
                        inFile >> data;
                        mirrorFramedAry[i][j] = data;
                        computeHistogram(data);
                        break;
                    }//while
                }//for j
            }//for i
        inFile.close();
    }//loadImage
    
    void computeHistogram(int data){
        histogramAry[data]++;
        //cout << data << " ";
    }//computeHistogram
    
    void printAry(ofstream& outFile1){
        for(int i=1; i<=maxVal;i++){
            if(histogramAry[i] >= 80){
                outFile1 << "(" << i << "):" << "80 +'s" << "\n";
            }//if
            else{
                outFile1 << "(" << i << "):" << histogramAry[i] << " ";
                for(int count=0; count<histogramAry[i]; count++){
                    outFile1 << "+";
                }//for
                outFile1 << "\n";
            }//else
        }//for
    }//printAry
    
    void computeThreshold(int threshold){
        cout << numRows << " " << numCols << " " << minVal << " " << maxVal;
        for(int i=0; i<numRows; i++){
            cout << "\n";
            for(int j=0; j<numCols; j++){
                if(mirrorFramedAry[i][j] < threshold){
                    mirrorFramedAry[i][j]=0;
                    cout << "0";
                }//if
                else{
                    mirrorFramedAry[i][j]=1;
                    cout << "1";
                }//else
            }//for j
        }//for i
        cout << "\n";
    }//computeThreshold
    
    void mirrorFrame(ofstream& outFile){
        for(int k=0; k<=numRows+1; k++){
            mirrorFramed[k][0] = mirrorFramedAry[k][1];
            mirrorFramed[k][numCols+1] = mirrorFramedAry[k][numCols];
        }//copy columns to frame
        
        for(int l=0; l<=numCols+1; l++){
            mirrorFramed[0][l] = mirrorFramedAry[1][l];
            mirrorFramed[numRows+1][l] = mirrorFramedAry[numRows][l];
        }//copy rows to frame
        
        for(int i=1; i<numRows+1; i++){
            for(int j=1; j<numCols+1; j++){
                mirrorFramed[i][j] = mirrorFramedAry[i][j];
            }//for j
        }//for i
    }//copyToFrame
    
    void getMedian(ofstream& outFile){
        for(int i=1; i<numRows+1; i++){
            for(int j=1; j<numCols+1; j++){
                int med = loadNeighbors(i,j);
                mirrorFramed[i][j] = med;
            }//for j
        }//for i
    }//getMedian
    
    void printMedian(ofstream& outFile){
        outFile << numRows << " " << numCols << " " << newMin << " " << newMax << "\n";
        for(int i=1; i<numRows+1; i++){
            outFile << "\n";
            for(int j=1; j<numCols+1; j++){
                outFile << mirrorFramed[i][j] << " ";
            }//for j
            //outFile << "\n";
       }//for i
        outFile.close();
    }//printMedian
    
    int loadNeighbors(int i, int j){
        int a,b,c,d,x,f,g,h,k;
        
        a = mirrorFramedAry[i-1][j-1];
        b = mirrorFramedAry[i-1][j];
        c = mirrorFramedAry[i-1][j+1];
        d = mirrorFramedAry[i][j-1];
        x = mirrorFramedAry[i][j];
        f = mirrorFramedAry[i][j+1];
        g = mirrorFramedAry[i+1][j-1];
        h = mirrorFramedAry[i+1][j];
        k = mirrorFramedAry[i+1][j+1];

        int neighborAry[9] = {a,b,c,d,x,f,g,h,k};
        selectionSort(neighborAry, 9);
        
        tempAry[i][j] = neighborAry[4];
        
        for(int i=0; i<numRows+2; i++){
            for(int j=0; j<numCols+2; j++){
                tempAry[i][j] = neighborAry[4];
                    if (tempAry[i][j] > newMax){
                        newMax = tempAry[i][j];
                    }//if
                    if (tempAry[i][j] < newMin){
                        newMin = tempAry[i][j];
                    }//if
            }//for j
        }//for i

        return neighborAry[4];
    }//computeNeighbor
    
    void selectionSort(int neighborAry[], int size){
        int min, temp;
        for(int i=0; i<size-1; i++){
            min = i;
            for(int j=1+1; j<size; j++){
                if(neighborAry[j] < neighborAry[min]){
                    min = j;
                }//if
            }//for j
            if(min != i){
                temp = neighborAry[i];
                neighborAry[i] = neighborAry[min];
                neighborAry[min] = temp;
            }//if
        }//for i
    }//selectionSort
    
};//class

int main(int argc, const char * argv[]) {
    ifstream inFile;
    ofstream outFile;
    
    inFile.open(argv[1]);
    outFile.open(argv[2]);
    
    medianFilter MF;
    
    MF.readImage(inFile); //read header
    MF.loadImage(inFile); //load image into mirrorFramedAry
    MF.mirrorFrame(outFile); //copy values to the frame
    MF.getMedian(outFile); //get median
    MF.printMedian(outFile);
    cout << "\n";
    
    ifstream inFile1;
    ofstream outFile1;
    ofstream outFile2;

    inFile.open(argv[2]);
    outFile.open(argv[3]);
    //outFile2.open(argv[4]);
    
    int data;
    int numRows;
    int numCols;
    int minVal;
    int maxVal;
    int** img;
    int thr_value;
    
    inFile >> data;
    numRows = data;
    cout << "numRows: " << data << "\n";
    inFile >> data;
    numCols = data;
    cout << "numCols: " << data << "\n";
    inFile >> data;
    minVal = data;
    cout << "minVal: " << data << "\n";
    inFile >> data;
    maxVal = data;
    cout << "maxVal: " << data << "\n";
    
    histogram myHistogram(maxVal);
    cout << "enter thr_value: ";
    cin >> thr_value;
    
    string array = argv[2];
    int num = thr_value;
    ostringstream convert;
    string substring = array.substr(0,array.rfind("."));
//    cout << substring;
    string result;
    convert << num;
    result = convert.str();
//    cout << result;
    string outName = substring + "_" + result + ".txt";
    outFile2.open(outName);
    
    threshold myThreshold(maxVal,numRows,numCols);
    
    img = new int*[numRows];
    for(int i=0; i<numRows; i++){
        img[i] = new int[numCols];
    }//for i
    
    for(int i=0; i<numRows; i++){
        for(int j=0; j<numCols; j++){
            while(inFile >> data){
                img[i][j] = data;
                myHistogram.computeHistogram(img[i][j]);
                myThreshold.computeThreshold(outFile2, img[i][j], thr_value, i, j);
                break;
            }//while
        }//for j
    }//for i
    myHistogram.printAry(outFile, maxVal);
    //myThreshold.printThreshold(outFile2, numRows, numCols);
    myThreshold.prettyPrint(outFile2, numRows, numCols, minVal, maxVal);
    
    outFile.close();
    
    return 0;
}//main
