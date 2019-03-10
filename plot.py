import matplotlib;
import matplotlib.pyplot as plt;

#X, Y = [120,1400,20000,40000], [100,1000,10000,100000];
X = [];
Y1 = [];
Y2 = [];
Y3 = [];

for line in open('qsVmsVhs.dat', 'r'):
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
plt.figure(figsize=(20,20));
plt.xlabel('No of items');
plt.ylabel('Time(ms)');
plt.plot(X,Y1,label="Quicksort");
plt.plot(X,Y2,label="Mergesort");
plt.plot(X,Y3,label="Heapsort");

plt.legend(bbox_to_anchor=(0., 1.02, 1., 2.102), loc=3, ncol=2, mode="expand", borderaxespad=0.);
#plt.show();
plt.savefig('qsVmsVhs.png');



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
plt.figure(figsize=(20,20));
plt.xlabel('No of items');
plt.ylabel('Time(ms)');
plt.plot(X,Y1,label="Quicksort Iterative");
plt.plot(X,Y2,label="Mergesort Iterative");
plt.plot(X,Y3,label="Heapsort Iterative");

plt.legend(bbox_to_anchor=(0., 1.02, 1., 2.102), loc=3, ncol=2, mode="expand", borderaxespad=0.);
#plt.show();
plt.savefig('qsVmsVhsItr.png');

######### quicksort normal vs itr
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
plt.figure(figsize=(20,20));
plt.xlabel('No of items');
plt.ylabel('Time(ms)');
plt.plot(X,Y1,label="Quicksort");
plt.plot(X,Y2,label="Quicksort Iterative");

plt.legend(bbox_to_anchor=(0., 1.02, 1., 2.102), loc=3, ncol=2, mode="expand", borderaxespad=0.);
#plt.show();
plt.savefig('qsVqsItr.png');
         
######
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
plt.figure(figsize=(20,20));
plt.xlabel('No of items');
plt.ylabel('Time(ms)');
plt.plot(X,Y1,label="MergeSort");
plt.plot(X,Y2,label="MergeSort Iterative");

plt.legend(bbox_to_anchor=(0., 1.02, 1., 2.102), loc=3, ncol=2, mode="expand", borderaxespad=0.);
#plt.show();
plt.savefig('msVmsItr.png');
         
         
######
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
plt.figure(figsize=(20,20));
plt.xlabel('No of items');
plt.ylabel('Time(ms)');
plt.plot(X,Y1,label="heapSort");
plt.plot(X,Y2,label="heapSort Iterative");

plt.legend(bbox_to_anchor=(0., 1.02, 1., 2.102), loc=3, ncol=2, mode="expand", borderaxespad=0.);
#plt.show();
plt.savefig('hsVhsItr.png');
