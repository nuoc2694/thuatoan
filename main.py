import heapq

graph = {
    'A': ['B', 'C', 'D'],
    'B': ['M', 'N'],
    'C': ['L'],
    'D': ['O', 'P'],
    'M': ['X', 'Y'],
    'N': ['U', 'V'],
    'O': ['I', 'J'],
    'X': ['R', 'S'],
    'U': ['G', 'H']
}


def bfs(start, goal):
    queue = [start]
    parent = {start : None}
    while queue:
        current = queue.pop(0)
        if (current == goal):
            path=[]
            while current:
                path.append(current)
                current = parent[current]
            return path[::-1]

        for neighbor in graph.get(current, []):
            if neighbor not in parent:
                parent[neighbor] = current
                queue.append(neighbor)

    return None

def dfs(start, goal):
    stack = [start]
    parent = {start: None}

    while stack:
        current = stack.pop()
        if current == goal:
            path = []
            while current:
                path.append(current)
                current = parent[current]
            return path[::-1]

        for neighbor in graph.get(current, []):
            if neighbor not in parent:
                parent[neighbor] = current
                stack.append(neighbor)

    return None


def heuristic(a, b):
    # Hàm heuristic trả về khoảng cách (giả sử các đỉnh gần nhau hơn thì có tên chữ cái gần nhau hơn)
    return abs(ord(a) - ord(b))

def a_star(start, goal):
    open_set = []
    heapq.heappush(open_set, (0, start))
    g_score = {start: 0}
    parent = {start: None}

    while open_set:
        _, current = heapq.heappop(open_set)

        if current == goal:
            path = []
            while current:
                path.append(current)
                current = parent[current]
            return path[::-1]

        for neighbor in graph.get(current, []):
            tentative_g_score = g_score[current] + 1
            if neighbor not in g_score or tentative_g_score < g_score[neighbor]:
                g_score[neighbor] = tentative_g_score
                f_score = tentative_g_score + heuristic(neighbor, goal)
                heapq.heappush(open_set, (f_score, neighbor))
                parent[neighbor] = current

    return None