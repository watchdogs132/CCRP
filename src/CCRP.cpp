#include<iostream>
#include<vector>
#include<algorithm>
#include<set>
#include<tuple>

using namespace std;

const int nodes = 14;

const int edges = 17;

int _cnt = 0;

const int max_time_series = 100;

vector<vector<pair<int, pair<int, int>>>> adj;;// spatial network

int edge[nodes + 5][nodes + 5][max_time_series + 5]; // edge capacity at any time

vector<vector<int>>node(nodes + 5, vector<int>(max_time_series)); // node capacity at any time

vector<int>source{ 1,2,8 }; // source nodes

vector<int>dest{ 13,14 };  // destination nodes

int occupied[nodes + 5][nodes + 5][max_time_series + 5];

vector<int>curr_src(nodes + 5); //current src capacity , number of evacuees.

int departure(int from, int to, int reach)
{
	int delta = 0;
	for (int i = reach; i < max_time_series; i++) {
		if (edge[from][to][i] != 0) {
			delta = i;
			break;
		}
	}
	return delta;
}

tuple<vector<int>, vector<int>> dijkstra(int src)
{
	set<pair<int, int>>q;
	q.insert({ 0,src });
	vector<int>p(nodes + 5, -1);
	vector<bool>done(nodes + 5, false);
	vector<int>d(nodes + 5, 1e9);
	vector<int>time;
	d[src] = 0;
	while (!q.empty()) {
		int a = q.begin()->second;
		q.erase(q.begin());
		if (done[a])continue;
		done[a] = true;
		for (auto v : adj[a]) {
			int from = a, to = v.first, capacity = v.second.first, time = v.second.second;
			int delta = (departure(from, to, d[from]) - d[from]);
			//d[from]=min(d[from] + delta,d[from]);
			if (d[from] + time + delta < d[to]) {
				q.erase({ d[to],to });
				d[to] = d[from] + time + delta;
				q.insert({ d[to],to });
				p[to] = from;
			}
		}
	}
	int final_dist = 1e9, final_dest;
	for (int i = 0; i < (int)dest.size(); i++) {
		if (p[dest[i]] == -1)continue;
		if (d[dest[i]] < final_dist) {
			final_dest = dest[i];
			final_dist = d[dest[i]];
		}
	}
	vector<int>path;
	for (int v = final_dest; v != src; v = p[v]) { path.push_back(v); }
	path.push_back(src);
	reverse(path.begin(), path.end());
	d[src] = departure(src, path[1], 0);
	for (int i = 1; i < (int)path.size(); i++) {
		int delta = (departure(path[i - 1], path[i], d[path[i - 1]]) - d[path[i - 1]]);
		int depart = d[path[i - 1]] + delta;
		time.push_back(depart);
	}
	time.push_back(d[final_dest]);
	path.push_back(final_dist);
	return { path, time };
}

vector<int>mark((int)source.size());  //mark source nodes which are done

tuple<vector<int>, vector<int>> shortest_path()
{
	for (int i = 0; i < (int)source.size(); i++) {
		if (curr_src[source[i]] == 0)mark[i] = 1;
	}
	int final_dist = 1e9;
	vector<int>final_path, final_time;
	for (int i = 0; i < (int)source.size(); i++) {
		if (mark[i])continue;
		int src = source[i];
		auto [path, time] = dijkstra(src);
		int dist = path.back();
		path.pop_back();
		if (dist < final_dist) {
			final_dist = dist;
			final_path = path;
			final_time = time;
		}
	}
	/*cout<<final_dist<<'\n';
	for(auto i:final_path)cout<<i<<' ';
	cout<<'\n';
	*/
	return { final_path, final_time };
}

int reserve_the_path(vector<int>path, vector<int>time)
{
	int f = curr_src[path[0]];
	for (int i = 1; i < (int)path.size() - 1; i++) { f = min(f, node[path[i]][time[i]]); }
	//cout << f <<' ';
	for (int i = 1; i < (int)path.size(); i++) {
		f = min(f, edge[path[i - 1]][path[i]][time[i - 1]]);
	}
	//cout << f << ' ';
	for (int i = 0; i < (int)path.size() - 1; i++) {
		int nod = path[i], t = time[i];
		node[nod][t] -= f;
	}
	for (int i = 1; i < (int)path.size(); i++) {
		edge[path[i - 1]][path[i]][time[i - 1]] -= f;
	}
	for (int i = 1; i < (int)path.size(); i++) {
		occupied[path[i - 1]][path[i]][time[i - 1]] = 1;
	}
	//cout << f << ' ';
	curr_src[path[0]] -= f;
	return f;
}

bool check()
{
	for (int i = 0; i < (int)source.size(); i++) {
		if (curr_src[source[i]] != 0)return false;
	}
	return true;
}

void display_the_path(int f, vector<int>path, vector<int>time)
{
	//cout << path.size() << '\n';
	cout << (_cnt + 1) << ' ';
	cout << "N" << path[0] << ' ';
	cout << f << ' ';
	for (int i = 0; i < (int)path.size(); i++) {
		cout << "N" << path[i] << "(T" << time[i] << ")" << ' ';
	}
	cout << time[0] << ' ';
	cout << time[(int)time.size() - 1] << ' ';
	cout << '\n';
	++_cnt;
}

void CCRP()
{
	cout << "****************************************************************************" << '\n';
	while (!check()) {
		auto [path, time] = shortest_path();
		auto f = reserve_the_path(path, time);
		if (f == 0)continue;
		display_the_path(f, path, time);
	}
	cout << '\n';
	cout << "****************************************************************************" << '\n';
}

void input()
{
	adj.clear();
	adj.resize(nodes + 5);
	for (int i = 1; i <= edges; i++) {
		int from, to, capacity, time;
		cin >> from >> to >> capacity >> time;
		adj[from].push_back({ to,{capacity,time} });
	}
	for (int i = 1; i <= nodes - (int)dest.size(); i++) {
		int a;
		cin >> a;
		for (int j = 0; j < max_time_series; j++) {
			node[i][j] = a;
		}
	}

	for (int i = 0; i <= nodes; i++) {
		for (int j = 0; j <= nodes; j++) {
			for (int k = 0; k < max_time_series; k++) {
				edge[i][j][k] = 0;
			}
		}
	}

	for (int i = 1; i <= nodes; i++) {
		for (int j = 0; j < adj[i].size(); j++) {
			int from = i, to = adj[i][j].first, capacity = adj[i][j].second.first;
			for (int k = 0; k < max_time_series; k++) {
				edge[from][to][k] = capacity;
			}
		}
	}
	for (int i = 0; i < (int)source.size(); i++) {
		int sz;
		cin >> sz;
		curr_src[source[i]] = sz;
	}
	for (int i = 0; i <= nodes; i++) {
		for (int j = 0; j <= nodes; j++) {
			for (int k = 0; k < max_time_series; k++) {
				occupied[i][j][k] = 0;
			}
		}
	}
	CCRP();
	//cout << _cnt << '\n';
}

int main()
{
	input();
}
