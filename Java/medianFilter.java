import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.PrintStream;
import java.util.Scanner;

public class medianFilter {
    int numRows;
    int numCols;
    int minVal;
    int maxVal;
    int newMin = 9999;
    int newMax = 0;
    int[][] mirrorFramedAry;
    int[][] tempAry;
    int[] neighborAry;
    int[][] mirrorFramed;
    int[][] img;
    int[] histogramAry;
    
    medianFilter(){} //constructor
    
    medianFilter(int n, int c, int min, int max){
        numRows = n;
        numCols = c;
        minVal = min;
        maxVal = max;
        
        mirrorFramedAry = new int[numRows+2][numCols+2];
        
        tempAry = new int[numRows+2][numCols+2];
        
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
    
    
    void readImage(String path) throws FileNotFoundException{
        int data;
        
        FileReader file = new FileReader(path);
        Scanner inFile = new Scanner(file);
		
		numRows = inFile.nextInt();
		System.out.println("numRows: " + numRows);
		numCols = inFile.nextInt();
		System.out.println("numCols: " + numCols);
		minVal = inFile.nextInt();
		System.out.println("minVal: " + minVal);
		maxVal = inFile.nextInt();
		System.out.println("maxVal: " + maxVal);
        
        histogramAry = new int[maxVal+1];
        for(int i=0; i<maxVal+1; i++){
            histogramAry[i] = 0;
        }//for i
        
        medianFilter MF = new medianFilter(numRows, numCols, minVal, maxVal);
        
        mirrorFramedAry = new int[numRows+2][numCols+2];
        
        tempAry = new int[numRows+2][numCols+2];
        
        mirrorFramed = new int[numRows+2][numCols+2];
        
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
    
    void loadImage(String path) throws FileNotFoundException{
        FileReader file = new FileReader(path);
        Scanner inFile = new Scanner(file);
        int data;
            for(int i=1; i<=numRows; i++){
                for(int j=1; j<=numCols; j++){
                    while(inFile.hasNextInt()){
                        data = inFile.nextInt();
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
    
    void printAry(PrintStream outFile1){
        for(int i=1; i<=maxVal;i++){
            if(histogramAry[i] >= 80){
                outFile1.println("(" + i + "):" + "80 +'s");
            }//if
            else{
                outFile1.print("(" + i + "):" + histogramAry[i] + " ");
                for(int count=0; count<histogramAry[i]; count++){
                    outFile1.print("+");
                }//for
                outFile1.println();
            }//else
        }//for
    }//printAry
    
    void computeThreshold(int threshold){
        System.out.print(numRows + " " + numCols + " " + minVal + " " + maxVal);
        for(int i=0; i<numRows; i++){
            System.out.println();
            for(int j=0; j<numCols; j++){
                if(mirrorFramedAry[i][j] < threshold){
                    mirrorFramedAry[i][j]=0;
                    System.out.print("0");
                }//if
                else{
                    mirrorFramedAry[i][j]=1;
                    System.out.print("1");
                }//else
            }//for j
        }//for i
        System.out.println();
    }//computeThreshold
    
    void mirrorFrame(PrintStream outFile){
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
    
    void getMedian(PrintStream outFile){
        for(int i=1; i<numRows+1; i++){
            for(int j=1; j<numCols+1; j++){
                int med = loadNeighbors(i,j);
                mirrorFramed[i][j] = med;
            }//for j
        }//for i
    }//getMedian
    
    void printMedian(PrintStream outFile){
        outFile.println(numRows + " " + numCols + " " + newMin + " " + newMax);
        for(int i=1; i<numRows+1; i++){
            outFile.println();
            for(int j=1; j<numCols+1; j++){
                outFile.print(mirrorFramed[i][j] + " ");
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
        
        neighborAry = new int[9];
        for(int w=0; w<9; w++){
        	neighborAry[0] = a;
        	neighborAry[1] = b;
        	neighborAry[2] = c;
        	neighborAry[3] = d;
        	neighborAry[4] = x;
        	neighborAry[5] = f;
        	neighborAry[6] = g;
        	neighborAry[7] = h;
        	neighborAry[8] = k;
        }//for w
        selectionSort(neighborAry, 9);
        
        tempAry[i][j] = neighborAry[4];
        
        for(int z=0; z<numRows+2; z++){
            for(int y=0; y<numCols+2; y++){
                tempAry[z][y] = neighborAry[4];
                    if (tempAry[z][y] > newMax){
                        newMax = tempAry[z][y];
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
}//class
