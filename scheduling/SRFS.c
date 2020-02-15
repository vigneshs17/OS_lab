#include<stdio.h>


int isFinish(int finish[], int n_process)
{
    int i;
    for(i=0;i<n_process;i++)
    {
        if(finish[i]==0)
        {
            return 0;
        }
    }

    return 1;
}


int main()
{
    int n_process,i,j,x,f;
    printf("\nEnter no of process: ");
    scanf("%d", &n_process);

    int values[n_process][3];   // values[x][0] = process number, values[x][1] = Arrival Time, values[x][2] = Burst time

    printf("\nEnter Arrival Time and Burst Time\n");
    for(i=0;i<n_process;i++)
    {
        scanf("%d %d", &values[i][1], &values[i][2]);
        values[i][0] = i;
    }

    int finish[n_process];
    for(i=0;i<n_process;i++)
    {
        finish[i] = 0;
    }


    for(i=0;i<n_process;i++)
    {
        for(j=i+1;j<n_process;j++)
        {
            if(values[i][1]>values[j][1])
            {
                x = values[i][1];
                values[i][1] = values[j][1];
                values[j][1] = x;

                x = values[i][0];                           //  Sorting based on Arrival Time
                values[i][0] = values[j][0];
                values[j][0] = x;

                x = values[i][2];
                values[i][2] = values[j][2];
                values[j][2] = x;
            }
        }
    }


    int rmng[n_process];
    for(i=0;i<n_process;i++)
    {
        rmng[values[i][0]] = values[i][2];
    }

    int prs_Seq[10000];
    int tp = -1;
    int min;
    int tmpQue[n_process];
    int tq = -1;
    int time = 0;
    int CntxtSw[10000][3];
    int tc = -1;

    while(!(isFinish(finish, n_process)))
    {
        tq = -1;
        f = 0;
        for(i=0;i<n_process;i++)
        {
            if(!finish[values[i][0]])
            {
                if(values[i][1]<=time)
                {
                    tq++;
                    f = 1;
                    tmpQue[tq] = i;
                }
                else
                {
                    if(!f)
                    {
                        tp++;
                        prs_Seq[tp] = -1;
                    }
                    break;
                }

            }
        }

        if(f)
        {
            min = 100000;
            for(i=0;i<=tq;i++)
            {
                if(rmng[ values[ tmpQue[i] ][0] ] < min)
                {
                    min = rmng[ values[ tmpQue[i] ][0] ];
                    j =  tmpQue[i];
                }
            }


            tp++;
            prs_Seq[tp] = values[j][0] + 1;

            if(tp!=0)
            {
                if(prs_Seq[tp]!=prs_Seq[tp-1])
                {
                    tc++;
                    CntxtSw[tc][0] = prs_Seq[tp-1];
                    CntxtSw[tc][1] = prs_Seq[tp];
                    CntxtSw[tc][2] = time;
                }
            }


            rmng[values[j][0]] = rmng[values[j][0]] - 1;

            if(rmng[values[j][0]]==0)
            {
                finish[values[j][0]] = time+1;
            }
        }

        time++;
    }

    printf("\nProcess Timeline\n");
    for(i=0;i<=tp;i++)
    {
        printf("%d ", prs_Seq[i]);
    }

    printf("\n");

    printf("\nContext Switch\nFrom     To       Time");
    for(i=0;i<=tc;i++)
    {
        printf("\n%d\t%d\t%d", CntxtSw[i][0], CntxtSw[i][1], CntxtSw[i][2]);
    }
    printf("\n");


    int Tat[n_process];
    int WaitTime[n_process];

    printf("\nFinish Time\n");
    for(i=0;i<n_process;i++)
    {
            printf("\n%d", finish[i]);
    }

    for(i=0;i<n_process;i++)
    {
        Tat[values[i][0]] = finish[values[i][0]] - values[i][1];
        WaitTime[values[i][0]] = Tat[values[i][0]] - values[i][2];
    }

    printf("\n\nProcess number  Turn Around Time");
    for(i=0;i<n_process;i++)
    {
        printf("\n%d \t\t %d", i+1, Tat[i]);
    }

    printf("\n\nProcess number  Waiting Time");
    for(i=0;i<n_process;i++)
    {
        printf("\n%d \t\t %d", i+1, WaitTime[i]);
    }


    int IdleTime[10000][2];
    int ti = -1;
    for(i=0;i<=tp;i++)
    {
        if(prs_Seq[i]==-1)
        {
            ti++;
            IdleTime[ti][0] = i;
            j = i+1;
            while(j<=tp && prs_Seq[j]==-1)
            {
                j++;
            }
            IdleTime[ti][1] = j;
            i = j-1;
        }

    }

    printf("\n\nIdle Time\nStart End\n");
    for(i=0;i<=ti;i++)
    {
        printf("%d\t%d\n", IdleTime[i][0], IdleTime[i][1]);
    }

    printf("\n");
}
