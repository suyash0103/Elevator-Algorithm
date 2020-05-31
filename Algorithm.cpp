#include<bits/stdc++.h>

using namespace std;

int queries;
vector<vector<int > > all_info;
queue<vector<int> > ready;
set<vector<int> > completed;
vector<int> isDest(10, 0);
int currtime = 0;
int currfloor = 0;

//struct comp
//{
//	bool operator()(vector<int> v1, vector<int> v2)
//	{
//		return abs(v1[0] - currtime) < abs(v2[0] - currtime);
//	}
//};

//struct comp
//{
//	bool operator()(vector<int> v1, vector<int> v2)
//	{
//		return abs(v1[1] - currfloor) < abs(v2[1] - currfloor);
//	}
//};

void stay(int floor)
{
	cout << "Staying still at floor " << floor << endl;
}

void open(int floor)
{
	cout << "Opened door at " << floor << " floor" << endl;
}

void close(int floor)
{
	cout << "Closed door at " << floor << " floor" << endl;
}

void move(int startfl, int endfl, int &time)
{
	if(endfl > startfl)
	{
		while(startfl < endfl)
		{
			if(isDest[startfl] == 1)
			{
				open(startfl);
				time++;
				close(startfl);
				time++;
				isDest[startfl] = 0;
			}
			for(int i = 0; i < queries; i++)
			{
				if(completed.find(all_info[i]) == completed.end() && all_info[i][1] == startfl)
				{
					if(time >= all_info[i][0] && all_info[i][2] > all_info[i][1])
					{
						ready.push(all_info[i]);
						completed.insert(all_info[i]);
						isDest[all_info[i][2]] = 1;
						open(startfl);
						time++;
						close(startfl);
						time++;
						break;	
					}
				}
			}
			isDest[startfl] = 0;
			cout << "Moved from " << startfl << " to " << startfl + 1 << endl;
			startfl++;
			time++;
		}
		if(isDest[endfl] == 1)
		{
			open(endfl);
			time++;
			close(endfl);
			time++;
			isDest[endfl] = 0;
		}
		for(int i = 0; i < queries; i++)
		{
			if(completed.find(all_info[i]) == completed.end() && all_info[i][1] == endfl)
			{
				if(time >= all_info[i][0] && all_info[i][2] > all_info[i][1])
				{
					ready.push(all_info[i]);
					completed.insert(all_info[i]);
					isDest[all_info[i][2]] = 1;
					open(endfl);
					time++;
					close(endfl);
					time++;
					break;
				}
			}
		}
	}
	else
	{
		while(startfl > endfl)
		{
			if(isDest[startfl] == 1)
			{
				open(startfl);
				time++;
				close(startfl);
				time++;
				isDest[startfl] = 0;
			}
			for(int i = 0; i < queries; i++)
			{
				if(completed.find(all_info[i]) == completed.end() && all_info[i][1] == startfl)
				{
					if(time >= all_info[i][0] && all_info[i][2] < all_info[i][1])
					{
						ready.push(all_info[i]);
						completed.insert(all_info[i]);
						isDest[all_info[i][2]] = 1;
						open(startfl);
						time++;
						close(startfl);
						time++;
						break;
					}
				}
			}
			isDest[startfl] = 0;
			cout << "Moved from " << startfl << " to " << startfl - 1 << endl;
			startfl--;
			time++;
		}
		if(isDest[endfl] == 1)
		{
			open(endfl);
			time++;
			close(endfl);
			time++;
			isDest[endfl] = 0;
		}
		for(int i = 0; i < queries; i++)
		{
			if(completed.find(all_info[i]) == completed.end() && all_info[i][1] == endfl)
			{
				if(time >= all_info[i][0] && all_info[i][2] < all_info[i][1])
				{
					ready.push(all_info[i]);
					completed.insert(all_info[i]);
					isDest[all_info[i][2]] = 1;
					open(endfl);
					time++;
					close(endfl);
					time++;
					break;	
				}
			}
		}
	}
}

int main()
{

	cin >> queries;	

	for(int i = 0; i < queries; i++)
	{
		int time, origin, destination;
		cin >> time >> origin >> destination;
		vector<int> info;
		info.push_back(time);
		info.push_back(origin);
		info.push_back(destination);
		all_info.push_back(info);
	}
	
	for(int i = 0; i < queries; i++)
	{		
//		sort(all_info.begin(), all_info.end(), comp());
		while(!ready.empty())
		{
			vector<int> ele = ready.front();
			ready.pop();
			if(isDest[ele[2]] == 0)
				continue;
			else
			{
				move(currfloor, ele[2], currtime);
				
				currfloor = ele[2];
				
				isDest[ele[2]] = 0;
			}
		}
		
		while(currtime < all_info[i][0])
		{
			stay(currfloor);
			currtime++;
		}
		if(currtime >= all_info[i][0])
		{
			if(completed.find(all_info[i]) == completed.end())
			{
				completed.insert(all_info[i]);
				
				move(currfloor, all_info[i][1], currtime);
				
				currfloor = all_info[i][1];
				open(currfloor);
				currtime++;
				close(currfloor);
				currtime++;	

				move(all_info[i][1], all_info[i][2], currtime);
				currfloor = all_info[i][2];
				open(currfloor);
				currtime++;
				close(currfloor);
				currtime++;	
			}
		}
	}
}


/*
6
1 2 9
2 3 5
3 5 7
4 8 5
5 7 3
6 1 0
*/

/*
5
1 3 7
2 2 9
3 9 0
4 7 3
5 0 1
*/

/*
6
1 2 6
2 4 0
3 6 9
4 8 3
5 0 1
6 3 2
*/

/*
6
1 0 7
2 1 4
3 9 0
10 7 1
13 5 2
14 6 8
*/

/*
5
1 2 4
2 3 8
3 5 0
4 9 4
5 3 6
*/

