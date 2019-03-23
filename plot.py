import matplotlib;
import matplotlib.pyplot as plt;

#X, Y = [120,1400,20000,40000], [100,1000,10000,100000];


def qsVmsVhs():
        X = [];
        Y1 = [];
        Y2 = [];
        Y3 = [];

        for line in open('qsVmsVhs.dat', 'r'):
                #print(line);
                values = [float(s) for s in line.split()];

                if(values):
                        Y1.append(values[0]);
                        Y2.append(values[1]);
                        Y3.append(values[2]);
                        X.append(values[3]);
        
        
        #print(Y1);
        #print(Y2);
        #print(Y3);
        #print(X);
        
        plt.figure(figsize=(10,10));
        plt.xlabel('No of items');
        plt.ylabel('Time(s)');
        plt.plot(X,Y1,label="Quicksort");
        plt.plot(X,Y2,label="Mergesort");
        plt.plot(X,Y3,label="Heapsort");

        plt.legend();
        #plt.show();
        plt.savefig('qsVmsVhs.png');


def qsVmsVhsItr():
        #iterative do
        X = [];
        Y1 = [];
        Y2 = [];
        Y3 = [];


        for line in open('qsVmsVhsItr.dat', 'r'):
                values = [float(s) for s in line.split()];

                if(values):
                        #print(Y1);
                        #print(Y2);
                        #print(Y3);
                        #print(X);
                        Y1.append(values[0]);
                        Y2.append(values[1]);
                        Y3.append(values[2]);
                        X.append(values[3]);
        
        #print(X)
        plt.figure(figsize=(10,10));
        plt.xlabel('No of items');
        plt.ylabel('Time(s)');
        plt.plot(X,Y1,label="Quicksort Iterative");
        plt.plot(X,Y2,label="Mergesort Iterative");
        plt.plot(X,Y3,label="Heapsort Iterative");

        plt.legend();
        plt.savefig('qsVmsVhsItr.png');
        def qsVqsItr():q       
######
def msVmsItr():
        X = [];
        Y1 = [];
        Y2 = [];
        Y3 = [];

        for line in open('msVmsItr.dat', 'r'):
                values = [float(s) for s in line.split()];

                if(values):
                        #print(Y1);
                        #print(Y2);
                        #print(Y3);
                        #print(X);
                        Y1.append(values[0]);
                        Y2.append(values[1]);
                        #Y3.append(values[2]);
                        X.append(values[2]);
        
        #print(X)
        plt.figure(figsize=(10,10));
        plt.xlabel('No of items');
        plt.ylabel('Time(s)');
        plt.plot(X,Y1,label="MergeSort");
        plt.plot(X,Y2,label="MergeSort Iterative");

        plt.legend();
        plt.savefig('msVmsItr.png');
         
         
######
def hsVhsItr():
        X = [];
        Y1 = [];
        Y2 = [];
        Y3 = [];

        for line in open('hsVhsItr.dat', 'r'):
                values = [float(s) for s in line.split()];

                if(values):
                        #print(Y1);
                        #print(Y2);
                        #print(Y3);
                        #print(X);
                        Y1.append(values[0]);
                        Y2.append(values[1]);
                        #Y3.append(values[2]);
                        X.append(values[2]);
        
        #print(X)
        plt.figure(figsize=(10,10));
        plt.xlabel('No of items');
        plt.ylabel('Time(s)');
        plt.plot(X,Y1,label="heapSort");
        plt.plot(X,Y2,label="heapSort Iterative");

        plt.legend();
        plt.savefig('hsVhsItr.png');



#############
def qsVqsItr():

        X = [];
        Y1 = [];
        Y2 = [];
        Y3 = [];

        for line in open('qsVqsItr.dat', 'r'):
                values = [float(s) for s in line.split()];

                if(values):
                        #print(Y1);
                        #print(Y2);
                        #print(Y3);
                        #print(X);
                        Y1.append(values[0]);
                        Y2.append(values[1]);
                        #Y3.append(values[2]);
                        X.append(values[2]);
        
        #print(X)
        plt.figure(figsize=(10,10));
        plt.xlabel('No of items');
        plt.ylabel('Time(s)');
        plt.plot(X,Y1,label="MergeSort");
        plt.plot(X,Y2,label="MergeSort Iterative");

        plt.legend();
        plt.savefig('qsVqsItr.png');
         
############################## 4 sort comparison
def fourSortCompPlot():
        X = [];
        Y1 = [];
        Y2 = [];
        Y3 = [];
        Y4 = [];

        for line in open('foursort.dat', 'r'):
                #print(line);
                values = [float(s) for s in line.split()];

                if(values):
                        Y1.append(values[0]);
                        Y2.append(values[1]);
                        Y3.append(values[2]);
                        Y4.append(values[3]);
                        X.append(values[4])

        #print(X)
        plt.figure(figsize=(20,20));
        plt.xlabel('No of items');
        plt.ylabel('Time(s)');
        plt.plot(X,Y1,label="QuickSort");
        plt.plot(X,Y2,label="MergeSort");
        plt.plot(X,Y3,label="HeapSort");
        plt.plot(X,Y4,label="InsertionSort");

        plt.legend();
        #plt.show();
        plt.savefig('foursort.png');


#fourSortCompPlot();
qsVmsVhs();
qsVmsVhsItr();
msVmsItr();
hsVhsItr();
qsVqsItr();
