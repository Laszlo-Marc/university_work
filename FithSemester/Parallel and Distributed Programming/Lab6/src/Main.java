import java.util.*;
import java.util.concurrent.*;
import java.util.concurrent.locks.*;

class UndirectedGraph {
    private List<List<Integer>> container;
    private List<Integer> nodes;

    UndirectedGraph(int nodeCount) {
        this.container = new ArrayList<>(nodeCount);
        this.nodes = new ArrayList<>();

        for (int i = 0; i < nodeCount; i++) {
            this.container.add(new ArrayList<>());
            this.nodes.add(i);
        }
    }

    void addEdge(int nodeA, int nodeB) {
        this.container.get(nodeA).add(nodeB);
        this.container.get(nodeB).add(nodeA);
    }

    List<Integer> neighboursOf(int node) {
        return this.container.get(node);
    }

    List<Integer> getNodes() {
        return nodes;
    }

    int size() {
        return this.container.size();
    }
}

public class Main {

    public static void main(String[] args) throws InterruptedException {

        int GRAPHS_COUNT = 101;

        List<UndirectedGraph> graphs = new ArrayList<>();

        for (int i = 1; i <= GRAPHS_COUNT; i++) {
            graphs.add(generateRandomHamiltonian(i * 10));
        }

        System.out.println("Sequential");
        batchTesting(graphs, 1);

        System.out.println("Parallel");
        batchTesting(graphs, 4);
    }

    private static void batchTesting(List<UndirectedGraph> graphs, int threadCount) throws InterruptedException {
        for (int i = 0; i < graphs.size(); i++) {
            test(i, graphs.get(i), threadCount);
        }
    }

    private static void test(int level, UndirectedGraph graph, int threadCount) throws InterruptedException {
        long startTime = System.nanoTime();
        findHamiltonian(graph, threadCount);
        long endTime = System.nanoTime();
        long duration = (endTime - startTime) / 1_000_000;
        if (level == 1 || level == 50 || level == 100)
            System.out.println("Level " + level + ": " + duration + " ms");

    }

    private static void findHamiltonian(UndirectedGraph graph, int threadCount) throws InterruptedException {
        ExecutorService pool = Executors.newFixedThreadPool(threadCount);
        Lock lock = new ReentrantLock();
        List<Integer> result = new ArrayList<>(graph.size());

        for (int i = 0; i < graph.size(); i++) {
            pool.execute(new Task(graph, i, result, lock));

        }

        pool.shutdown();
        pool.awaitTermination(10, TimeUnit.SECONDS);

    }

    private static UndirectedGraph generateRandomHamiltonian(int size) {
        UndirectedGraph graph = new UndirectedGraph(size);

        List<Integer> nodes = graph.getNodes();
        Collections.shuffle(nodes);

        // Create a Hamiltonian cycle
        for (int i = 1; i < nodes.size(); i++) {
            graph.addEdge(nodes.get(i - 1), nodes.get(i));
        }
        graph.addEdge(nodes.get(nodes.size() - 1), nodes.get(0));

        Random random = new Random();

        // Add some random edges
        for (int i = 0; i < size / 2; i++) {
            int nodeA = random.nextInt(size);
            int nodeB = random.nextInt(size);

            if (nodeA != nodeB) {
                graph.addEdge(nodeA, nodeB);
            }
        }

        return graph;
    }

    static class Task implements Runnable {
        private final UndirectedGraph graph;
        private final int startNode;
        private final List<Integer> result;
        private final Lock lock;

        Task(UndirectedGraph graph, int startNode, List<Integer> result, Lock lock) {
            this.graph = graph;
            this.startNode = startNode;
            this.result = result;
            this.lock = lock;
        }

        @Override
        public void run() {
            List<Integer> path = new ArrayList<>();
            Set<Integer> visited = new HashSet<>();
            if (dfs(startNode, path, visited)) {
                lock.lock();
                try {
                    if (result.isEmpty()) {
                        result.addAll(path);
                    }
                } finally {
                    lock.unlock();
                }
            }
        }

        private boolean dfs(int current, List<Integer> path, Set<Integer> visited) {
            path.add(current);
            visited.add(current);

            if (path.size() == graph.size()) {
                // Check if the last node connects to the first node
                return graph.neighboursOf(current).contains(path.get(0));
            }

            for (int neighbour : graph.neighboursOf(current)) {
                if (!visited.contains(neighbour)) {
                    if (dfs(neighbour, path, visited)) {
                        return true;
                    }
                }
            }

            // Backtrack
            path.remove(path.size() - 1);
            visited.remove(current);
            return false;
        }
    }
}