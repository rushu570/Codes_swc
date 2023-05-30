#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

const int MAXN = 100005;  // maximum number of nodes in the tree
const int LOG_MAXN = 20;  // maximum logarithmic value

vector<int> adj[MAXN];  // adjacency list of the tree
int depth[MAXN];  // depth of each node
int parent[MAXN][LOG_MAXN];  // parent array for binary lifting

void dfs(int node, int par, int d) {
    depth[node] = d;
    parent[node][0] = par;

    for (int i = 1; i < LOG_MAXN; i++) {
        if (parent[node][i - 1] != -1) {
            parent[node][i] = parent[parent[node][i - 1]][i - 1];
        } else {
            parent[node][i] = -1;
        }
    }

    for (int child : adj[node]) {
        if (child != par) {
            dfs(child, node, d + 1);
        }
    }
}

int lca(int u, int v) {
    // Make sure u is at a higher depth
    if (depth[u] < depth[v]) {
        swap(u, v);
    }

    // Lift u to the same depth as v
    for (int i = LOG_MAXN - 1; i >= 0; i--) {
        if (depth[u] - (1 << i) >= depth[v]) {
            u = parent[u][i];
        }
    }

    // If u and v are the same node or u is the parent of v, return u
    if (u == v) {
        return u;
    }

    // Lift u and v together until they have the same parent
    for (int i = LOG_MAXN - 1; i >= 0; i--) {
        if (parent[u][i] != parent[v][i]) {
            u = parent[u][i];
            v = parent[v][i];
        }
    }

    // Return the parent of u (which is the LCA of u and v)
    return parent[u][0];
}

int main() {
    int n;  // number of nodes in the tree
    cin >> n;

    // Read the edges of the tree
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    // Initialize the parent array
    for (int i = 0; i < MAXN; i++) {
        for (int j = 0; j < LOG_MAXN; j++) {
            parent[i][j] = -1;
        }
    }

    // Perform a depth-first search to calculate depths and parents
    dfs(1, -1, 0);

    int q;  // number of queries
    cin >> q;

    // Process the queries
    while (q--) {
        int u, v;
        cin >> u >> v;
        int lcaNode = lca(u, v);
        cout << "LCA of " << u << " and " << v << " is: " << lcaNode << endl;
    }

    return 0;
}
