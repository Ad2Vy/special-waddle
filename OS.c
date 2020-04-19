#include<stdio.h>
#include<stdlib.h>
typedef struct
{

    int arrival_time,burst_time,queue;
    int process_id;
}process;

int main()
{
    int size,quantum,done =0;//Number of processes
    int count = 0;
    int i,j,k,l,m =0;
    int time,smallest,waiting_time[50],turnaround_time[50],completion[50],temp_burst[50];
    double average_waiting,average_turnaround;
    printf("\nEnter the number of processes:");
    scanf("%d",&size);
    process no[size];
    for(i = 0; i < size; i++)
	{
		printf("\nProcess ID:\t");
		scanf("%d", &no[i].process_id);
		printf("Arrival Time:\t");
		scanf("%d", &no[i].arrival_time);
		printf("Burst Time:\t");
		scanf("%d", &no[i].burst_time);
		printf("Queue1/Queue2(1/2):\t");
		scanf("%d", &no[i].queue);
	}
	printf("\nEnter the time quantum for Round Robin:");
	scanf("%d",&quantum);
    for(j=0;j<size;j++)
    {
        temp_burst[j] = no[j].burst_time;//storing the burst time in a array for  further use.
    }

    no[size+1].burst_time = 999;//  assign a max burst for comparison

    for(time=0;count!=size;time++) // shortest remaining time first scheduling
    {
         smallest = size+1;
         for(k=0;k<size;k++)
         {
            if(no[k].arrival_time<=time && no[k].burst_time<no[smallest].burst_time && no[k].burst_time>0 && no[k].queue == 1)
            {
                smallest=k;
            }
         }

         if(count >= size/2) //round robin scheduling
          {
            while(1)
            {
              for(l=0;l<size;l++)
              {
                  if(no[l].arrival_time<=time && no[l].burst_time > quantum && no[l].queue == 2 )
                  {
                      no[j].burst_time -= quantum;
                      smallest = l;
                  }
                  else if(no[l].arrival_time<=time && no[l].burst_time < quantum && no[l].queue == 2)
                  {
                      no[l].burst_time = 0;
                      smallest = l;
                      goto a;
                  }
              }
            }
          }

        no[smallest].burst_time--; //decrementing  the burst time

        a: if(no[smallest].burst_time == 0)
         {
            count++;
            completion[smallest] = time+1;
            turnaround_time[smallest] = completion[smallest] - no[smallest].arrival_time;
            waiting_time[smallest] = turnaround_time[smallest] - temp_burst[smallest];
         }
    }
    printf("\n\nProcess Id\tArrival Time\t Burst Time\t Waiting Time\tTurnaround Time");
    for(m=0;m<size;m++)
    {
        printf("\n   P%d   \t\t%d\t\t%d  \t\t%d\t\t%d",no[m].process_id,no[m].arrival_time,temp_burst[m],waiting_time[m],turnaround_time[m]);
        average_waiting += waiting_time[m];
        average_turnaround += turnaround_time[m];
    }
    printf("\n\nAverage waiting time = %lf\n",average_waiting/size);
    printf("Average Turnaround time = %lf",average_turnaround/size);

}
