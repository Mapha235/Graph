#define BASE
#ifdef SDL2
#include "../include/common.h"

typedef struct {
    int x,
        y;
} Position;

bool init(SDL_Window** window)
{
    //Error Checking/Initialisation
    if (SDL_Init(SDL_INIT_NOPARACHUTE & SDL_INIT_EVERYTHING) != 0) {
        SDL_Log("Unable to initialize SDL: %s\n", SDL_GetError());
        return -1;
    } else {
        //Specify OpenGL Version (4.2)
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_Log("SDL Initialised");
    }
    // GLuint vertexShader = glCreateShader( GL_VERTEX_SHADER);

    *window = SDL_CreateWindow(
        "Sudoku",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        640,
        480,
        SDL_WINDOW_OPENGL);

    //Check that the window was succesfully created
    if (window == NULL) {
        //Print error, if null
        std::cout << "Could not create window" << std::endl
                  << SDL_GetError() << std::endl;
        return 1;
    } else
        SDL_Log("Window Successful Generated");
    return 0;
}

int main(int argc, char* argv[])
{
    //Create Window Instance
    SDL_Window* window;
    init(&window);

    //Map OpenGL Context to Window
    SDL_GLContext glContext = SDL_GL_CreateContext(window);

    SDL_Surface* screenSurface = NULL;

    //Render
    SDL_Renderer* renderer = NULL;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_SetRenderDrawColor(renderer, 0, 0, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);
    SDL_UpdateWindowSurface(window);

    SDL_Surface* rect;

    SDL_Event event;
    bool running = 1;
    while (running) {
        if (SDL_PollEvent(&event)) {
            if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
                running = 0;
            } else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_m) {
                SDL_BlitSurface(rect, NULL, screenSurface, NULL);
            }
        }
        //Swap Render Buffers
        SDL_GL_SwapWindow(window);
    }

    //Free up resources
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}
#endif

#ifdef BASE
#include "Graph.hpp"
#include "WeightedGraph.hpp"
#include <deque>
#include <iostream>

#define INFTY -1

using namespace std;

unsigned int factorial(unsigned int n)
{
    if (n > 1)
        return n * factorial(n - 1);
    else
        return 1;
}

unsigned int maxEdgeCount(int v_count)
{
    // return factorial(v_count) / (2 * factorial(v_count - 2));
    int sum(0);
    for (int i = 0; i < v_count; i++)
        sum += i;
    return sum;
    // return ((v_count + 1) * v_count) / 2 - v_count;
}

void printEdges(Graph& graph)
{
    for (auto& it : graph.getEdges())
        cout << it << endl;
}

/*For whatever reason v_count > 12 will crash the program.*/
Graph completeGraph(int v_count)
{
    std::vector<std::pair<int, int>> edges;
    for (int i = 0; i < v_count; i++) {
        for (int j = 0; j < v_count; j++) {
            if (i < j)
                edges.push_back(std::make_pair(i + 1, j + 1));
        }
    }
    return Graph(v_count, edges);
}

Graph circleGraph(int v_count)
{
    std::vector<std::pair<int, int>> edges;
    for (int i = 1; i <= v_count; i++) {
        edges.push_back(std::make_pair(i, (((i + 1) % v_count == 0) ? (i + 1) : (i + 1) % v_count)));
    }
    return Graph(v_count, edges);
}

Graph starGraph(int v_count)
{
    std::vector<std::pair<int, int>> edges;
    for (int i = 1; i < v_count; ++i) {
        edges.push_back(std::make_pair(1, i + 1));
    }
    return Graph(v_count, edges);
}

/*@param e_count number of edges.*/
Graph pathGraph(int e_count)
{
    std::vector<std::pair<int, int>> edges;
    for (int i = 1; i <= e_count; i++)
        edges.push_back(std::make_pair(i, i + 1));
    return Graph(e_count + 1, edges);
}

std::vector<int> breadth_first_search(Graph g, int start_id = 1)
{
    std::vector<int> search_sequence;
    std::deque<int> queue;
    queue.push_back(start_id);

    std::vector<bool> visited;
    for (int i = 0; i < g.getVertices().size(); i++) {
        visited.push_back(false);
    }
    visited[start_id - 1] = true;

    try {
        while (!queue.empty()) {

            for (auto& it : queue) {
                cout << it << ',';
            }
            cout << "\n";

            for (auto it : g.getNeighbors(queue.front())) {
                if (!visited[it.getID() - 1]) {
                    queue.push_back(it.getID());
                    visited[it.getID() - 1] = true;
                }
            }
            search_sequence.push_back(queue.front());
            queue.pop_front();
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
    return search_sequence;
}

std::vector<int> depth_first_search(Graph g, int start_id = 1)
{
    std::vector<int> search_sequence_v;
    std::vector<int> stack;
    std::vector<bool> visited;

    for (int i = 0; i < g.getVertices().size(); i++) {
        visited.push_back(false);
    }

    stack.push_back(start_id);

    try {
        while (!stack.empty()) {
            auto v = stack.back();
            search_sequence_v.push_back(v);

            for (auto& it : stack) {
                cout << it << ',';
            }
            cout << "\n";

            stack.pop_back();

            if (!visited[v - 1]) {
                visited[v - 1] = true;

                for (auto it : g.getNeighbors(v)) {
                    if (!visited[it.getID() - 1]) {
                        stack.push_back(it.getID());
                    }
                }
            }
        }
    } catch (const std::exception& e) {
        std::cerr << e.what() << '\n';
    }
    return search_sequence_v;
}

void dijkstra()
{
}

int main(int argc, char** argv)
{
    pair<int, int> edge1(1, 2);
    pair<int, int> edge2(1, 3);
    pair<int, int> edge3(1, 4);
    pair<int, int> edge4(2, 5);
    pair<int, int> edge5(2, 6);
    pair<int, int> edge6(6, 10);
    pair<int, int> edge7(3, 7);
    pair<int, int> edge8(7, 11);
    pair<int, int> edge9(4, 8);
    pair<int, int> edge10(4, 9);
    pair<int, int> edge11(9, 12);
    pair<int, int> edge12(9, 13);
    auto edges = {
        edge1,
        edge2,
        edge3,
        edge4,
        edge5,
        edge6,
        edge7,
        edge8,
        edge9,
        edge10,
        edge11,
        edge12,
    };

    pair<int, int> edge_1(1, 2);
    pair<int, int> edge_2(1, 5);
    pair<int, int> edge_3(2, 4);
    pair<int, int> edge_4(4, 5);
    pair<int, int> edge_5(5, 3);
    pair<int, int> edge_6(3, 4);
    auto edges2 = {
        edge_1,
        edge_2,
        edge_3,
        edge_4,
        edge_5,
        edge_6
    };

    std::vector<std::vector<bool>> adj_matrix = {
        { 0, 1, 1, 1 },
        { 1, 0, 1, 1 },
        { 1, 1, 0, 1 },
        { 1, 1, 1, 0 }
    };

    Graph example(5, edges2);
    Graph complete = completeGraph(4);
    Graph circle = circleGraph(1000);
    Graph tree(13, edges);
    Graph star = starGraph(6);
    Graph path = pathGraph(7);
    Graph g(adj_matrix);

    // WeightedGraph weight(completeGraph(6),3);

    // for (auto it : complete.getEdges())
    //     cout << it << endl;

    // for (auto it : breadth_first_search(complete, 1))
    //     std::cout << it << ',';

    // cout << '\n';

    for (auto it : breadth_first_search(g, 1))
        std::cout << it << ',';


    //test[row][column]
    // cout << maxEdgeCount(5) << endl;

    return 0;
}

#endif
