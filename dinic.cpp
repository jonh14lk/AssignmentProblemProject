#include <bits/stdc++.h>

using namespace std;

#define MAXN 502 // constantes
#define INF 1e9  // constantes

// struct de uma aresta
struct edge // está inserido na lista de adjacencia do vertice "from"
{
  int to;       // vertice "to" da aresta
  int index;    // indice da aresta "reversa", para achar em O(1)
  int flow;     // fluxo que foi passado nessa aresta
  int capacity; // capacidade da aresta
};

int num_applicants, num_jobs, source, sink;
vector<edge> graph[MAXN];
int dist[MAXN];
int start[MAXN];

// função para adicionar uma aresta
void add_edge(int from, int to, int capacity)
{
  graph[from].push_back({to, (int)graph[to].size(), capacity, capacity}); // aresta normal
  graph[to].push_back({from, (int)graph[from].size() - 1, 0, 0});         // aresta do grafo residual
}

// breadth-first search para verificar se existe um "novo grafo" de modo que exista um caminho de source até sink
bool bfs() // as arestas que que já estão com a capacidade igual a zero não irão ser consideradas
{
  memset(dist, -1, sizeof(dist)); // guarda a distancia entre o vértice i ao vértice source

  dist[source] = 0; // a distancia do vértice source até ele mesmo é 0

  queue<int> q;

  q.push(source);

  while (!q.empty()) // bfs
  {
    int u = q.front();
    q.pop();

    for (auto at : graph[u])
    {
      if (at.flow > 0 && dist[at.to] == -1) // se podemos passar pela aresta e o próximo vértice não foi visitado
      {
        q.push(at.to);
        dist[at.to] = dist[u] + 1; // a distancia sempre é incrementada em 1
      }
    }
  }

  return dist[sink] != -1; // se a distancia entre source e sink é diferente de -1, significa que existe um "novo grafo" valido
}

// depth-first search para achar o maior fluxo que é possível passar no caminho em que ele achar
int dfs(int u, int flow)
{
  if (u == sink) // se eu cheguei no meu vértice destino, devemos retornar imediatamente
  {
    return flow;
  }

  for (int &p = start[u]; p < graph[u].size(); p++) // dfs
  {
    edge &at = graph[u][p];

    if (at.flow > 0 && dist[u] == dist[at.to] - 1) // se podemos passar pela aresta e o próximo vértice foi visitado no bfs
    {
      int current = dfs(at.to, min(flow, at.flow)); // current = aresta de menor capacidade no caminho entre source e sink

      if (current > 0) // se current é maior do que zero, a opçao ideal é passar esse fluxo e retornar logo em seguida
      {
        at.flow -= current;                     // subtraio o fluxo máximo que da pra passar por esse caminho das outras arestas do grafo normal
        graph[at.to][at.index].flow += current; // somando o fluxo máximo  que da pra passar por esse caminho das outras arestas do grafo residual
        return current;
      }
    }
  }

  return 0;
}

// função principal do algoritmo
int dinic()
{
  int max_flow = 0;

  while (bfs() == true) // enquanto existir um "novo grafo" que possua caminho de source até sink
  {
    memset(start, 0, sizeof(start)); // start guarda a posição que em que devemos começar em cada lista de adjacencia no dfs
    while (true)
    {
      int flow = dfs(source, INF); // o dfs me retorna o fluxo que deu para passar em um novo caminho que ele achou de source até sink no "novo grafo"

      if (flow == 0) // se não for possivel passar mais fluxo por nesse "novo grafo", paramos a execução
      {
        break;
      }

      max_flow += flow; // caso contrário, iremos incrementar a resposta com o que encontramos
    }
  }

  return max_flow; // ao final teremos o fluxo máximo
}