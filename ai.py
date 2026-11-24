from collections import deque
from random import shuffle
import heapq
from time import time

(1, 2, 3, 4, 5, 6, 0, 7, 8)


class EightPuzzleProblem:
    def __init__(self):
        # 0은 빈칸
        # fmt: off
        self.initial_state = (0, 2, 3,
                              4, 8, 6,
                              1, 7, 5)
        self.goal_state = (1, 2, 3,
                           4, 5, 6,
                           7, 8, 0)
        # fmt: on

    # 현재 상태가 목표 상태인지 검사
    def goal_test(self, state):
        return state == self.goal_state

    # 빈칸이 움직일 수 있는 방향 반환
    def actions(self, state):
        blank = state.index(0)
        row = blank // 3
        col = blank % 3

        possible_actions = []

        if row > 0:
            possible_actions.append("위")

        if row < 2:
            possible_actions.append("아래")

        if col > 0:
            possible_actions.append("왼쪽")

        if col < 2:
            possible_actions.append("오른쪽")

        return possible_actions

    # 행동을 실행한 다음 상태 반환
    def result(self, state, action):
        new_state = list(state)
        blank = state.index(0)

        if action == "위":
            target = blank - 3
        elif action == "아래":
            target = blank + 3
        elif action == "왼쪽":
            target = blank - 1
        else:
            target = blank + 1

        # 빈칸과 이동할 칸의 위치 교환
        new_state[blank], new_state[target] = (new_state[target], new_state[blank])

        # set에 저장할 수 있도록 튜플로 반환
        return tuple(new_state)

    # 한 번 움직일 때마다 비용은 1
    def step_cost(self, state, action):
        return 1

    def heuristic(self, state):
        """각 타일의 Manhattan distance 합을 계산한다."""
        distance = 0
        for tile in range(1, 9):
            current = state.index(tile)
            goal = self.goal_state.index(tile)
            current_row, current_col = divmod(current, 3)
            goal_row, goal_col = divmod(goal, 3)
            distance += abs(current_row - goal_row)
            distance += abs(current_col - goal_col)
        return distance


# 탐색 트리의 노드

total = 0


class Node:

    def __init__(self, state, parent=None, action=None, path_cost=0, depth=0):

        global total
        total += 1

        self.state = state  # 현재 상태

        self.parent = parent  # 부모 노드

        self.action = action  # 부모에서 현재 상태로 온 행동

        self.path_cost = path_cost  # 시작점부터의 비용

        self.depth = depth


# 자식 노드 생성


def child_node(problem, parent, action):

    next_state = problem.result(parent.state, action)

    return Node(
        state=next_state,
        parent=parent,
        action=action,
        path_cost=parent.path_cost + problem.step_cost(parent.state, action),
    )


# 목표까지 사용한 행동을 구함


def solution(node):

    actions = []

    while node.parent is not None:

        actions.append(node.action)

        node = node.parent

    actions.reverse()

    return actions


def expand(node, problem):
    successors = []

    # 현재 상태에서 가능한 행동들을 하나씩 실행
    for action in problem.actions(node.state):
        next_state = problem.result(node.state, action)

        child = Node(
            state=next_state,
            parent=node,
            action=action,
            path_cost=(node.path_cost + problem.step_cost(node.state, action)),
            depth=node.depth + 1,
        )

        successors.append(child)

    return successors


def breadth_first_search(problem):
    # 초기 노드 생성
    node = Node(problem.initial_state)
    q = deque[Node]()
    q.append(node)
    while q:
        u = q.popleft()
        if problem.goal_test(u.state):
            return solution(u)
        for v in expand(u, problem):
            q.append(v)


problem = EightPuzzleProblem()

MAX_DEPTH = 20


def dfs(u: Node):
    if MAX_DEPTH < u.depth:
        return
    if problem.goal_test(u.state):
        return solution(u)
    for v in expand(u, problem):
        if r := dfs(v):
            return r

def dijkstra():
    S = (7, 2, 4, 5, 0, 6, 8, 3, 1)
    T = (1, 2, 3, 4, 5, 6, 7, 8, 0)
    dist = dict()
    pq = []
    dist[S] = 0
    heapq.heappush(pq, (0, S))
    while pq:
        d, u = heapq.heappop(pq)
        if d != dist[u]:
            continue
        for action in problem.actions(u):
            v = problem.result(u, action)
            if (v not in dist) or (dist[u] + 1 < dist[v]):
                dist[v] = dist[u] + 1
                heapq.heappush(pq, (dist[v], v))
    return dist[T]

def astar():
    S = (7, 2, 4, 5, 0, 6, 8, 3, 1)
    T = (1, 2, 3, 4, 5, 6, 7, 8, 0)
    dist = dict()
    pq = []
    dist[S] = problem.heuristic(S)
    heapq.heappush(pq, (problem.heuristic(S), S))
    while pq:
        d, u = heapq.heappop(pq)
        if d != dist[u]:
            continue
        for action in problem.actions(u):
            v = problem.result(u, action)
            nd = dist[u] - problem.heuristic(u) + 1 + problem.heuristic(v)
            if (v not in dist) or (nd < dist[v]):
                dist[v] = nd
                heapq.heappush(pq, (nd, v))
    return dist[T]

def run(f):
    start = time()
    ans = f()
    end = time()
    print(f"{ans}({end - start:.2f}s)")

run(dijkstra)
run(astar)
