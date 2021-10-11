#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
#include<math.h>

using namespace std;

int sum(vector<vector<int>> vec, int i, int j, int k, int l)
{
    int p, q, result = 0;
    for(p=i;p<=k;p++)
    {
        for(q=j;q<=l;q++)
        {
            result = result + vec[p][q];
        }
    }
    return result;
}

int TaskOne(int m, int n, vector<vector<int>> vec) // task 1
{
    cout<<endl<<"Could Not Implement This Task, Rest All The Tasks Are Fully Functional!!"<<endl;
    return 0;
}

int TaskTwo(int m, int n, vector<vector<int>> vec) // task 2
{
	int i, j;
    int a = -1, b = -1, c = -1, d = -1;
	vector<int> sol(n,0); // initialising the vector with 0
	int Area = 0;
    int diag;
    if(vec[0][0] == 0)
    {
        diag = 0;
    }
    else
    {
        diag = 1;
    }
    for(i=0;i<m;i++)
    {
        for(j=0;j<n;j++)
        {
            int temp = sol[j];
            if(i == 0 || j == 0) // base condition
            {
                if(vec[i][j] == 1)
                {
                    sol[j] = 1;
                    if(Area < sol[j])
                    {
                        Area = sol[j];
                        c = i;
                        d = j;
                    }
                }
                else
                {
                    sol[j] = 0;
                }
            }
            else
            {
                if(vec[i][j] == 1)
                {
                    sol[j] = 1 + min(sol[j], min(sol[j-1], diag));
                    if(Area < sol[j])
                    {
                        Area = sol[j];
                        c = i;
                        d = j;
                    }
                }
                else
                {
                    sol[j] = 0;
                }
            }
            if(j == n-1)
            {
                diag = sol[0];
            }
            else
            {
                diag = temp;
            }
        }
    }
    a = c - Area + 1;
    b = d - Area + 1;
    //cout<<Area*Area<<endl;
    cout<<a+1<<" "<<b+1<<" "<<c+1<<" "<<d+1;
    return 0;
}

int TaskThree(int m, int n, vector<vector<int>> vec) // task 3
{
	int left, right, left1, right1;
    int MaxSum = 0;
    int a = -1, b = -1, c = -1, d = -1;
	for(left=0;left<m;left++)
    {
        for(right=0;right<n;right++)
        {
            for(left1=left;left1<m;left1++)
            {
                for(right1=right;right1<n;right1++)
                {
                    int Sum = sum(vec, left, right, left1, right1); // sum function called
                    if((right1 - right + 1)*(left1 - left + 1) == Sum)
                    {
                        if(Sum > MaxSum)
                        {
                            MaxSum = Sum;
                            a = left;
                            b = right;
                            c = left1;
                            d = right1;
                        }
                    }
                }
            }
        }
    }
    //cout<<"Maximum sum/area is:"<<MaxSum<<endl;
    cout<<a+1<<" "<<b+1<<" "<<c+1<<" "<<d+1;
    return 0;
}

int TaskFour(int m, int n, vector<vector<int>> vec) // task 4
{
	vector<vector<int>> dpheight( m+1 , vector<int> (n, 0));
    vector<vector<int>> dpleft( m+1 , vector<int> (n, 0));
    vector<vector<int>> dpright( m+1 , vector<int> (n, n-1));
	int i, j;
    int a = -1, b = -1, c = -1, d = -1;
    for(i=1;i<m+1;i++)
    {
        int leftbound = 0;
        for(j=0;j<n;j++) // height and left operations
        {
            if(vec[i-1][j] == 1)
            {
                dpheight[i][j] = dpheight[i-1][j] + 1;
                dpleft[i][j] = max(leftbound, dpleft[i-1][j]);
            }
            else
            {
                dpheight[i][j] = 0;
                dpleft[i][j] = 0;
                leftbound = j+1;
            }
        }
        int rightbound = n-1;
        for(j=n-1;j>=0;j--) // right operations
        {
            if(vec[i-1][j] == 1)
            {
                dpright[i][j] = min(rightbound, dpright[i-1][j]);
            }
            else
            {
                dpright[i][j] = n-1;
                rightbound = j-1;
            }
        }
    }
    int maxarea = 0, x = 0, y = 0;
    for(i=1;i<m+1;i++) // area operations
    {
        for(j=0;j<n;j++)
        {
           if(vec[i-1][j] == 1)
            {
                int area = (dpright[i][j] - dpleft[i][j] + 1)*(dpheight[i][j]); // calculating area
                if(maxarea < area)
                {
                    maxarea = area;
                    x = i - 1;
                    y = j;
                }
            }
        }
    }
    int temp = maxarea/dpheight[x+1][y];
    a = x - dpheight[x+1][y] + 2;
    b = dpright[x+1][y] + 2 - temp;
    c = x + 1;
    d = dpright[x+1][y] + 1;
    //cout<<maxarea<<endl;
    cout<<a<<" "<<b<<" "<<c<<" "<<d;
    return 0;

}

int TaskFive(int m, int n, vector<vector<int>> vec) // task 5
{
    int a = -1, b = -1, c = -1, d = -1;
    int maxarea = 0, x = 0, y = 0, dpfheight = 0, dpfright = 0;
    vector<int> dpleft(n, 0);
    vector<int> dpright(n, n);
    vector<int> dpheight(n, 0);
    int i, j;
    for(i=0;i<m;i++)
    {
        int leftbound = 0;
        for(j=0;j<n;j++) // height and left operations
        {
            if(vec[i][j] == 1)
            {
                dpheight[j] = dpheight[j] + 1;
                dpleft[j] = max(dpleft[j], leftbound);
            }
            else
            {
                dpheight[j] = 0;
                dpleft[j] = 0;
                leftbound = j + 1;
            }
        }
        int rightbound = n - 1;
        for(j=n-1;j>=0;j--) // right operations
        {
            if(vec[i][j] == 1)
            {
                dpright[j] = min(dpright[j], rightbound);
            }
            else
            {
                dpright[j] = n - 1;
                rightbound = j - 1;
            }
        }
        for(j=0;j<n;j++) // area operations
        {
            if(vec[i][j] == 1)
            {
                int area = (dpright[j] - dpleft[j] + 1)*dpheight[j]; // calculating area
                if(maxarea < area)
                {
                    maxarea = area;
                    x = i;
                    y = j;
                    dpfheight = dpheight[j];
                    dpfright = dpright[j];
                }
            }
        }
    }
    //cout<<maxarea<<endl;
    int temp = maxarea/dpfheight;
    a = x - dpfheight + 2;
    b = dpfright + 2 - temp;
    c = x + 1;
    d = dpfright + 1;
    cout<<a<<" "<<b<<" "<<c<<" "<<d;
    return 0;
}

int main(int argc, char* argv[]) // main function
{
	int m, n, h;
	int part = stoi(argv[1]);
	ifstream indata(argv[2]);
    // int part = 4;
	// ifstream indata("C:/Users/Parth Gupta/Desktop/AoA/1000x1000");
	indata >> m >> n >> h; // reading from file
	vector<vector<int>> vec( m , vector<int> (n));
    int i, j;
    for(i=0;i<m;i++)
    {
        for(j=0;j<n;j++)
        {
            indata>>vec[i][j]; // reading from file
        }
    }
	indata.close();
    for(i=0;i<m;i++) // converting the given input to 0/1 on the basis of h
    {
        for(j=0;j<n;j++)
        {
            if(vec[i][j] >= h)
            {
                vec[i][j] = 1;
            }
            else
            {
                vec[i][j] = 0;
            }
        }
    }
	switch (part)
	{
		case 1:	TaskOne(m, n, vec);
			break;
		case 2: TaskTwo(m, n, vec);
			break;
		case 3: TaskThree(m, n, vec);
			break;
		case 4: TaskFour(m, n, vec);
			break;
		case 5: TaskFive(m, n, vec);
			break;
		default: cout<<"Invalid Command Line Argument!!"<<endl;
			break;
	}
    return 0;
}
