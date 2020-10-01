#include <bits/stdc++.h>
#include "dinic.cpp"

using namespace std;

int main()
{
  cin >> num_applicants >> num_jobs;

  source = 0, sink = num_applicants + num_jobs + 1; // definindo qual o vertice source e qual o vértice sink na rede de fluxo

  for (int i = 1; i <= num_applicants; i++) // para cada vértice equivalente a um candidato
  {
    add_edge(source, i, 1); // adicionar uma aresta de source até ele com capacidade = 1
  }

  for (int i = 1; i <= num_applicants; i++) // para cada vértice equivalente a um candidato
  {
    while (true) // ler quais os empregos que cada canditato está interessado
    {
      int current;
      cin >> current;
      if (current != 0)
      {
        int index = num_applicants + current; // os vértices equivalentes aos empregos disponiveis são indexados a partir de (n + 1)
        add_edge(i, index, 1);                // adicionar uma aresta entre o candidato e o emprego que ele está interessado
      }
      else
      {
        break;
      }
    }
  }

  for (int i = 1; i <= num_jobs; i++) // para cada vértice equivalente a um emprego disponivel
  {
    int index = num_applicants + i; // os vértices equivalentes aos empregos disponiveis são indexados a partir de (n + 1)
    add_edge(index, sink, 1);       // adicionar uma aresta entre cada emprego e o vertice sink com capacidade = 1
  }

  int answer = dinic(); // quantos candidatos irão conseguir um emprego = fluxo máximo na rede de fluxo montada

  cout << answer << " candidates were selected!" << endl;

  cout << endl;

  vector<int> winner(num_jobs, -1);

  for (int i = num_applicants + 1; i <= num_applicants + num_jobs; i++) // para cada vértice equivalente a um emprego disponivel
  {
    for (auto const &j : graph[i])
    {
      if (j.to != sink && j.flow > 0) // se a aresta atual não tem sink como destino, ela faz parte do grafo residual e se algum fluxo foi passado por ela, ela foi utilizada
      {
        int index = i - num_applicants; // então o vértice "to" da aresta é o candidato que ficou com o emprego i
        winner[index - 1] = j.to;
        cout << "the applicant " << j.to << " got the job " << index << endl;
      }
    }
  }

  cout << endl;

  for (int i = 0; i < num_jobs; i++) // imprimir ao final, os empregos que não contrataram ninguém
  {
    int index = i + 1;
    if (winner[i] == -1)
    {
      cout << "nobody got the job " << index << endl;
    }
  }

  cout << endl;

  return 0;
}