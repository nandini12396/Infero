#include<stdio.h>

int data[1000][1000][9];
int Path[1000][2];
int normal_dirx[4] = {-1,-1,-2,-2};
int normal_diry[4] = {-2,2,-1,1};

int power_dirx[2] = {-2,-2};
int power_diry[2] = {-2,2};

int down_x[4] = {2,2,1,1};
int down_y[4] = {-1,1,-2,2};

int down_xx[2] = {2,2};
int down_yy[2] = {-2,2};

int main()
{
    int T,N,M;
    scanf("%d",&T);
    for(int tc=1;tc<=T;tc++)
    {
        int ti,tj,value,tti,ttj;
        scanf("%d %d",&N,&M);
        for(int i=0;i<N;i++)
        {
            for(int j=0;j<M;j++)
            {
                scanf("%d",&data[i][j][0]);
                data[i][j][1] = data[i][j][2] = data[i][j][3] = 1000000000;
                data[i][j][4] = data[i][j][5] = data[i][j][6] = 0;
            }
        }

        for(int j=0;j<M;j++)
        {
            data[N-1][j][1] = data[N-1][j][0];
        }

        for(int i=N-1;i>=0;i--)
        {
            for(int j=0;j<M;j++)
            {                
                {
                    for(int dir=0;dir<4;dir++)    
                    {
                        ti = i + normal_dirx[dir];
                        tj = j + normal_diry[dir];

                        if(ti>=0&&tj>=0&&ti<N&&tj<M)
                        {
                            value = data[i][j][1] + data[ti][tj][0];
                            if(value <= data[ti][tj][2])
                            {
                                data[ti][tj][2] = value;
                                data[ti][tj][5] = data[i][j][4] +1;
                            }
                        }
                    }
                }

                {
                    for(int dir=0;dir<4;dir++)    
                    {
                        ti = i + normal_dirx[dir];
                        tj = j + normal_diry[dir];

                        if(ti>=0&&tj>=0&&ti<N&&tj<M)
                        {
                            value = data[i][j][2] + data[ti][tj][0];
                            if(value <= data[ti][tj][3])
                            {
                                data[ti][tj][3] = value;
                                data[ti][tj][6] = data[i][j][5] +1;
                            }
                        }
                    }
                }

                {
                    for(int dir=0;dir<4;dir++)    
                    {
                        ti = i + normal_dirx[dir];
                        tj = j + normal_diry[dir];

                        if(ti>=0&&tj>=0&&ti<N&&tj<M)
                        {
                            value = data[i][j][3] + data[ti][tj][0];
                            if(value <= data[ti][tj][3])
                            {
                                data[ti][tj][3] = value;
                                data[ti][tj][6] = data[i][j][6] +1;
                            }
                        }
                    }

                    for(int dir=0;dir<2;dir++)    
                    {
                        ti = i + power_dirx[dir];
                        tj = j + power_diry[dir];

                        if(ti>=0&&tj>=0&&ti<N&&tj<M)
                        {
                            value = data[i][j][3] + data[ti][tj][0];
                            if(value <= data[ti][tj][1])
                            {
                                data[ti][tj][1] = value;
                                data[ti][tj][4] = data[i][j][6] +1;
                            }
                        }
                    }
                }
            }
        }
        int Answer = 1000000000,Jumps=0;
        for(int j=0;j<M;j++)
        {
            if(data[0][j][1] <= Answer)
            {
                Answer = data[0][j][1];
                Jumps = data[0][j][4];
                tj = j;                
            }
            if(data[0][j][2] <= Answer)
            {
                Answer = data[0][j][2];
                Jumps = data[0][j][5];
                tj = j;                
            }
            if(data[0][j][3] <= Answer)
            {
                Answer = data[0][j][3];
                Jumps = data[0][j][6];
                tj = j;                
            }
        }    

        printf("Case #%d\n%d\n%d\n",tc,Answer,Jumps+1);

        int noj = Jumps,ff;
        Path[Jumps][0] = 0;
        Path[Jumps][1] = tj;
        tti = 0;
        ttj = tj;
        while(Jumps)
        {
            ff = 0;
            for(int dir = 0; dir <4 ; dir++)
            {
                ti = tti + down_x[dir];
                tj = ttj + down_y[dir];

                if(ti>=0&&tj>=0&&ti<N&&tj<M)
                {
                    if(Answer == data[ti][tj][1] + data[tti][ttj][0] && Jumps == data[ti][tj][4]+1)
                    {
                        Answer -= data[tti][ttj][0];
                        Jumps--;
                        tti = Path[Jumps][0] = ti;
                        ttj = Path[Jumps][1] = tj;
                        ff = 1;
                        break;
                    }
                    else if(Answer == data[ti][tj][2] + data[tti][ttj][0] && Jumps == data[ti][tj][5]+1)
                    {
                        Answer -= data[tti][ttj][0];
                        Jumps--;
                        tti = Path[Jumps][0] = ti;
                        ttj = Path[Jumps][1] = tj;
                        ff = 1;
                        break;
                    }
                    else if(Answer == data[ti][tj][3] + data[tti][ttj][0] && Jumps == data[ti][tj][6]+1)
                    {
                        Answer -= data[tti][ttj][0];
                        Jumps--;
                        tti = Path[Jumps][0] = ti;
                        ttj = Path[Jumps][1] = tj;
                        ff = 1;
                        break;
                    }
                }
            }
            if(ff!=1)
            for(int dir = 0; dir <2 ; dir++)
            {
                ti = tti + down_xx[dir];
                tj = ttj + down_yy[dir];

                if(ti>=0&&tj>=0&&ti<N&&tj<M)
                {
                    if(Answer == data[ti][tj][3] + data[tti][ttj][0] && Jumps == data[ti][tj][6]+1)
                    {
                        Answer -= data[tti][ttj][0];
                        Jumps--;
                        tti = Path[Jumps][0] = ti;
                        ttj = Path[Jumps][1] = tj;
                        break;
                    }                    
                }
            }
        }

        for(int j=0;j<=noj;j++)
        {
            printf("%d %d ",Path[j][0]+1,Path[j][1]+1);
        }
        printf("\n");

    }
    return 0;
}


