// with this algorithm , process are executed in a preemptive way in such a way that all process will have to wait for the process in execution to free the resources 
// in this case which is the first process to arrive in the queue or the waiting list and ready for execution 

#include<iostream>
#include <algorithm>
#include<iomanip>

// we will be making of c++ built in function to write this algorithm with ease 



using namespace std;
struct process_struct
{
  int pid;  
  int at;       //Arrival Time
  int bt;       //CPU Burst time 
  int ct,wt,tat,rt,start_time;   // Completion, waiting, turnaround, response time , start time 
}ps[100];       //Array of structure to store the info of each process.   


// The function below will compare the time of execution of each process and determine which one is the shortest 
bool comparatorAT(struct process_struct a,struct process_struct b)
{
   int x =a.at;
   int y =b.at;
   return x < y;
//    if(x > y)
//      return false;  // Apply sorting
//    return true;   // no sorting
   
} 

// comparing process id
bool comparatorPID(struct process_struct a,struct process_struct b)
{
   int x =a.pid;
   int y =b.pid;
   return x < y;
}
int main()
{
    int n;
    cout<<"Enter total number of processes : ";
    cin>>n;
    float sum_tat=0,sum_wt=0,sum_rt=0;
    int length_cycle,total_idle_time=0;
    float cpu_utilization;
    
    cout << fixed << setprecision(2);
    // keep values to 2 decimal places
    for(int i=0;i<n;i++)
    {
        cout<<"\nEnter Process " <<i<< "Arrival Time : ";
        cin >> ps[i].at;
        ps[i].pid=i;
    }
    
    for(int i=0;i<n;i++)
    {
        cout<<"\nEnter Process " <<i<< "Burst Time : ";
        cin >> ps[i].bt;
    }
    
    //sort
    sort(ps,ps+n, comparatorAT);

    //calculation
    for(int i=0;i<n;i++)
    {
      // if the process is the first process , its start time will be equal to its arrival time  
      // else it will be the maximum value between it arrival time  and and the completion time of it predecessor given that this is a first come first serve algorithm 
      ps[i].start_time = (i==0) ? ps[i].at : max(ps[i].at, ps[i-1].ct);  


      ps[i].ct =  ps[i].start_time + ps[i].bt;

 
      ps[i].tat = ps[i].ct-ps[i].at;       
      ps[i].wt = ps[i].tat-ps[i].bt;
      ps[i].rt=ps[i].wt;
       
      sum_tat += ps[i].tat;
      sum_wt += ps[i].wt;
      sum_rt += ps[i].rt;
      total_idle_time += (i==0) ? 0 : (ps[i].start_time -  ps[i-1].ct);
    }
    length_cycle = ps[n-1].ct - ps[0].start_time;
    //sort so that process ID in output comes in Original order (just for interactivity)
    sort(ps,ps+n, comparatorPID);
    
    //Output
    cout<<"\nProcess No.\tAT\tCPU Burst Time\tCT\tTAT\tWT\tRT\n";
    for(int i=0;i<n;i++)
     cout<<i<<"\t\t"<<ps[i].at<<"\t"<<ps[i].bt<<"\t\t"<<ps[i].ct<<"\t"<<ps[i].tat<<"\t"<<ps[i].wt<<"\t"<<ps[i].rt<<endl;
    cout<<endl;
    
    cpu_utilization = (float)(length_cycle - total_idle_time)/ length_cycle;
    
    cout<<"\nAverage Turn Around time= "<< sum_tat/n;
    cout<<"\nAverage Waiting Time= "<<sum_wt/n;
    cout<<"\nAverage Response Time= "<<sum_rt/n;    
    cout<<"\nThroughput= "<<n/(float)length_cycle;
    cout<<"\nCPU Utilization(Percentage)= " << cpu_utilization*100;
    return 0;
}